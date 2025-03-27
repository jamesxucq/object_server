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
	${OBJECTDIR}/cli_bzl.o \
	${OBJECTDIR}/cli_obje.o \
	${OBJECTDIR}/cli_struct.o \
	${OBJECTDIR}/clien_statu.o \
	${OBJECTDIR}/connect.o \
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
	${OBJECTDIR}/osev_cli.o \
	${OBJECTDIR}/osvp_utili.o \
	${OBJECTDIR}/parse_resxml.o \
	${OBJECTDIR}/parse_valida/conve_lvikoi.o \
	${OBJECTDIR}/parse_valida/filli_conve.o \
	${OBJECTDIR}/parse_valida/parse_ilevoi.o \
	${OBJECTDIR}/parse_valida/parse_klevoi.o \
	${OBJECTDIR}/parse_valida/parse_levivk.o \
	${OBJECTDIR}/parse_valida/pretr_check.o \
	${OBJECTDIR}/parse_valida/split_pamvs.o \
	${OBJECTDIR}/parse_valida/valida_ite.o \
	${OBJECTDIR}/pretr_instru/cont_name_obid.o \
	${OBJECTDIR}/pretr_instru/conve_utili.o \
	${OBJECTDIR}/pretr_instru/defau_utili.o \
	${OBJECTDIR}/pretr_instru/instr_pretr.o \
	${OBJECTDIR}/pretr_instru/instru.o \
	${OBJECTDIR}/pretr_instru/post_inner_valu.o \
	${OBJECTDIR}/pretr_instru/pre_instru_ite.o \
	${OBJECTDIR}/pretr_instru/valid_logic.o \
	${OBJECTDIR}/pretr_prompt/prompt_ite.o \
	${OBJECTDIR}/pretr_prompt/prompt_utili.o \
	${OBJECTDIR}/privi_utili.o \
	${OBJECTDIR}/tokit_instru/common/ccomm_types.o \
	${OBJECTDIR}/tokit_instru/conve.o \
	${OBJECTDIR}/tokit_instru/conve_lang/conv_gcc_cpp.o \
	${OBJECTDIR}/tokit_instru/conve_lang/conve_utili.o \
	${OBJECTDIR}/tokit_instru/conve_lang/conver.o \
	${OBJECTDIR}/tokit_instru/conve_lang/cstri_utili.o \
	${OBJECTDIR}/tokit_instru/conve_lang/filli_clang.o \
	${OBJECTDIR}/tokit_instru/conve_lang/lev1_utili.o \
	${OBJECTDIR}/tokit_instru/conve_lang/load_conte.o \
	${OBJECTDIR}/tokit_instru/conve_lang/lv2p_expan.o \
	${OBJECTDIR}/tokit_instru/conve_lang/lv2p_list.o \
	${OBJECTDIR}/tokit_instru/conve_lang/parse_expand.o \
	${OBJECTDIR}/tokit_instru/conve_lang/parse_l12con.o \
	${OBJECTDIR}/tokit_instru/conve_lang/parse_lv2p_atti.o \
	${OBJECTDIR}/tokit_instru/conve_lang/seri_leng.o \
	${OBJECTDIR}/tokit_instru/execu_tokit_ite.o \
	${OBJECTDIR}/tokit_instru/expand.o \
	${OBJECTDIR}/tokit_instru/fmt_lang/fmt_binoid.o \
	${OBJECTDIR}/tokit_instru/fmt_lang/fmt_xmlang.o \
	${OBJECTDIR}/tokit_instru/format.o \
	${OBJECTDIR}/tokit_instru/key_valu.o \
	${OBJECTDIR}/tokit_instru/kstri_utili.o \
	${OBJECTDIR}/tokit_instru/list.o \
	${OBJECTDIR}/tokit_instru/load.o \
	${OBJECTDIR}/tokit_instru/lvtp_expand/expand_ite.o \
	${OBJECTDIR}/tokit_instru/parse_list/klist_ite.o \
	${OBJECTDIR}/tokit_instru/parse_list/parse_lev1.o \
	${OBJECTDIR}/tokit_instru/pretty.o \
	${OBJECTDIR}/tokit_instru/pretty_utili/pretty_ite.o \
	${OBJECTDIR}/tokit_instru/save.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/modetest.o \
	${TESTDIR}/tests/objetest.o

# C Compiler Flags
CFLAGS=-Wall -D_DEBUG -D_OSEV_CLI -D_LARGEFILE64_SOURCE -D_FILEOFFSET_BITS==64 -fno-strict-aliasing -Wno-maybe-uninitialized -O2

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
	gcc -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/osev-cli ${OBJECTFILES} ${LDLIBSOPTIONS} ../../client/clang/osev_clie_clang/dist/Debug/GNU-Linux/libosev_clie_clang.a ../third_party/packing/libpacking.a -lpthread -ldl -lmbedcrypto

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

${OBJECTDIR}/cli_bzl.o: cli_bzl.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cli_bzl.o cli_bzl.c

${OBJECTDIR}/cli_obje.o: cli_obje.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cli_obje.o cli_obje.c

${OBJECTDIR}/cli_struct.o: cli_struct.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cli_struct.o cli_struct.c

${OBJECTDIR}/clien_statu.o: clien_statu.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clien_statu.o clien_statu.c

${OBJECTDIR}/connect.o: connect.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/connect.o connect.c

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

${OBJECTDIR}/osev_cli.o: osev_cli.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osev_cli.o osev_cli.c

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

${OBJECTDIR}/tokit_instru/conve.o: tokit_instru/conve.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve.o tokit_instru/conve.c

${OBJECTDIR}/tokit_instru/conve_lang/conv_gcc_cpp.o: tokit_instru/conve_lang/conv_gcc_cpp.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/conve_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_lang/conv_gcc_cpp.o tokit_instru/conve_lang/conv_gcc_cpp.c

${OBJECTDIR}/tokit_instru/conve_lang/conve_utili.o: tokit_instru/conve_lang/conve_utili.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/conve_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_lang/conve_utili.o tokit_instru/conve_lang/conve_utili.c

${OBJECTDIR}/tokit_instru/conve_lang/conver.o: tokit_instru/conve_lang/conver.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/conve_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_lang/conver.o tokit_instru/conve_lang/conver.c

${OBJECTDIR}/tokit_instru/conve_lang/cstri_utili.o: tokit_instru/conve_lang/cstri_utili.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/conve_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_lang/cstri_utili.o tokit_instru/conve_lang/cstri_utili.c

${OBJECTDIR}/tokit_instru/conve_lang/filli_clang.o: tokit_instru/conve_lang/filli_clang.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/conve_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_lang/filli_clang.o tokit_instru/conve_lang/filli_clang.c

${OBJECTDIR}/tokit_instru/conve_lang/lev1_utili.o: tokit_instru/conve_lang/lev1_utili.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/conve_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_lang/lev1_utili.o tokit_instru/conve_lang/lev1_utili.c

${OBJECTDIR}/tokit_instru/conve_lang/load_conte.o: tokit_instru/conve_lang/load_conte.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/conve_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_lang/load_conte.o tokit_instru/conve_lang/load_conte.c

${OBJECTDIR}/tokit_instru/conve_lang/lv2p_expan.o: tokit_instru/conve_lang/lv2p_expan.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/conve_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_lang/lv2p_expan.o tokit_instru/conve_lang/lv2p_expan.c

${OBJECTDIR}/tokit_instru/conve_lang/lv2p_list.o: tokit_instru/conve_lang/lv2p_list.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/conve_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_lang/lv2p_list.o tokit_instru/conve_lang/lv2p_list.c

${OBJECTDIR}/tokit_instru/conve_lang/parse_expand.o: tokit_instru/conve_lang/parse_expand.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/conve_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_lang/parse_expand.o tokit_instru/conve_lang/parse_expand.c

${OBJECTDIR}/tokit_instru/conve_lang/parse_l12con.o: tokit_instru/conve_lang/parse_l12con.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/conve_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_lang/parse_l12con.o tokit_instru/conve_lang/parse_l12con.c

${OBJECTDIR}/tokit_instru/conve_lang/parse_lv2p_atti.o: tokit_instru/conve_lang/parse_lv2p_atti.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/conve_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_lang/parse_lv2p_atti.o tokit_instru/conve_lang/parse_lv2p_atti.c

${OBJECTDIR}/tokit_instru/conve_lang/seri_leng.o: tokit_instru/conve_lang/seri_leng.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/conve_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_lang/seri_leng.o tokit_instru/conve_lang/seri_leng.c

${OBJECTDIR}/tokit_instru/execu_tokit_ite.o: tokit_instru/execu_tokit_ite.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/execu_tokit_ite.o tokit_instru/execu_tokit_ite.c

${OBJECTDIR}/tokit_instru/expand.o: tokit_instru/expand.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/expand.o tokit_instru/expand.c

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

${OBJECTDIR}/tokit_instru/lvtp_expand/expand_ite.o: tokit_instru/lvtp_expand/expand_ite.c
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/lvtp_expand
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/lvtp_expand/expand_ite.o tokit_instru/lvtp_expand/expand_ite.c

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

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/modetest.o ${TESTDIR}/tests/objetest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   


${TESTDIR}/tests/modetest.o: tests/modetest.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/modetest.o tests/modetest.c


${TESTDIR}/tests/objetest.o: tests/objetest.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/objetest.o tests/objetest.c


${OBJECTDIR}/_ext/d8a3b606/modoid_nomain.o: ${OBJECTDIR}/_ext/d8a3b606/modoid.o ../osev_common/modoid.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/d8a3b606
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/d8a3b606/modoid.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8a3b606/modoid_nomain.o ../osev_common/modoid.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/d8a3b606/modoid.o ${OBJECTDIR}/_ext/d8a3b606/modoid_nomain.o;\
	fi

${OBJECTDIR}/_ext/d8a3b606/obid_nomain.o: ${OBJECTDIR}/_ext/d8a3b606/obid.o ../osev_common/obid.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/d8a3b606
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/d8a3b606/obid.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8a3b606/obid_nomain.o ../osev_common/obid.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/d8a3b606/obid.o ${OBJECTDIR}/_ext/d8a3b606/obid_nomain.o;\
	fi

${OBJECTDIR}/_ext/d8a3b606/pamstyl_utili_nomain.o: ${OBJECTDIR}/_ext/d8a3b606/pamstyl_utili.o ../osev_common/pamstyl_utili.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/d8a3b606
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/d8a3b606/pamstyl_utili.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8a3b606/pamstyl_utili_nomain.o ../osev_common/pamstyl_utili.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/d8a3b606/pamstyl_utili.o ${OBJECTDIR}/_ext/d8a3b606/pamstyl_utili_nomain.o;\
	fi

${OBJECTDIR}/_ext/d8a3b606/stoid_nomain.o: ${OBJECTDIR}/_ext/d8a3b606/stoid.o ../osev_common/stoid.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/d8a3b606
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/d8a3b606/stoid.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8a3b606/stoid_nomain.o ../osev_common/stoid.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/d8a3b606/stoid.o ${OBJECTDIR}/_ext/d8a3b606/stoid_nomain.o;\
	fi

${OBJECTDIR}/_ext/d8a3b606/xml_utili_nomain.o: ${OBJECTDIR}/_ext/d8a3b606/xml_utili.o ../osev_common/xml_utili.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/d8a3b606
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/d8a3b606/xml_utili.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8a3b606/xml_utili_nomain.o ../osev_common/xml_utili.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/d8a3b606/xml_utili.o ${OBJECTDIR}/_ext/d8a3b606/xml_utili_nomain.o;\
	fi

${OBJECTDIR}/_ext/f534dc3f/binary_logger_nomain.o: ${OBJECTDIR}/_ext/f534dc3f/binary_logger.o ../third_party/binary_logger.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/f534dc3f
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/f534dc3f/binary_logger.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/f534dc3f/binary_logger_nomain.o ../third_party/binary_logger.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/f534dc3f/binary_logger.o ${OBJECTDIR}/_ext/f534dc3f/binary_logger_nomain.o;\
	fi

${OBJECTDIR}/_ext/f534dc3f/linenoise_nomain.o: ${OBJECTDIR}/_ext/f534dc3f/linenoise.o ../third_party/linenoise.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/f534dc3f
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/f534dc3f/linenoise.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/f534dc3f/linenoise_nomain.o ../third_party/linenoise.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/f534dc3f/linenoise.o ${OBJECTDIR}/_ext/f534dc3f/linenoise_nomain.o;\
	fi

${OBJECTDIR}/cinstru_nomain.o: ${OBJECTDIR}/cinstru.o cinstru.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cinstru.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cinstru_nomain.o cinstru.c;\
	else  \
	    ${CP} ${OBJECTDIR}/cinstru.o ${OBJECTDIR}/cinstru_nomain.o;\
	fi

${OBJECTDIR}/cli_bzl_nomain.o: ${OBJECTDIR}/cli_bzl.o cli_bzl.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cli_bzl.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cli_bzl_nomain.o cli_bzl.c;\
	else  \
	    ${CP} ${OBJECTDIR}/cli_bzl.o ${OBJECTDIR}/cli_bzl_nomain.o;\
	fi

${OBJECTDIR}/cli_obje_nomain.o: ${OBJECTDIR}/cli_obje.o cli_obje.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cli_obje.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cli_obje_nomain.o cli_obje.c;\
	else  \
	    ${CP} ${OBJECTDIR}/cli_obje.o ${OBJECTDIR}/cli_obje_nomain.o;\
	fi

${OBJECTDIR}/cli_struct_nomain.o: ${OBJECTDIR}/cli_struct.o cli_struct.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cli_struct.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cli_struct_nomain.o cli_struct.c;\
	else  \
	    ${CP} ${OBJECTDIR}/cli_struct.o ${OBJECTDIR}/cli_struct_nomain.o;\
	fi

${OBJECTDIR}/clien_statu_nomain.o: ${OBJECTDIR}/clien_statu.o clien_statu.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/clien_statu.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clien_statu_nomain.o clien_statu.c;\
	else  \
	    ${CP} ${OBJECTDIR}/clien_statu.o ${OBJECTDIR}/clien_statu_nomain.o;\
	fi

${OBJECTDIR}/connect_nomain.o: ${OBJECTDIR}/connect.o connect.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/connect.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/connect_nomain.o connect.c;\
	else  \
	    ${CP} ${OBJECTDIR}/connect.o ${OBJECTDIR}/connect_nomain.o;\
	fi

${OBJECTDIR}/cstri_utili_nomain.o: ${OBJECTDIR}/cstri_utili.o cstri_utili.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cstri_utili.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cstri_utili_nomain.o cstri_utili.c;\
	else  \
	    ${CP} ${OBJECTDIR}/cstri_utili.o ${OBJECTDIR}/cstri_utili_nomain.o;\
	fi

${OBJECTDIR}/debug_funct_sh_nomain.o: ${OBJECTDIR}/debug_funct_sh.o debug_funct_sh.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/debug_funct_sh.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/debug_funct_sh_nomain.o debug_funct_sh.c;\
	else  \
	    ${CP} ${OBJECTDIR}/debug_funct_sh.o ${OBJECTDIR}/debug_funct_sh_nomain.o;\
	fi

${OBJECTDIR}/finish_cline/cline_valid_ite_nomain.o: ${OBJECTDIR}/finish_cline/cline_valid_ite.o finish_cline/cline_valid_ite.c 
	${MKDIR} -p ${OBJECTDIR}/finish_cline
	@NMOUTPUT=`${NM} ${OBJECTDIR}/finish_cline/cline_valid_ite.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/finish_cline/cline_valid_ite_nomain.o finish_cline/cline_valid_ite.c;\
	else  \
	    ${CP} ${OBJECTDIR}/finish_cline/cline_valid_ite.o ${OBJECTDIR}/finish_cline/cline_valid_ite_nomain.o;\
	fi

${OBJECTDIR}/finish_cline/parse_cline_nomain.o: ${OBJECTDIR}/finish_cline/parse_cline.o finish_cline/parse_cline.c 
	${MKDIR} -p ${OBJECTDIR}/finish_cline
	@NMOUTPUT=`${NM} ${OBJECTDIR}/finish_cline/parse_cline.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/finish_cline/parse_cline_nomain.o finish_cline/parse_cline.c;\
	else  \
	    ${CP} ${OBJECTDIR}/finish_cline/parse_cline.o ${OBJECTDIR}/finish_cline/parse_cline_nomain.o;\
	fi

${OBJECTDIR}/finish_instru/finis_instru_nomain.o: ${OBJECTDIR}/finish_instru/finis_instru.o finish_instru/finis_instru.c 
	${MKDIR} -p ${OBJECTDIR}/finish_instru
	@NMOUTPUT=`${NM} ${OBJECTDIR}/finish_instru/finis_instru.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/finish_instru/finis_instru_nomain.o finish_instru/finis_instru.c;\
	else  \
	    ${CP} ${OBJECTDIR}/finish_instru/finis_instru.o ${OBJECTDIR}/finish_instru/finis_instru_nomain.o;\
	fi

${OBJECTDIR}/finish_instru/finis_tolkit_nomain.o: ${OBJECTDIR}/finish_instru/finis_tolkit.o finish_instru/finis_tolkit.c 
	${MKDIR} -p ${OBJECTDIR}/finish_instru
	@NMOUTPUT=`${NM} ${OBJECTDIR}/finish_instru/finis_tolkit.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/finish_instru/finis_tolkit_nomain.o finish_instru/finis_tolkit.c;\
	else  \
	    ${CP} ${OBJECTDIR}/finish_instru/finis_tolkit.o ${OBJECTDIR}/finish_instru/finis_tolkit_nomain.o;\
	fi

${OBJECTDIR}/finish_instru/finish_ite_nomain.o: ${OBJECTDIR}/finish_instru/finish_ite.o finish_instru/finish_ite.c 
	${MKDIR} -p ${OBJECTDIR}/finish_instru
	@NMOUTPUT=`${NM} ${OBJECTDIR}/finish_instru/finish_ite.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/finish_instru/finish_ite_nomain.o finish_instru/finish_ite.c;\
	else  \
	    ${CP} ${OBJECTDIR}/finish_instru/finish_ite.o ${OBJECTDIR}/finish_instru/finish_ite_nomain.o;\
	fi

${OBJECTDIR}/finish_instru/instru_utili_nomain.o: ${OBJECTDIR}/finish_instru/instru_utili.o finish_instru/instru_utili.c 
	${MKDIR} -p ${OBJECTDIR}/finish_instru
	@NMOUTPUT=`${NM} ${OBJECTDIR}/finish_instru/instru_utili.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/finish_instru/instru_utili_nomain.o finish_instru/instru_utili.c;\
	else  \
	    ${CP} ${OBJECTDIR}/finish_instru/instru_utili.o ${OBJECTDIR}/finish_instru/instru_utili_nomain.o;\
	fi

${OBJECTDIR}/finish_instru/print_strea_nomain.o: ${OBJECTDIR}/finish_instru/print_strea.o finish_instru/print_strea.c 
	${MKDIR} -p ${OBJECTDIR}/finish_instru
	@NMOUTPUT=`${NM} ${OBJECTDIR}/finish_instru/print_strea.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/finish_instru/print_strea_nomain.o finish_instru/print_strea.c;\
	else  \
	    ${CP} ${OBJECTDIR}/finish_instru/print_strea.o ${OBJECTDIR}/finish_instru/print_strea_nomain.o;\
	fi

${OBJECTDIR}/finish_instru/tokit_utili_nomain.o: ${OBJECTDIR}/finish_instru/tokit_utili.o finish_instru/tokit_utili.c 
	${MKDIR} -p ${OBJECTDIR}/finish_instru
	@NMOUTPUT=`${NM} ${OBJECTDIR}/finish_instru/tokit_utili.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/finish_instru/tokit_utili_nomain.o finish_instru/tokit_utili.c;\
	else  \
	    ${CP} ${OBJECTDIR}/finish_instru/tokit_utili.o ${OBJECTDIR}/finish_instru/tokit_utili_nomain.o;\
	fi

${OBJECTDIR}/instru_execute/execut_instru_nomain.o: ${OBJECTDIR}/instru_execute/execut_instru.o instru_execute/execut_instru.c 
	${MKDIR} -p ${OBJECTDIR}/instru_execute
	@NMOUTPUT=`${NM} ${OBJECTDIR}/instru_execute/execut_instru.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/instru_execute/execut_instru_nomain.o instru_execute/execut_instru.c;\
	else  \
	    ${CP} ${OBJECTDIR}/instru_execute/execut_instru.o ${OBJECTDIR}/instru_execute/execut_instru_nomain.o;\
	fi

${OBJECTDIR}/instru_execute/execute_ite_nomain.o: ${OBJECTDIR}/instru_execute/execute_ite.o instru_execute/execute_ite.c 
	${MKDIR} -p ${OBJECTDIR}/instru_execute
	@NMOUTPUT=`${NM} ${OBJECTDIR}/instru_execute/execute_ite.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/instru_execute/execute_ite_nomain.o instru_execute/execute_ite.c;\
	else  \
	    ${CP} ${OBJECTDIR}/instru_execute/execute_ite.o ${OBJECTDIR}/instru_execute/execute_ite_nomain.o;\
	fi

${OBJECTDIR}/options_nomain.o: ${OBJECTDIR}/options.o options.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/options.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/options_nomain.o options.c;\
	else  \
	    ${CP} ${OBJECTDIR}/options.o ${OBJECTDIR}/options_nomain.o;\
	fi

${OBJECTDIR}/osev_cli_nomain.o: ${OBJECTDIR}/osev_cli.o osev_cli.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/osev_cli.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osev_cli_nomain.o osev_cli.c;\
	else  \
	    ${CP} ${OBJECTDIR}/osev_cli.o ${OBJECTDIR}/osev_cli_nomain.o;\
	fi

${OBJECTDIR}/osvp_utili_nomain.o: ${OBJECTDIR}/osvp_utili.o osvp_utili.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/osvp_utili.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osvp_utili_nomain.o osvp_utili.c;\
	else  \
	    ${CP} ${OBJECTDIR}/osvp_utili.o ${OBJECTDIR}/osvp_utili_nomain.o;\
	fi

${OBJECTDIR}/parse_resxml_nomain.o: ${OBJECTDIR}/parse_resxml.o parse_resxml.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/parse_resxml.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parse_resxml_nomain.o parse_resxml.c;\
	else  \
	    ${CP} ${OBJECTDIR}/parse_resxml.o ${OBJECTDIR}/parse_resxml_nomain.o;\
	fi

${OBJECTDIR}/parse_valida/conve_lvikoi_nomain.o: ${OBJECTDIR}/parse_valida/conve_lvikoi.o parse_valida/conve_lvikoi.c 
	${MKDIR} -p ${OBJECTDIR}/parse_valida
	@NMOUTPUT=`${NM} ${OBJECTDIR}/parse_valida/conve_lvikoi.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parse_valida/conve_lvikoi_nomain.o parse_valida/conve_lvikoi.c;\
	else  \
	    ${CP} ${OBJECTDIR}/parse_valida/conve_lvikoi.o ${OBJECTDIR}/parse_valida/conve_lvikoi_nomain.o;\
	fi

${OBJECTDIR}/parse_valida/filli_conve_nomain.o: ${OBJECTDIR}/parse_valida/filli_conve.o parse_valida/filli_conve.c 
	${MKDIR} -p ${OBJECTDIR}/parse_valida
	@NMOUTPUT=`${NM} ${OBJECTDIR}/parse_valida/filli_conve.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parse_valida/filli_conve_nomain.o parse_valida/filli_conve.c;\
	else  \
	    ${CP} ${OBJECTDIR}/parse_valida/filli_conve.o ${OBJECTDIR}/parse_valida/filli_conve_nomain.o;\
	fi

${OBJECTDIR}/parse_valida/parse_ilevoi_nomain.o: ${OBJECTDIR}/parse_valida/parse_ilevoi.o parse_valida/parse_ilevoi.c 
	${MKDIR} -p ${OBJECTDIR}/parse_valida
	@NMOUTPUT=`${NM} ${OBJECTDIR}/parse_valida/parse_ilevoi.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parse_valida/parse_ilevoi_nomain.o parse_valida/parse_ilevoi.c;\
	else  \
	    ${CP} ${OBJECTDIR}/parse_valida/parse_ilevoi.o ${OBJECTDIR}/parse_valida/parse_ilevoi_nomain.o;\
	fi

${OBJECTDIR}/parse_valida/parse_klevoi_nomain.o: ${OBJECTDIR}/parse_valida/parse_klevoi.o parse_valida/parse_klevoi.c 
	${MKDIR} -p ${OBJECTDIR}/parse_valida
	@NMOUTPUT=`${NM} ${OBJECTDIR}/parse_valida/parse_klevoi.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parse_valida/parse_klevoi_nomain.o parse_valida/parse_klevoi.c;\
	else  \
	    ${CP} ${OBJECTDIR}/parse_valida/parse_klevoi.o ${OBJECTDIR}/parse_valida/parse_klevoi_nomain.o;\
	fi

${OBJECTDIR}/parse_valida/parse_levivk_nomain.o: ${OBJECTDIR}/parse_valida/parse_levivk.o parse_valida/parse_levivk.c 
	${MKDIR} -p ${OBJECTDIR}/parse_valida
	@NMOUTPUT=`${NM} ${OBJECTDIR}/parse_valida/parse_levivk.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parse_valida/parse_levivk_nomain.o parse_valida/parse_levivk.c;\
	else  \
	    ${CP} ${OBJECTDIR}/parse_valida/parse_levivk.o ${OBJECTDIR}/parse_valida/parse_levivk_nomain.o;\
	fi

${OBJECTDIR}/parse_valida/pretr_check_nomain.o: ${OBJECTDIR}/parse_valida/pretr_check.o parse_valida/pretr_check.c 
	${MKDIR} -p ${OBJECTDIR}/parse_valida
	@NMOUTPUT=`${NM} ${OBJECTDIR}/parse_valida/pretr_check.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parse_valida/pretr_check_nomain.o parse_valida/pretr_check.c;\
	else  \
	    ${CP} ${OBJECTDIR}/parse_valida/pretr_check.o ${OBJECTDIR}/parse_valida/pretr_check_nomain.o;\
	fi

${OBJECTDIR}/parse_valida/split_pamvs_nomain.o: ${OBJECTDIR}/parse_valida/split_pamvs.o parse_valida/split_pamvs.c 
	${MKDIR} -p ${OBJECTDIR}/parse_valida
	@NMOUTPUT=`${NM} ${OBJECTDIR}/parse_valida/split_pamvs.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parse_valida/split_pamvs_nomain.o parse_valida/split_pamvs.c;\
	else  \
	    ${CP} ${OBJECTDIR}/parse_valida/split_pamvs.o ${OBJECTDIR}/parse_valida/split_pamvs_nomain.o;\
	fi

${OBJECTDIR}/parse_valida/valida_ite_nomain.o: ${OBJECTDIR}/parse_valida/valida_ite.o parse_valida/valida_ite.c 
	${MKDIR} -p ${OBJECTDIR}/parse_valida
	@NMOUTPUT=`${NM} ${OBJECTDIR}/parse_valida/valida_ite.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parse_valida/valida_ite_nomain.o parse_valida/valida_ite.c;\
	else  \
	    ${CP} ${OBJECTDIR}/parse_valida/valida_ite.o ${OBJECTDIR}/parse_valida/valida_ite_nomain.o;\
	fi

${OBJECTDIR}/pretr_instru/cont_name_obid_nomain.o: ${OBJECTDIR}/pretr_instru/cont_name_obid.o pretr_instru/cont_name_obid.c 
	${MKDIR} -p ${OBJECTDIR}/pretr_instru
	@NMOUTPUT=`${NM} ${OBJECTDIR}/pretr_instru/cont_name_obid.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pretr_instru/cont_name_obid_nomain.o pretr_instru/cont_name_obid.c;\
	else  \
	    ${CP} ${OBJECTDIR}/pretr_instru/cont_name_obid.o ${OBJECTDIR}/pretr_instru/cont_name_obid_nomain.o;\
	fi

${OBJECTDIR}/pretr_instru/conve_utili_nomain.o: ${OBJECTDIR}/pretr_instru/conve_utili.o pretr_instru/conve_utili.c 
	${MKDIR} -p ${OBJECTDIR}/pretr_instru
	@NMOUTPUT=`${NM} ${OBJECTDIR}/pretr_instru/conve_utili.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pretr_instru/conve_utili_nomain.o pretr_instru/conve_utili.c;\
	else  \
	    ${CP} ${OBJECTDIR}/pretr_instru/conve_utili.o ${OBJECTDIR}/pretr_instru/conve_utili_nomain.o;\
	fi

${OBJECTDIR}/pretr_instru/defau_utili_nomain.o: ${OBJECTDIR}/pretr_instru/defau_utili.o pretr_instru/defau_utili.c 
	${MKDIR} -p ${OBJECTDIR}/pretr_instru
	@NMOUTPUT=`${NM} ${OBJECTDIR}/pretr_instru/defau_utili.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pretr_instru/defau_utili_nomain.o pretr_instru/defau_utili.c;\
	else  \
	    ${CP} ${OBJECTDIR}/pretr_instru/defau_utili.o ${OBJECTDIR}/pretr_instru/defau_utili_nomain.o;\
	fi

${OBJECTDIR}/pretr_instru/instr_pretr_nomain.o: ${OBJECTDIR}/pretr_instru/instr_pretr.o pretr_instru/instr_pretr.c 
	${MKDIR} -p ${OBJECTDIR}/pretr_instru
	@NMOUTPUT=`${NM} ${OBJECTDIR}/pretr_instru/instr_pretr.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pretr_instru/instr_pretr_nomain.o pretr_instru/instr_pretr.c;\
	else  \
	    ${CP} ${OBJECTDIR}/pretr_instru/instr_pretr.o ${OBJECTDIR}/pretr_instru/instr_pretr_nomain.o;\
	fi

${OBJECTDIR}/pretr_instru/instru_nomain.o: ${OBJECTDIR}/pretr_instru/instru.o pretr_instru/instru.c 
	${MKDIR} -p ${OBJECTDIR}/pretr_instru
	@NMOUTPUT=`${NM} ${OBJECTDIR}/pretr_instru/instru.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pretr_instru/instru_nomain.o pretr_instru/instru.c;\
	else  \
	    ${CP} ${OBJECTDIR}/pretr_instru/instru.o ${OBJECTDIR}/pretr_instru/instru_nomain.o;\
	fi

${OBJECTDIR}/pretr_instru/post_inner_valu_nomain.o: ${OBJECTDIR}/pretr_instru/post_inner_valu.o pretr_instru/post_inner_valu.c 
	${MKDIR} -p ${OBJECTDIR}/pretr_instru
	@NMOUTPUT=`${NM} ${OBJECTDIR}/pretr_instru/post_inner_valu.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pretr_instru/post_inner_valu_nomain.o pretr_instru/post_inner_valu.c;\
	else  \
	    ${CP} ${OBJECTDIR}/pretr_instru/post_inner_valu.o ${OBJECTDIR}/pretr_instru/post_inner_valu_nomain.o;\
	fi

${OBJECTDIR}/pretr_instru/pre_instru_ite_nomain.o: ${OBJECTDIR}/pretr_instru/pre_instru_ite.o pretr_instru/pre_instru_ite.c 
	${MKDIR} -p ${OBJECTDIR}/pretr_instru
	@NMOUTPUT=`${NM} ${OBJECTDIR}/pretr_instru/pre_instru_ite.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pretr_instru/pre_instru_ite_nomain.o pretr_instru/pre_instru_ite.c;\
	else  \
	    ${CP} ${OBJECTDIR}/pretr_instru/pre_instru_ite.o ${OBJECTDIR}/pretr_instru/pre_instru_ite_nomain.o;\
	fi

${OBJECTDIR}/pretr_instru/valid_logic_nomain.o: ${OBJECTDIR}/pretr_instru/valid_logic.o pretr_instru/valid_logic.c 
	${MKDIR} -p ${OBJECTDIR}/pretr_instru
	@NMOUTPUT=`${NM} ${OBJECTDIR}/pretr_instru/valid_logic.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pretr_instru/valid_logic_nomain.o pretr_instru/valid_logic.c;\
	else  \
	    ${CP} ${OBJECTDIR}/pretr_instru/valid_logic.o ${OBJECTDIR}/pretr_instru/valid_logic_nomain.o;\
	fi

${OBJECTDIR}/pretr_prompt/prompt_ite_nomain.o: ${OBJECTDIR}/pretr_prompt/prompt_ite.o pretr_prompt/prompt_ite.c 
	${MKDIR} -p ${OBJECTDIR}/pretr_prompt
	@NMOUTPUT=`${NM} ${OBJECTDIR}/pretr_prompt/prompt_ite.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pretr_prompt/prompt_ite_nomain.o pretr_prompt/prompt_ite.c;\
	else  \
	    ${CP} ${OBJECTDIR}/pretr_prompt/prompt_ite.o ${OBJECTDIR}/pretr_prompt/prompt_ite_nomain.o;\
	fi

${OBJECTDIR}/pretr_prompt/prompt_utili_nomain.o: ${OBJECTDIR}/pretr_prompt/prompt_utili.o pretr_prompt/prompt_utili.c 
	${MKDIR} -p ${OBJECTDIR}/pretr_prompt
	@NMOUTPUT=`${NM} ${OBJECTDIR}/pretr_prompt/prompt_utili.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pretr_prompt/prompt_utili_nomain.o pretr_prompt/prompt_utili.c;\
	else  \
	    ${CP} ${OBJECTDIR}/pretr_prompt/prompt_utili.o ${OBJECTDIR}/pretr_prompt/prompt_utili_nomain.o;\
	fi

${OBJECTDIR}/privi_utili_nomain.o: ${OBJECTDIR}/privi_utili.o privi_utili.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/privi_utili.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/privi_utili_nomain.o privi_utili.c;\
	else  \
	    ${CP} ${OBJECTDIR}/privi_utili.o ${OBJECTDIR}/privi_utili_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/common/ccomm_types_nomain.o: ${OBJECTDIR}/tokit_instru/common/ccomm_types.o tokit_instru/common/ccomm_types.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/common
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/common/ccomm_types.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/common/ccomm_types_nomain.o tokit_instru/common/ccomm_types.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/common/ccomm_types.o ${OBJECTDIR}/tokit_instru/common/ccomm_types_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/conve_nomain.o: ${OBJECTDIR}/tokit_instru/conve.o tokit_instru/conve.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/conve.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_nomain.o tokit_instru/conve.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/conve.o ${OBJECTDIR}/tokit_instru/conve_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/conve_lang/conv_gcc_cpp_nomain.o: ${OBJECTDIR}/tokit_instru/conve_lang/conv_gcc_cpp.o tokit_instru/conve_lang/conv_gcc_cpp.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/conve_lang
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/conve_lang/conv_gcc_cpp.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_lang/conv_gcc_cpp_nomain.o tokit_instru/conve_lang/conv_gcc_cpp.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/conve_lang/conv_gcc_cpp.o ${OBJECTDIR}/tokit_instru/conve_lang/conv_gcc_cpp_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/conve_lang/conve_utili_nomain.o: ${OBJECTDIR}/tokit_instru/conve_lang/conve_utili.o tokit_instru/conve_lang/conve_utili.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/conve_lang
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/conve_lang/conve_utili.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_lang/conve_utili_nomain.o tokit_instru/conve_lang/conve_utili.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/conve_lang/conve_utili.o ${OBJECTDIR}/tokit_instru/conve_lang/conve_utili_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/conve_lang/conver_nomain.o: ${OBJECTDIR}/tokit_instru/conve_lang/conver.o tokit_instru/conve_lang/conver.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/conve_lang
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/conve_lang/conver.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_lang/conver_nomain.o tokit_instru/conve_lang/conver.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/conve_lang/conver.o ${OBJECTDIR}/tokit_instru/conve_lang/conver_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/conve_lang/cstri_utili_nomain.o: ${OBJECTDIR}/tokit_instru/conve_lang/cstri_utili.o tokit_instru/conve_lang/cstri_utili.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/conve_lang
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/conve_lang/cstri_utili.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_lang/cstri_utili_nomain.o tokit_instru/conve_lang/cstri_utili.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/conve_lang/cstri_utili.o ${OBJECTDIR}/tokit_instru/conve_lang/cstri_utili_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/conve_lang/filli_clang_nomain.o: ${OBJECTDIR}/tokit_instru/conve_lang/filli_clang.o tokit_instru/conve_lang/filli_clang.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/conve_lang
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/conve_lang/filli_clang.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_lang/filli_clang_nomain.o tokit_instru/conve_lang/filli_clang.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/conve_lang/filli_clang.o ${OBJECTDIR}/tokit_instru/conve_lang/filli_clang_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/conve_lang/lev1_utili_nomain.o: ${OBJECTDIR}/tokit_instru/conve_lang/lev1_utili.o tokit_instru/conve_lang/lev1_utili.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/conve_lang
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/conve_lang/lev1_utili.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_lang/lev1_utili_nomain.o tokit_instru/conve_lang/lev1_utili.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/conve_lang/lev1_utili.o ${OBJECTDIR}/tokit_instru/conve_lang/lev1_utili_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/conve_lang/load_conte_nomain.o: ${OBJECTDIR}/tokit_instru/conve_lang/load_conte.o tokit_instru/conve_lang/load_conte.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/conve_lang
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/conve_lang/load_conte.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_lang/load_conte_nomain.o tokit_instru/conve_lang/load_conte.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/conve_lang/load_conte.o ${OBJECTDIR}/tokit_instru/conve_lang/load_conte_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/conve_lang/lv2p_expan_nomain.o: ${OBJECTDIR}/tokit_instru/conve_lang/lv2p_expan.o tokit_instru/conve_lang/lv2p_expan.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/conve_lang
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/conve_lang/lv2p_expan.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_lang/lv2p_expan_nomain.o tokit_instru/conve_lang/lv2p_expan.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/conve_lang/lv2p_expan.o ${OBJECTDIR}/tokit_instru/conve_lang/lv2p_expan_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/conve_lang/lv2p_list_nomain.o: ${OBJECTDIR}/tokit_instru/conve_lang/lv2p_list.o tokit_instru/conve_lang/lv2p_list.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/conve_lang
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/conve_lang/lv2p_list.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_lang/lv2p_list_nomain.o tokit_instru/conve_lang/lv2p_list.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/conve_lang/lv2p_list.o ${OBJECTDIR}/tokit_instru/conve_lang/lv2p_list_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/conve_lang/parse_expand_nomain.o: ${OBJECTDIR}/tokit_instru/conve_lang/parse_expand.o tokit_instru/conve_lang/parse_expand.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/conve_lang
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/conve_lang/parse_expand.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_lang/parse_expand_nomain.o tokit_instru/conve_lang/parse_expand.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/conve_lang/parse_expand.o ${OBJECTDIR}/tokit_instru/conve_lang/parse_expand_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/conve_lang/parse_l12con_nomain.o: ${OBJECTDIR}/tokit_instru/conve_lang/parse_l12con.o tokit_instru/conve_lang/parse_l12con.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/conve_lang
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/conve_lang/parse_l12con.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_lang/parse_l12con_nomain.o tokit_instru/conve_lang/parse_l12con.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/conve_lang/parse_l12con.o ${OBJECTDIR}/tokit_instru/conve_lang/parse_l12con_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/conve_lang/parse_lv2p_atti_nomain.o: ${OBJECTDIR}/tokit_instru/conve_lang/parse_lv2p_atti.o tokit_instru/conve_lang/parse_lv2p_atti.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/conve_lang
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/conve_lang/parse_lv2p_atti.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_lang/parse_lv2p_atti_nomain.o tokit_instru/conve_lang/parse_lv2p_atti.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/conve_lang/parse_lv2p_atti.o ${OBJECTDIR}/tokit_instru/conve_lang/parse_lv2p_atti_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/conve_lang/seri_leng_nomain.o: ${OBJECTDIR}/tokit_instru/conve_lang/seri_leng.o tokit_instru/conve_lang/seri_leng.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/conve_lang
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/conve_lang/seri_leng.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/conve_lang/seri_leng_nomain.o tokit_instru/conve_lang/seri_leng.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/conve_lang/seri_leng.o ${OBJECTDIR}/tokit_instru/conve_lang/seri_leng_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/execu_tokit_ite_nomain.o: ${OBJECTDIR}/tokit_instru/execu_tokit_ite.o tokit_instru/execu_tokit_ite.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/execu_tokit_ite.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/execu_tokit_ite_nomain.o tokit_instru/execu_tokit_ite.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/execu_tokit_ite.o ${OBJECTDIR}/tokit_instru/execu_tokit_ite_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/expand_nomain.o: ${OBJECTDIR}/tokit_instru/expand.o tokit_instru/expand.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/expand.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/expand_nomain.o tokit_instru/expand.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/expand.o ${OBJECTDIR}/tokit_instru/expand_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/fmt_lang/fmt_binoid_nomain.o: ${OBJECTDIR}/tokit_instru/fmt_lang/fmt_binoid.o tokit_instru/fmt_lang/fmt_binoid.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/fmt_lang
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/fmt_lang/fmt_binoid.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/fmt_lang/fmt_binoid_nomain.o tokit_instru/fmt_lang/fmt_binoid.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/fmt_lang/fmt_binoid.o ${OBJECTDIR}/tokit_instru/fmt_lang/fmt_binoid_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/fmt_lang/fmt_xmlang_nomain.o: ${OBJECTDIR}/tokit_instru/fmt_lang/fmt_xmlang.o tokit_instru/fmt_lang/fmt_xmlang.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/fmt_lang
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/fmt_lang/fmt_xmlang.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/fmt_lang/fmt_xmlang_nomain.o tokit_instru/fmt_lang/fmt_xmlang.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/fmt_lang/fmt_xmlang.o ${OBJECTDIR}/tokit_instru/fmt_lang/fmt_xmlang_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/format_nomain.o: ${OBJECTDIR}/tokit_instru/format.o tokit_instru/format.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/format.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/format_nomain.o tokit_instru/format.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/format.o ${OBJECTDIR}/tokit_instru/format_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/key_valu_nomain.o: ${OBJECTDIR}/tokit_instru/key_valu.o tokit_instru/key_valu.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/key_valu.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/key_valu_nomain.o tokit_instru/key_valu.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/key_valu.o ${OBJECTDIR}/tokit_instru/key_valu_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/kstri_utili_nomain.o: ${OBJECTDIR}/tokit_instru/kstri_utili.o tokit_instru/kstri_utili.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/kstri_utili.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/kstri_utili_nomain.o tokit_instru/kstri_utili.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/kstri_utili.o ${OBJECTDIR}/tokit_instru/kstri_utili_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/list_nomain.o: ${OBJECTDIR}/tokit_instru/list.o tokit_instru/list.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/list.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/list_nomain.o tokit_instru/list.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/list.o ${OBJECTDIR}/tokit_instru/list_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/load_nomain.o: ${OBJECTDIR}/tokit_instru/load.o tokit_instru/load.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/load.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/load_nomain.o tokit_instru/load.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/load.o ${OBJECTDIR}/tokit_instru/load_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/lvtp_expand/expand_ite_nomain.o: ${OBJECTDIR}/tokit_instru/lvtp_expand/expand_ite.o tokit_instru/lvtp_expand/expand_ite.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/lvtp_expand
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/lvtp_expand/expand_ite.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/lvtp_expand/expand_ite_nomain.o tokit_instru/lvtp_expand/expand_ite.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/lvtp_expand/expand_ite.o ${OBJECTDIR}/tokit_instru/lvtp_expand/expand_ite_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/parse_list/klist_ite_nomain.o: ${OBJECTDIR}/tokit_instru/parse_list/klist_ite.o tokit_instru/parse_list/klist_ite.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/parse_list
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/parse_list/klist_ite.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/parse_list/klist_ite_nomain.o tokit_instru/parse_list/klist_ite.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/parse_list/klist_ite.o ${OBJECTDIR}/tokit_instru/parse_list/klist_ite_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/parse_list/parse_lev1_nomain.o: ${OBJECTDIR}/tokit_instru/parse_list/parse_lev1.o tokit_instru/parse_list/parse_lev1.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/parse_list
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/parse_list/parse_lev1.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/parse_list/parse_lev1_nomain.o tokit_instru/parse_list/parse_lev1.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/parse_list/parse_lev1.o ${OBJECTDIR}/tokit_instru/parse_list/parse_lev1_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/pretty_nomain.o: ${OBJECTDIR}/tokit_instru/pretty.o tokit_instru/pretty.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/pretty.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/pretty_nomain.o tokit_instru/pretty.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/pretty.o ${OBJECTDIR}/tokit_instru/pretty_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/pretty_utili/pretty_ite_nomain.o: ${OBJECTDIR}/tokit_instru/pretty_utili/pretty_ite.o tokit_instru/pretty_utili/pretty_ite.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru/pretty_utili
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/pretty_utili/pretty_ite.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/pretty_utili/pretty_ite_nomain.o tokit_instru/pretty_utili/pretty_ite.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/pretty_utili/pretty_ite.o ${OBJECTDIR}/tokit_instru/pretty_utili/pretty_ite_nomain.o;\
	fi

${OBJECTDIR}/tokit_instru/save_nomain.o: ${OBJECTDIR}/tokit_instru/save.o tokit_instru/save.c 
	${MKDIR} -p ${OBJECTDIR}/tokit_instru
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tokit_instru/save.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../../client/clang/osev_clie_clang -I../third_party -I../osev_common -I../stora_engine -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tokit_instru/save_nomain.o tokit_instru/save.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tokit_instru/save.o ${OBJECTDIR}/tokit_instru/save_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
