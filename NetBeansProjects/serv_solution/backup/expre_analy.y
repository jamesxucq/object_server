
//
%token_prefix TK_

//
%token_type {leaf_node *}
%default_type {oper_node *}

//
// %extra_context {Parse *state}
%extra_argument {pastat *state}

//
%syntax_error {
  // UNUSED_PARAMETER(yymajor);  /* Silence some compiler warnings */
  strcpy(state->erro_msg, "syntax error near.\n");
}
%stack_overflow {
  strcpy(state->erro_msg, "parser stack overflow.\n");
}

%parse_accept {
  state->accept = PARSE_SUCCESS;
  strcpy(state->erro_msg, "parsing complete!\n");
}

%parse_failure {
  state->accept = PARSE_FAULT;
  strcpy(state->erro_msg, "Giving up.  Parser is hopelessly lost...\n");
}

//
%name ExpreParse

//
%include {
#include "lexic/valtok.h"
#include "synta_tree.h"
#include "gramm_analy.h"

//
#define YYNOERRORRECOVERY 1

} // end %include

//
%token OR AND NOT IS MATCH LIKE_KW BETWEEN IN NE EQ.
%token GT LE LT GE ESCAPE.
%token LP RP.
%token PLUS MINUS.

//
%fallback ID LIKE_KW MATCH CTIME_KW.

//
%left OR.
%left AND.
%right NOT.
%left IS MATCH LIKE_KW BETWEEN IN ISNULL NOTNULL NE EQ.
%left GT LE LT GE.
%right ESCAPE.
%left BITAND BITOR LSHIFT RSHIFT.
%left PLUS MINUS.
%left STAR SLASH REM.
%left CONCAT.
%left COLLATE.
%right BITNOT.
%nonassoc ON.

//
%token_class ids  ID|STRING.

/////////////////////////// Expression Processing /////////////////////////////
//

%type expr {oper_node *}
%destructor expr {OPER_NODE_DELE($$);}
%type term {leaf_node *}
%destructor term {LEAF_NODE_DELE($$);}

//
expres ::= expr(X).
expr(A) ::= term(X). { A = new_oper_leaf(TERM_TOKE, X);}
expr(A) ::= LP expr(X) RP. { A = X; }
//
term(A) ::= NULL|FLOAT(X). {A = new_leaf_vato(X);}
term(A) ::= BLOB(X). {A = new_leaf_vato(X);}
term(A) ::= STRING(X). {A = new_leaf_vato(X);}
term(A) ::= INTEGER(X). { A = new_leaf_vato(X);}
term(A) ::= VARIABLE(X). {A = new_leaf_vato(X);}
term(A) ::= ID(X). { A = new_leaf_vato(X);}
term(A) ::= JOIN_KW(X). {A = new_leaf_vato(X);}

//
expr(A) ::= expr(A) COLLATE ids(C). {A = expr_add_collate(state, TK_COLLATE, C, NULL);}
expr(A) ::= ID(X) LP exprlist(Y) RP. { A = expr_function(X, Y); }
expr(A) ::= ID(X) LP STAR RP. {/* expr(A) ::= ID(X) LP STAR RP.  */}

//
term(A) ::= CTIME_KW(OP). {A = new_leaf_vato(OP);}

// disable by james 20210918
// expr(A) ::= LP nexprlist(X) COMMA expr(Y) RP. {  
//    printf("expr(A) ::= LP nexprlist(X) COMMA expr(Y) RP.\n");
// }

//
expr(A) ::= expr(X) AND(OP) expr(Y). {A = new_oper_node(state, @OP, X, Y);}
expr(A) ::= expr(X) OR(OP) expr(Y). {A = new_oper_node(state, @OP, X, Y);}
expr(A) ::= expr(X) LT|GT|GE|LE(OP) expr(Y). { A = new_oper_node(state, @OP, X, Y); }
expr(A) ::= expr(X) EQ|NE(OP) expr(Y). {A = new_oper_node(state, @OP, X, Y);}
expr(A) ::= expr(X) BITAND|BITOR|LSHIFT|RSHIFT(OP) expr(Y). {A = new_oper_node(state, @OP, X, Y);}
expr(A) ::= expr(X) PLUS|MINUS(OP) expr(Y). {A = new_oper_node(state, @OP, X, Y);}
expr(A) ::= expr(X) STAR|SLASH|REM(OP) expr(Y). {A = new_oper_node(state, @OP, X, Y);}
expr(A) ::= expr(X) CONCAT(OP) expr(Y). {A = new_oper_node(state, @OP, X, Y);}

//
%type likeop {leaf_node *}
likeop(A) ::= LIKE_KW|MATCH(X). {A = X;}
likeop(A) ::= NOT LIKE_KW|MATCH(X). {A = X;}
expr(A) ::= expr(A) likeop(OP) expr(Y).  [LIKE_KW] {
    printf("expr(A) ::= expr(A) likeop(OP) expr(Y).\n");
}
expr(A) ::= expr(A) likeop(OP) expr(Y) ESCAPE expr(E).  [LIKE_KW] {
    printf("expr(A) ::= expr(A) likeop(OP) expr(Y) ESCAPE expr(E).\n");
}

expr(A) ::= expr(A) ISNULL|NOTNULL(E). {A = new_oper_node(state,@E,A,0);}
expr(A) ::= expr(A) NOT NULL. {A = new_oper_node(state,TK_NOTNULL,A,0);}

// 
expr(A) ::= expr(A) IS expr(Y). {
  A = new_oper_node(state,TK_IS,A,Y);
  binary_unary_null(state, Y, A, TK_ISNULL);
}
expr(A) ::= expr(A) IS NOT expr(Y). {
  A = new_oper_node(state,TK_IS,A,Y);
  binary_unary_null(state, Y, A, TK_NOTNULL);
}

//
expr(A) ::= NOT(B) expr(X). {A = new_oper_node(state, @B, X, 0);}
expr(A) ::= BITNOT(B) expr(X). {A = new_oper_node(state, @B, X, 0);}
expr(A) ::= PLUS|MINUS(B) expr(X). [BITNOT] {A = new_oper_node(state, @B==TK_PLUS ? TK_UPLUS : TK_UMINUS, X, 0);}

//
%type between_op {int}
between_op(A) ::= BETWEEN. {A = 0;}
between_op(A) ::= NOT BETWEEN. {A = 1;}
expr(A) ::= expr(A) between_op(N) expr(X) AND expr(Y). [BETWEEN] {
    printf("expr(A) between_op(N) expr(X) AND expr(Y).\n");
}

//
%type in_op {int}
in_op(A) ::= IN. {A = 0;}
in_op(A) ::= NOT IN. {A = 1;}
expr(A) ::= expr(A) in_op(N) LP exprlist(Y) RP. [IN] {
    printf("expr(A) ::= expr(A) in_op(N) LP exprlist(Y) RP.\n");
}

//
%type exprlist {leaf_list *}
%destructor exprlist {leaf_list_dele($$);}
%type nexprlist {leaf_list *}
%destructor nexprlist {leaf_list_dele($$);}

exprlist(A) ::= nexprlist(A).
exprlist(A) ::= . {A = NULL;}
nexprlist(A) ::= nexprlist(X) COMMA term(Y). { A = appe_leaf_vato(X, Y); }
nexprlist(A) ::= nexprlist(X) COMMA PLUS|MINUS(B) term(Y). { A = appe_leaf_vats(X, @B==TK_PLUS ? TK_UPLUS : TK_UMINUS, Y); }
nexprlist(A) ::= nexprlist(X) term(Y). { A = appe_leaf_type(X, Y); }
nexprlist(A) ::= PLUS|MINUS(B) term(X). { A = new_leaf_sign(@B==TK_PLUS ? TK_UPLUS : TK_UMINUS, X); }
nexprlist(A) ::= term(X). { A = new_leaf_list(X); }
