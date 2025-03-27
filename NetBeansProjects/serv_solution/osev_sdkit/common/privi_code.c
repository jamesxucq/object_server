
#include "commo_header.h"


#include "privi_code.h"

// constr
coqu_pvmk epost_privi = {BLVH_WRITE, ENTP_POST}; // post
coqu_pvmk eecho_privi = {BLVH_READ, ENTP_STATU}; // echo
coqu_pvmk ecrea_privi = {BLVH_WRITE, ENTP_CREAT}; // creat
coqu_pvmk edrop_privi = {BLVH_WRITE, ENTP_DROP}; // drop
coqu_pvmk eupda_privi = {BLVH_WRITE, ENTP_UPDAT}; // updat
coqu_pvmk einse_privi = {BLVH_WRITE, ENTP_INSER}; // inser
coqu_pvmk esear_privi = {BLVH_READ, ENTP_SEARO}; // search
coqu_pvmk einvo_privi = {BLVH_EXECU, ENTP_INVOK}; // invok

// query
coqu_pvmk qpost_privi = {BLVF_WRITE, QUEP_POST}; // post
coqu_pvmk qecho_privi = {BLVF_READ, QUEP_STATU}; // echo
coqu_pvmk qcrea_privi = {BLVF_WRITE, QUEP_CREAT}; // creat
coqu_pvmk qdrop_privi = {BLVF_WRITE, QUEP_DROP}; // drop
coqu_pvmk qupda_privi = {BLVF_WRITE, QUEP_UPDAT}; // updat
coqu_pvmk qinse_privi = {BLVF_WRITE, QUEP_INSER}; // inser
coqu_pvmk qsear_privi = {(BLVF_READ | BLVF_WRITE), QUEP_SEARQ}; // search
coqu_pvmk qinvo_privi = {BLVF_EXECU, QUEP_INVOK}; // invok
coqu_pvmk qfact_privi = {(BLVF_READ | BLVF_WRITE), QUEP_FACTO}; // facto