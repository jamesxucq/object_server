#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/d8a3b606/modoid.o \
	${OBJECTDIR}/_ext/d8a3b606/obid.o \
	${OBJECTDIR}/_ext/d8a3b606/pamstyl_utili.o \
	${OBJECTDIR}/_ext/d8a3b606/stoid.o \
	${OBJECTDIR}/_ext/d8a3b606/xml_utili.o \
	${OBJECTDIR}/_ext/f534dc3f/binary_logger.o \
	${OBJECTDIR}/_ext/f534dc3f/linenoise.o \
	${OBJECTDIR}/cinstru.o \
	${OBJECTDIR}/clit_bzl.o \
	${OBJECTDIR}/clit_obje.o \
	${OBJECTDIR}/clit_struct.o \
	${OBJECTDIR}/connect.o \
	${OBJECTDIR}/cstatu.o \
	${OBJECTDIR}/cstri_utili.o \
	${OBJECTDIR}/debug_funct_sh.o \
	${OBJECTDIR}/finish_cline/cline_valid_ite.o \
	${OBJECTDIR}/finish_cline/parse_cline.o \
	${OBJECTDIR}/finish_instru/finis_instru.o \
	${OBJECTDIR}/finish_instru/finis_tolkit.o \
	${OBJECTDIR}/finish_instru/finish_ite.o \
	${OBJECTDIR}/finish_instru/instru_utili.o \
	${OBJECTDIR}/finish_instru/print_strea.o \
	${OBJECTDIR}/finish_instru/tokit_utili.o \
	${OBJECTDIR}/instru_execute/execut_instru.o \
	${OBJECTDIR}/instru_execute/execute_ite.o \
	${OBJECTDIR}/options.o \
	${OBJECTDIR}/osev_clit.o \
	${OBJECTDIR}/osvp_utili.o \
	${OBJECTDIR}/parse_resxml.o \
	${OBJECTDIR}/parse_valida/conve_lvikoi.o \
	${OBJECTDIR}/parse_valida/filli_conve.o \
	${OBJECTDIR}/parse_valida/later_check.o \
	${OBJECTDIR}/parse_valida/parse_ilevoi.o \
	${OBJECTDIR}/parse_valida/parse_klevoi.o \
	${OBJECTDIR}/parse_valida/parse_levivk.o \
	${OBJECTDIR}/parse_valida/pretr_check.o \
	${OBJECTDIR}/parse_valida/split_pamvs.o \
	${OBJECTDIR}/parse_valida/split_space.o \
	${OBJECTDIR}/parse_valida/valida_ite.o \
	${OBJECTDIR}/pretr_instru/cont_name_obid.o \
	${OBJECTDIR}/pretr_instru/conve_utili.o \
	${OBJECTDIR}/pretr_instru/defau_utili.o \
	${OBJECTDIR}/pretr_instru/instr_pretr.o \
	${OBJECTDIR}/pretr_instru/instru.o \
	${OBJECTDIR}/pretr_instru/post_inner_valu.o \
	${OBJECTDIR}/pretr_instru/pre_instru_ite.o \
	${OBJECTDIR}/pretr_instru/repla_inner_valu.o \
	${OBJECTDIR}/pretr_instru/statu_inner_valu.o \
	${OBJECTDIR}/pretr_instru/valid_logic.o \
	${OBJECTDIR}/pretr_prompt/prompt_ite.o \
	${OBJECTDIR}/pretr_prompt/prompt_utili.o \
	${OBJECTDIR}/privi_utili.o \
	${OBJECTDIR}/tokit_instru/common/ccomm_types.o \
	${OBJECTDIR}/tokit_instru/execu_tokit_ite.o \
	${OBJECTDIR}/tokit_instru/explain.o \
	${OBJECTDIR}/tokit_instru/fmt_lang/fmt_binoid.o \
	${OBJECTDIR}/tokit_instru/fmt_lang/fmt_xmlang.o \
	${OBJECTDIR}/tokit_instru/format.o \
	${OBJECTDIR}/tokit_instru/key_valu.o \
	${OBJECTDIR}/tokit_instru/kstri_utili.o \
	${OBJECTDIR}/tokit_instru/list.o \
	${OBJECTDIR}/tokit_instru/load.o \
	${OBJECTDIR}/tokit_instru/lvtp_explain/explain_ite.o \
	${OBJECTDIR}/tokit_instru/parse_list/klist_ite.o \
	${OBJECTDIR}/tokit_instru/parse_list/parse_lev1.o \
	${OBJECTDIR}/tokit_instru/pretty.o \
	${OBJECTDIR}/tokit_instru/pretty_utili/pretty_ite.o \
	${OBJECTDIR}/tokit_instru/save.o \
	${OBJECTDIR}/tokit_instru/trans_lang/filli_clang.o \
	${OBJECTDIR}/tokit_instru/trans_lang/lev1_utili.o \
	${OBJECTDIR}/tokit_instru/trans_lang/load_conte.o \
	${OBJECTDIR}/tokit_instru/trans_lang/lv2p_expan.o \
	${OBJECTDIR}/tokit_instru/trans_lang/lv2p_list.o \
	${OBJECTDIR}/tokit_instru/trans_lang/parse_expand.o \
	${OBJECTDIR}/tokit_instru/trans_lang/parse_l12con.o \
	${OBJECTDIR}/tokit_instru/trans_lang/parse_lv2p_atti.o \
	${OBJECTDIR}/tokit_instru/trans_lang/seri_leng.o \
	${OBJECTDIR}/tokit_instru/trans_lang/tran_gcc_cpp.o \
	${OBJECTDIR}/tokit_instru/trans_lang/trans_utili.o \
	${OBJECTDIR}/tokit_instru/trans_lang/translate.o \
	${OBJECTDIR}/tokit_instru/trans_lang/tstri_utili.o \
	${OBJECTDIR}/tokit_instru/translate.o


# C Compiler Flags
CFLAGS=-Wall -D_DEBUG -D_OSEV_CLIT -D_LARGEFILE64_SOURCE -D_FILEOFFSET_BITS==64 -fno-strict-aliasing -Wno-maybe-uninitialized -O2

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/osev-cli

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/osev-cli: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/osev-cli ${OBJECTFILES} ${LDLIBSOPTIONS} ../../client/clang/osev_clie_clang/dist/Debug/GNU-Linux/libosev_clie_clang.a ../third_party/packing/libpacking.a -lpthread /lib/x86_64-linux-gnu/libmbedcrypto.a

${OBJECTDIR}/_ext/d8a3b606/modoid.o: ../osev_common/modoid.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d8a3b606
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8a3b606/modoid.o ../osev_common/modoid.c

${OBJECTDIR}/_ext/d8a3b606/obid.o: ../osev_common/obid.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d8a3b606
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8a3b606/obid.o ../osev_common/obid.c

${OBJECTDIR}/_ext/d8a3b606/pamstyl_utili.o: ../osev_common/pamstyl_utili.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d8a3b606
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8a3b606/pamstyl_utili.o ../osev_common/pamstyl_utili.c

${OBJECTDIR}/_ext/d8a3b606/stoid.o: ../osev_common/stoid.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d8a3b606
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8a3b606/stoid.o ../osev_common/stoid.c

${OBJECTDIR}/_ext/d8a3b606/xml_utili.o: ../osev_common/xml_utili.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d8a3b606
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8a3b606/xml_utili.o ../osev_common/xml_utili.c

${OBJECTDIR}/_ext/f534dc3f/binary_logger.o: ../third_party/binary_logger.c
	${MKDIR} -p ${OBJECTDIR}/_ext/f534dc3f
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/f534dc3f/binary_logger.o ../third_party/binary_logger.c

${OBJECTDIR}/_ext/f534dc3f/linenoise.o: ../third_party/linenoise.c
	${MKDIR} -p ${OBJECTDIR}/_ext/f534dc3f
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/f534dc3f/linenoise.o ../third_party/linenoise.c

${OBJECTDIR}/cinstru.o: cinstru.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cinstru.o cinstru.c

${OBJECTDIR}/clit_bzl.o: clit_bzl.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clit_bzl.o clit_bzl.c

${OBJECTDIR}/clit_obje.o: clit_obje.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clit_obje.o clit_obje.c

${OBJECTDIR}/clit_struct.o: clit_struct.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clit_struct.o clit_struct.c

${OBJECTDIR}/connect.o: connect.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/connect.o connect.c

${OBJECTDIR}/cstatu.o: cstatu.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cstatu.o cstatu.c

${OBJECTDIR}/cstri_utili.o: cstri_utili.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cstri_utili.o cstri_utili.c

${OBJECTDIR}/debug_funct_sh.o: debug_funct_sh.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/debug_funct_sh.o debug_funct_sh.c

${OBJECTDIR}/finish_cline/cline_valid_ite.o: finish_cline/cline_valid_ite.c
	${MKDIR} -p ${OBJECTDIR}/finish_cline
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/finish_cline/cline_valid_ite.o finish_cline/cline_valid_ite.c

${OBJECTDIR}/finish_cline/parse_cline.o: finish_cline/parse_cline.c
	${MKDIR} -p ${OBJECTDIR}/finish_cline
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/finish_cline/parse_cline.o finish_cline/parse_cline.c

${OBJECTDIR}/finish_instru/finis_instru.o: finish_instru/finis_instru.c
	${MKDIR} -p ${OBJECTDIR}/finish_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/finish_instru/finis_instru.o finish_instru/finis_instru.c

${OBJECTDIR}/finish_instru/finis_tolkit.o: finish_instru/finis_tolkit.c
	${MKDIR} -p ${OBJECTDIR}/finish_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/finish_instru/finis_tolkit.o finish_instru/finis_tolkit.c

${OBJECTDIR}/finish_instru/finish_ite.o: finish_instru/finish_ite.c
	${MKDIR} -p ${OBJECTDIR}/finish_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/finish_instru/finish_ite.o finish_instru/finish_ite.c

${OBJECTDIR}/finish_instru/instru_utili.o: finish_instru/instru_utili.c
	${MKDIR} -p ${OBJECTDIR}/finish_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/finish_instru/instru_utili.o finish_instru/instru_utili.c

${OBJECTDIR}/finish_instru/print_strea.o: finish_instru/print_strea.c
	${MKDIR} -p ${OBJECTDIR}/finish_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/finish_instru/print_strea.o finish_instru/print_strea.c

${OBJECTDIR}/finish_instru/tokit_utili.o: finish_instru/tokit_utili.c
	${MKDIR} -p ${OBJECTDIR}/finish_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/finish_instru/tokit_utili.o finish_instru/tokit_utili.c

${OBJECTDIR}/instru_execute/execut_instru.o: instru_execute/execut_instru.c
	${MKDIR} -p ${OBJECTDIR}/instru_execute
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/instru_execute/execut_instru.o instru_execute/execut_instru.c

${OBJECTDIR}/instru_execute/execute_ite.o: instru_execute/execute_ite.c
	${MKDIR} -p ${OBJECTDIR}/instru_execute
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/instru_execute/execute_ite.o instru_execute/execute_ite.c

${OBJECTDIR}/options.o: options.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/options.o options.c

${OBJECTDIR}/osev_clit.o: osev_clit.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osev_clit.o osev_clit.c

${OBJECTDIR}/osvp_utili.o: osvp_utili.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osvp_utili.o osvp_utili.c

${OBJECTDIR}/parse_resxml.o: parse_resxml.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parse_resxml.o parse_resxml.c

${OBJECTDIR}/parse_valida/conve_lvikoi.o: parse_valida/conve_lvikoi.c
	${MKDIR} -p ${OBJECTDIR}/parse_valida
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parse_valida/conve_lvikoi.o parse_valida/conve_lvikoi.c

${OBJECTDIR}/parse_valida/filli_conve.o: parse_valida/filli_conve.c
	${MKDIR} -p ${OBJECTDIR}/parse_valida
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parse_valida/filli_conve.o parse_valida/filli_conve.c

${OBJECTDIR}/parse_valida/later_check.o: parse_valida/later_check.c
	${MKDIR} -p ${OBJECTDIR}/parse_valida
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parse_valida/later_check.o parse_valida/later_check.c

${OBJECTDIR}/parse_valida/parse_ilevoi.o: parse_valida/parse_ilevoi.c
	${MKDIR} -p ${OBJECTDIR}/parse_valida
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parse_valida/parse_ilevoi.o parse_valida/parse_ilevoi.c

${OBJECTDIR}/parse_valida/parse_klevoi.o: parse_valida/parse_klevoi.c
	${MKDIR} -p ${OBJECTDIR}/parse_valida
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parse_valida/parse_klevoi.o parse_valida/parse_klevoi.c

${OBJECTDIR}/parse_valida/parse_levivk.o: parse_valida/parse_levivk.c
	${MKDIR} -p ${OBJECTDIR}/parse_valida
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parse_valida/parse_levivk.o parse_valida/parse_levivk.c

${OBJECTDIR}/parse_valida/pretr_check.o: parse_valida/pretr_check.c
	${MKDIR} -p ${OBJECTDIR}/parse_valida
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parse_valida/pretr_check.o parse_valida/pretr_check.c

${OBJECTDIR}/parse_valida/split_pamvs.o: parse_valida/split_pamvs.c
	${MKDIR} -p ${OBJECTDIR}/parse_valida
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parse_valida/split_pamvs.o parse_valida/split_pamvs.c

${OBJECTDIR}/parse_valida/split_space.o: parse_valida/split_space.c
	${MKDIR} -p ${OBJECTDIR}/parse_valida
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parse_valida/split_space.o parse_valida/split_space.c

${OBJECTDIR}/parse_valida/valida_ite.o: parse_valida/valida_ite.c
	${MKDIR} -p ${OBJECTDIR}/parse_valida
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parse_valida/valida_ite.o parse_valida/valida_ite.c

${OBJECTDIR}/pretr_instru/cont_name_obid.o: pretr_instru/cont_name_obid.c
	${MKDIR} -p ${OBJECTDIR}/pretr_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pretr_instru/cont_name_obid.o pretr_instru/cont_name_obid.c

${OBJECTDIR}/pretr_instru/conve_utili.o: pretr_instru/conve_utili.c
	${MKDIR} -p ${OBJECTDIR}/pretr_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pretr_instru/conve_utili.o pretr_instru/conve_utili.c

${OBJECTDIR}/pretr_instru/defau_utili.o: pretr_instru/defau_utili.c
	${MKDIR} -p ${OBJECTDIR}/pretr_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pretr_instru/defau_utili.o pretr_instru/defau_utili.c

${OBJECTDIR}/pretr_instru/instr_pretr.o: pretr_instru/instr_pretr.c
	${MKDIR} -p ${OBJECTDIR}/pretr_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pretr_instru/instr_pretr.o pretr_instru/instr_pretr.c

${OBJECTDIR}/pretr_instru/instru.o: pretr_instru/instru.c
	${MKDIR} -p ${OBJECTDIR}/pretr_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pretr_instru/instru.o pretr_instru/instru.c

${OBJECTDIR}/pretr_instru/post_inner_valu.o: pretr_instru/post_inner_valu.c
	${MKDIR} -p ${OBJECTDIR}/pretr_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pretr_instru/post_inner_valu.o pretr_instru/post_inner_valu.c

${OBJECTDIR}/pretr_instru/pre_instru_ite.o: pretr_instru/pre_instru_ite.c
	${MKDIR} -p ${OBJECTDIR}/pretr_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pretr_instru/pre_instru_ite.o pretr_instru/pre_instru_ite.c

${OBJECTDIR}/pretr_instru/repla_inner_valu.o: pretr_instru/repla_inner_valu.c
	${MKDIR} -p ${OBJECTDIR}/pretr_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pretr_instru/repla_inner_valu.o pretr_instru/repla_inner_valu.c

${OBJECTDIR}/pretr_instru/statu_inner_valu.o: pretr_instru/statu_inner_valu.c
	${MKDIR} -p ${OBJECTDIR}/pretr_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pretr_instru/statu_inner_valu.o pretr_instru/statu_inner_valu.c

${OBJECTDIR}/pretr_instru/valid_logic.o: pretr_instru/valid_logic.c
	${MKDIR} -p ${OBJECTDIR}/pretr_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pretr_instru/valid_logic.o pretr_instru/valid_logic.c

${OBJECTDIR}/pretr_prompt/prompt_ite.o: pretr_prompt/prompt_ite.c
	${MKDIR} -p ${OBJECTDIR}/pretr_prompt
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pretr_prompt/prompt_ite.o pretr_prompt/prompt_ite.c

${OBJECTDIR}/pretr_prompt/prompt_utili.o: pretr_prompt/prompt_utili.c
	${MKDIR} -p ${OBJECTDIR}/pretr_prompt
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pretr_prompt/prompt_utili.o pretr_prompt/prompt_utili.c

${OBJECTDIR}/privi_utili.o: privi_utili.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/privi_utili.o privi_utili.c

${OBJECTDIR}/tokit_instru/common/ccomm_types.o: tokit_instru/common/ccomm_types.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/common
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/common/ccomm_types.o tokit_instru/common/ccomm_types.c

${OBJECTDIR}/tokit_instru/execu_tokit_ite.o: tokit_instru/execu_tokit_ite.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/execu_tokit_ite.o tokit_instru/execu_tokit_ite.c

${OBJECTDIR}/tokit_instru/explain.o: tokit_instru/explain.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/explain.o tokit_instru/explain.c

${OBJECTDIR}/tokit_instru/fmt_lang/fmt_binoid.o: tokit_instru/fmt_lang/fmt_binoid.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/fmt_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/fmt_lang/fmt_binoid.o tokit_instru/fmt_lang/fmt_binoid.c

${OBJECTDIR}/tokit_instru/fmt_lang/fmt_xmlang.o: tokit_instru/fmt_lang/fmt_xmlang.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/fmt_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/fmt_lang/fmt_xmlang.o tokit_instru/fmt_lang/fmt_xmlang.c

${OBJECTDIR}/tokit_instru/format.o: tokit_instru/format.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/format.o tokit_instru/format.c

${OBJECTDIR}/tokit_instru/key_valu.o: tokit_instru/key_valu.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/key_valu.o tokit_instru/key_valu.c

${OBJECTDIR}/tokit_instru/kstri_utili.o: tokit_instru/kstri_utili.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/kstri_utili.o tokit_instru/kstri_utili.c

${OBJECTDIR}/tokit_instru/list.o: tokit_instru/list.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/list.o tokit_instru/list.c

${OBJECTDIR}/tokit_instru/load.o: tokit_instru/load.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/load.o tokit_instru/load.c

${OBJECTDIR}/tokit_instru/lvtp_explain/explain_ite.o: tokit_instru/lvtp_explain/explain_ite.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/lvtp_explain
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/lvtp_explain/explain_ite.o tokit_instru/lvtp_explain/explain_ite.c

${OBJECTDIR}/tokit_instru/parse_list/klist_ite.o: tokit_instru/parse_list/klist_ite.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/parse_list
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/parse_list/klist_ite.o tokit_instru/parse_list/klist_ite.c

${OBJECTDIR}/tokit_instru/parse_list/parse_lev1.o: tokit_instru/parse_list/parse_lev1.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/parse_list
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/parse_list/parse_lev1.o tokit_instru/parse_list/parse_lev1.c

${OBJECTDIR}/tokit_instru/pretty.o: tokit_instru/pretty.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/pretty.o tokit_instru/pretty.c

${OBJECTDIR}/tokit_instru/pretty_utili/pretty_ite.o: tokit_instru/pretty_utili/pretty_ite.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/pretty_utili
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/pretty_utili/pretty_ite.o tokit_instru/pretty_utili/pretty_ite.c

${OBJECTDIR}/tokit_instru/save.o: tokit_instru/save.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/save.o tokit_instru/save.c

${OBJECTDIR}/tokit_instru/trans_lang/filli_clang.o: tokit_instru/trans_lang/filli_clang.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/trans_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/trans_lang/filli_clang.o tokit_instru/trans_lang/filli_clang.c

${OBJECTDIR}/tokit_instru/trans_lang/lev1_utili.o: tokit_instru/trans_lang/lev1_utili.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/trans_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/trans_lang/lev1_utili.o tokit_instru/trans_lang/lev1_utili.c

${OBJECTDIR}/tokit_instru/trans_lang/load_conte.o: tokit_instru/trans_lang/load_conte.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/trans_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/trans_lang/load_conte.o tokit_instru/trans_lang/load_conte.c

${OBJECTDIR}/tokit_instru/trans_lang/lv2p_expan.o: tokit_instru/trans_lang/lv2p_expan.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/trans_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/trans_lang/lv2p_expan.o tokit_instru/trans_lang/lv2p_expan.c

${OBJECTDIR}/tokit_instru/trans_lang/lv2p_list.o: tokit_instru/trans_lang/lv2p_list.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/trans_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/trans_lang/lv2p_list.o tokit_instru/trans_lang/lv2p_list.c

${OBJECTDIR}/tokit_instru/trans_lang/parse_expand.o: tokit_instru/trans_lang/parse_expand.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/trans_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/trans_lang/parse_expand.o tokit_instru/trans_lang/parse_expand.c

${OBJECTDIR}/tokit_instru/trans_lang/parse_l12con.o: tokit_instru/trans_lang/parse_l12con.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/trans_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/trans_lang/parse_l12con.o tokit_instru/trans_lang/parse_l12con.c

${OBJECTDIR}/tokit_instru/trans_lang/parse_lv2p_atti.o: tokit_instru/trans_lang/parse_lv2p_atti.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/trans_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/trans_lang/parse_lv2p_atti.o tokit_instru/trans_lang/parse_lv2p_atti.c

${OBJECTDIR}/tokit_instru/trans_lang/seri_leng.o: tokit_instru/trans_lang/seri_leng.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/trans_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/trans_lang/seri_leng.o tokit_instru/trans_lang/seri_leng.c

${OBJECTDIR}/tokit_instru/trans_lang/tran_gcc_cpp.o: tokit_instru/trans_lang/tran_gcc_cpp.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/trans_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/trans_lang/tran_gcc_cpp.o tokit_instru/trans_lang/tran_gcc_cpp.c

${OBJECTDIR}/tokit_instru/trans_lang/trans_utili.o: tokit_instru/trans_lang/trans_utili.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/trans_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/trans_lang/trans_utili.o tokit_instru/trans_lang/trans_utili.c

${OBJECTDIR}/tokit_instru/trans_lang/translate.o: tokit_instru/trans_lang/translate.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/trans_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/trans_lang/translate.o tokit_instru/trans_lang/translate.c

${OBJECTDIR}/tokit_instru/trans_lang/tstri_utili.o: tokit_instru/trans_lang/tstri_utili.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/trans_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/trans_lang/tstri_utili.o tokit_instru/trans_lang/tstri_utili.c

${OBJECTDIR}/tokit_instru/translate.o: tokit_instru/translate.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/translate.o tokit_instru/translate.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
