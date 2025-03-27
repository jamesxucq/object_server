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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/f534dc3f/access_log.o \
	${OBJECTDIR}/debug_funct_os.o \
	${OBJECTDIR}/epoll_serv.o \
	${OBJECTDIR}/evd_list.o \
	${OBJECTDIR}/options.o \
	${OBJECTDIR}/osev_bzl.o \
	${OBJECTDIR}/osev_obje.o \
	${OBJECTDIR}/osev_serv.o \
	${OBJECTDIR}/parse_conf.o \
	${OBJECTDIR}/process/exceptio.o \
	${OBJECTDIR}/process/final_base.o \
	${OBJECTDIR}/process/final_collect.o \
	${OBJECTDIR}/process/final_constr.o \
	${OBJECTDIR}/process/final_invoke.o \
	${OBJECTDIR}/process/final_osev.o \
	${OBJECTDIR}/process/final_query.o \
	${OBJECTDIR}/process/finalize.o \
	${OBJECTDIR}/process/hand_binary.o \
	${OBJECTDIR}/process/initi_base.o \
	${OBJECTDIR}/process/initi_collect.o \
	${OBJECTDIR}/process/initi_constr.o \
	${OBJECTDIR}/process/initi_invoke.o \
	${OBJECTDIR}/process/initi_osev.o \
	${OBJECTDIR}/process/initi_query.o \
	${OBJECTDIR}/process/initi_utili.o \
	${OBJECTDIR}/process/initialize.o \
	${OBJECTDIR}/process_cycle.o \
	${OBJECTDIR}/seion_utili.o \
	${OBJECTDIR}/session.o


# C Compiler Flags
CFLAGS=-Wall -D_OSEV_SERV -D_LARGEFILE64_SOURCE -D_FILEOFFSET_BITS==64 -Wno-strict-aliasing -I/usr/include/libxml2 -fno-strict-aliasing

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/osev_serv_t

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/osev_serv_t: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/osev_serv_t ${OBJECTFILES} ${LDLIBSOPTIONS} ../osev_sdkit/dist/Release/GNU-Linux/libosev_sdkit.a ../third_party/packing/libpacking.a -lwiredtiger -lxml2 -lpthread -ldl /lib/x86_64-linux-gnu/libmbedcrypto.a

${OBJECTDIR}/_ext/f534dc3f/access_log.o: ../third_party/access_log.c
	${MKDIR} -p ${OBJECTDIR}/_ext/f534dc3f
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/f534dc3f/access_log.o ../third_party/access_log.c

${OBJECTDIR}/debug_funct_os.o: debug_funct_os.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/debug_funct_os.o debug_funct_os.c

${OBJECTDIR}/epoll_serv.o: epoll_serv.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/epoll_serv.o epoll_serv.c

${OBJECTDIR}/evd_list.o: evd_list.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/evd_list.o evd_list.c

${OBJECTDIR}/options.o: options.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/options.o options.c

${OBJECTDIR}/osev_bzl.o: osev_bzl.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osev_bzl.o osev_bzl.c

${OBJECTDIR}/osev_obje.o: osev_obje.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osev_obje.o osev_obje.c

${OBJECTDIR}/osev_serv.o: osev_serv.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osev_serv.o osev_serv.c

${OBJECTDIR}/parse_conf.o: parse_conf.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parse_conf.o parse_conf.c

${OBJECTDIR}/process/exceptio.o: process/exceptio.c
	${MKDIR} -p ${OBJECTDIR}/process
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/process/exceptio.o process/exceptio.c

${OBJECTDIR}/process/final_base.o: process/final_base.c
	${MKDIR} -p ${OBJECTDIR}/process
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/process/final_base.o process/final_base.c

${OBJECTDIR}/process/final_collect.o: process/final_collect.c
	${MKDIR} -p ${OBJECTDIR}/process
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/process/final_collect.o process/final_collect.c

${OBJECTDIR}/process/final_constr.o: process/final_constr.c
	${MKDIR} -p ${OBJECTDIR}/process
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/process/final_constr.o process/final_constr.c

${OBJECTDIR}/process/final_invoke.o: process/final_invoke.c
	${MKDIR} -p ${OBJECTDIR}/process
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/process/final_invoke.o process/final_invoke.c

${OBJECTDIR}/process/final_osev.o: process/final_osev.c
	${MKDIR} -p ${OBJECTDIR}/process
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/process/final_osev.o process/final_osev.c

${OBJECTDIR}/process/final_query.o: process/final_query.c
	${MKDIR} -p ${OBJECTDIR}/process
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/process/final_query.o process/final_query.c

${OBJECTDIR}/process/finalize.o: process/finalize.c
	${MKDIR} -p ${OBJECTDIR}/process
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/process/finalize.o process/finalize.c

${OBJECTDIR}/process/hand_binary.o: process/hand_binary.c
	${MKDIR} -p ${OBJECTDIR}/process
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/process/hand_binary.o process/hand_binary.c

${OBJECTDIR}/process/initi_base.o: process/initi_base.c
	${MKDIR} -p ${OBJECTDIR}/process
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/process/initi_base.o process/initi_base.c

${OBJECTDIR}/process/initi_collect.o: process/initi_collect.c
	${MKDIR} -p ${OBJECTDIR}/process
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/process/initi_collect.o process/initi_collect.c

${OBJECTDIR}/process/initi_constr.o: process/initi_constr.c
	${MKDIR} -p ${OBJECTDIR}/process
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/process/initi_constr.o process/initi_constr.c

${OBJECTDIR}/process/initi_invoke.o: process/initi_invoke.c
	${MKDIR} -p ${OBJECTDIR}/process
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/process/initi_invoke.o process/initi_invoke.c

${OBJECTDIR}/process/initi_osev.o: process/initi_osev.c
	${MKDIR} -p ${OBJECTDIR}/process
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/process/initi_osev.o process/initi_osev.c

${OBJECTDIR}/process/initi_query.o: process/initi_query.c
	${MKDIR} -p ${OBJECTDIR}/process
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/process/initi_query.o process/initi_query.c

${OBJECTDIR}/process/initi_utili.o: process/initi_utili.c
	${MKDIR} -p ${OBJECTDIR}/process
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/process/initi_utili.o process/initi_utili.c

${OBJECTDIR}/process/initialize.o: process/initialize.c
	${MKDIR} -p ${OBJECTDIR}/process
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/process/initialize.o process/initialize.c

${OBJECTDIR}/process_cycle.o: process_cycle.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/process_cycle.o process_cycle.c

${OBJECTDIR}/seion_utili.o: seion_utili.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/seion_utili.o seion_utili.c

${OBJECTDIR}/session.o: session.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../osev_sdkit/common -I../osev_common -I../third_party -I../osev_sdkit/requ_interp -I../osev_sdkit/chk_privile -I../osev_sdkit/quer_contain -I../osev_sdkit/run_status -I../osev_sdkit/storage -I../osev_sdkit/clas_compile -I../osev_sdkit/authenize -I../osev_sdkit/lvot_conte -I../osev_sdkit/obje_invoke -I../osev_sdkit/const_entity -I../osev_sdkit/base_meta -I../stora_engine -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/session.o session.c

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
