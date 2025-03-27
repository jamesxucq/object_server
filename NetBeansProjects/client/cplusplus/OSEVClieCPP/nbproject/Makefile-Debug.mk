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
	${OBJECTDIR}/_ext/693ca2d9/encoding.o \
	${OBJECTDIR}/_ext/693ca2d9/hash_table_ex.o \
	${OBJECTDIR}/_ext/693ca2d9/linux_os.o \
	${OBJECTDIR}/_ext/693ca2d9/obid.o \
	${OBJECTDIR}/_ext/693ca2d9/packa_entit.o \
	${OBJECTDIR}/_ext/693ca2d9/parms_style.o \
	${OBJECTDIR}/_ext/74f98836/action_hmap.o \
	${OBJECTDIR}/_ext/74f98836/base64.o \
	${OBJECTDIR}/_ext/74f98836/last_stri.o \
	${OBJECTDIR}/_ext/74f98836/md5.o \
	${OBJECTDIR}/_ext/74f98836/oidoid_hmap.o \
	${OBJECTDIR}/_ext/693ca2d9/xml_utili.o \
	${OBJECTDIR}/_ext/85cdc912/logger.o \
	${OBJECTDIR}/BASELevFP.o \
	${OBJECTDIR}/BASELevOn.o \
	${OBJECTDIR}/BASELevTP.o \
	${OBJECTDIR}/BASELevTh.o \
	${OBJECTDIR}/ClieTokit/DeseRespo.o \
	${OBJECTDIR}/ClieTokit/EntitKits.o \
	${OBJECTDIR}/ClieTokit/InserKits.o \
	${OBJECTDIR}/ClieTokit/UserKits.o \
	${OBJECTDIR}/InvoRType.o \
	${OBJECTDIR}/OSEVConne.o \
	${OBJECTDIR}/excep_msg.o \
	${OBJECTDIR}/function/fstoid.o \
	${OBJECTDIR}/parser/parse_respo.o \
	${OBJECTDIR}/parser/parsing.o \
	${OBJECTDIR}/parser/pinvo.o \
	${OBJECTDIR}/proto_conne/clie_bzl.o \
	${OBJECTDIR}/proto_conne/clie_obje.o \
	${OBJECTDIR}/proto_conne/conatt.o \
	${OBJECTDIR}/proto_conne/conve_utili.o \
	${OBJECTDIR}/proto_conne/cstri_utili.o \
	${OBJECTDIR}/proto_conne/hand_method.o \
	${OBJECTDIR}/proto_conne/osco_socks.o \
	${OBJECTDIR}/proto_conne/proto_conne.o


# C Compiler Flags
CFLAGS=-Wall -D_CPLUSPLUS_CLIE -D_DEBUG -D_LARGEFILE64_SOURCE -D_FILEOFFSET_BITS==64 -fno-strict-aliasing -Wno-maybe-uninitialized -Wno-register

# CC Compiler Flags
CCFLAGS=-Wall -D_CPLUSPLUS_CLIE -D_DEBUG -D_LARGEFILE64_SOURCE -D_FILEOFFSET_BITS==64 -fno-strict-aliasing -Wno-maybe-uninitialized -Wno-register
CXXFLAGS=-Wall -D_CPLUSPLUS_CLIE -D_DEBUG -D_LARGEFILE64_SOURCE -D_FILEOFFSET_BITS==64 -fno-strict-aliasing -Wno-maybe-uninitialized -Wno-register

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libOSEVClieCPP.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libOSEVClieCPP.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libOSEVClieCPP.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/_ext/693ca2d9/encoding.o: ../../../serv_solution/osev_common/encoding.c
	${MKDIR} -p ${OBJECTDIR}/_ext/693ca2d9
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/693ca2d9/encoding.o ../../../serv_solution/osev_common/encoding.c

${OBJECTDIR}/_ext/693ca2d9/hash_table_ex.o: ../../../serv_solution/osev_common/hash_table_ex.c
	${MKDIR} -p ${OBJECTDIR}/_ext/693ca2d9
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/693ca2d9/hash_table_ex.o ../../../serv_solution/osev_common/hash_table_ex.c

${OBJECTDIR}/_ext/693ca2d9/linux_os.o: ../../../serv_solution/osev_common/linux_os.c
	${MKDIR} -p ${OBJECTDIR}/_ext/693ca2d9
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/693ca2d9/linux_os.o ../../../serv_solution/osev_common/linux_os.c

${OBJECTDIR}/_ext/693ca2d9/obid.o: ../../../serv_solution/osev_common/obid.c
	${MKDIR} -p ${OBJECTDIR}/_ext/693ca2d9
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/693ca2d9/obid.o ../../../serv_solution/osev_common/obid.c

${OBJECTDIR}/_ext/693ca2d9/packa_entit.o: ../../../serv_solution/osev_common/packa_entit.c
	${MKDIR} -p ${OBJECTDIR}/_ext/693ca2d9
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/693ca2d9/packa_entit.o ../../../serv_solution/osev_common/packa_entit.c

${OBJECTDIR}/_ext/693ca2d9/parms_style.o: ../../../serv_solution/osev_common/parms_style.c
	${MKDIR} -p ${OBJECTDIR}/_ext/693ca2d9
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/693ca2d9/parms_style.o ../../../serv_solution/osev_common/parms_style.c

${OBJECTDIR}/_ext/74f98836/action_hmap.o: ../../../serv_solution/osev_common/utility/action_hmap.c
	${MKDIR} -p ${OBJECTDIR}/_ext/74f98836
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74f98836/action_hmap.o ../../../serv_solution/osev_common/utility/action_hmap.c

${OBJECTDIR}/_ext/74f98836/base64.o: ../../../serv_solution/osev_common/utility/base64.c
	${MKDIR} -p ${OBJECTDIR}/_ext/74f98836
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74f98836/base64.o ../../../serv_solution/osev_common/utility/base64.c

${OBJECTDIR}/_ext/74f98836/last_stri.o: ../../../serv_solution/osev_common/utility/last_stri.c
	${MKDIR} -p ${OBJECTDIR}/_ext/74f98836
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74f98836/last_stri.o ../../../serv_solution/osev_common/utility/last_stri.c

${OBJECTDIR}/_ext/74f98836/md5.o: ../../../serv_solution/osev_common/utility/md5.c
	${MKDIR} -p ${OBJECTDIR}/_ext/74f98836
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74f98836/md5.o ../../../serv_solution/osev_common/utility/md5.c

${OBJECTDIR}/_ext/74f98836/oidoid_hmap.o: ../../../serv_solution/osev_common/utility/oidoid_hmap.c
	${MKDIR} -p ${OBJECTDIR}/_ext/74f98836
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74f98836/oidoid_hmap.o ../../../serv_solution/osev_common/utility/oidoid_hmap.c

${OBJECTDIR}/_ext/693ca2d9/xml_utili.o: ../../../serv_solution/osev_common/xml_utili.c
	${MKDIR} -p ${OBJECTDIR}/_ext/693ca2d9
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/693ca2d9/xml_utili.o ../../../serv_solution/osev_common/xml_utili.c

${OBJECTDIR}/_ext/85cdc912/logger.o: ../../../serv_solution/third_party/logger.c
	${MKDIR} -p ${OBJECTDIR}/_ext/85cdc912
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/85cdc912/logger.o ../../../serv_solution/third_party/logger.c

${OBJECTDIR}/BASELevFP.o: BASELevFP.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BASELevFP.o BASELevFP.cpp

${OBJECTDIR}/BASELevOn.o: BASELevOn.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BASELevOn.o BASELevOn.cpp

${OBJECTDIR}/BASELevTP.o: BASELevTP.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BASELevTP.o BASELevTP.cpp

${OBJECTDIR}/BASELevTh.o: BASELevTh.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BASELevTh.o BASELevTh.cpp

${OBJECTDIR}/ClieTokit/DeseRespo.o: ClieTokit/DeseRespo.cpp
	${MKDIR} -p ${OBJECTDIR}/ClieTokit
	${RM} "$@.d"
	$(COMPILE.cc) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ClieTokit/DeseRespo.o ClieTokit/DeseRespo.cpp

${OBJECTDIR}/ClieTokit/EntitKits.o: ClieTokit/EntitKits.cpp
	${MKDIR} -p ${OBJECTDIR}/ClieTokit
	${RM} "$@.d"
	$(COMPILE.cc) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ClieTokit/EntitKits.o ClieTokit/EntitKits.cpp

${OBJECTDIR}/ClieTokit/InserKits.o: ClieTokit/InserKits.cpp
	${MKDIR} -p ${OBJECTDIR}/ClieTokit
	${RM} "$@.d"
	$(COMPILE.cc) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ClieTokit/InserKits.o ClieTokit/InserKits.cpp

${OBJECTDIR}/ClieTokit/UserKits.o: ClieTokit/UserKits.cpp
	${MKDIR} -p ${OBJECTDIR}/ClieTokit
	${RM} "$@.d"
	$(COMPILE.cc) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ClieTokit/UserKits.o ClieTokit/UserKits.cpp

${OBJECTDIR}/InvoRType.o: InvoRType.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InvoRType.o InvoRType.cpp

${OBJECTDIR}/OSEVConne.o: OSEVConne.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/OSEVConne.o OSEVConne.cpp

${OBJECTDIR}/excep_msg.o: excep_msg.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/excep_msg.o excep_msg.c

${OBJECTDIR}/function/fstoid.o: function/fstoid.c
	${MKDIR} -p ${OBJECTDIR}/function
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/function/fstoid.o function/fstoid.c

${OBJECTDIR}/parser/parse_respo.o: parser/parse_respo.c
	${MKDIR} -p ${OBJECTDIR}/parser
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parser/parse_respo.o parser/parse_respo.c

${OBJECTDIR}/parser/parsing.o: parser/parsing.c
	${MKDIR} -p ${OBJECTDIR}/parser
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parser/parsing.o parser/parsing.c

${OBJECTDIR}/parser/pinvo.o: parser/pinvo.c
	${MKDIR} -p ${OBJECTDIR}/parser
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parser/pinvo.o parser/pinvo.c

${OBJECTDIR}/proto_conne/clie_bzl.o: proto_conne/clie_bzl.c
	${MKDIR} -p ${OBJECTDIR}/proto_conne
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/proto_conne/clie_bzl.o proto_conne/clie_bzl.c

${OBJECTDIR}/proto_conne/clie_obje.o: proto_conne/clie_obje.c
	${MKDIR} -p ${OBJECTDIR}/proto_conne
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/proto_conne/clie_obje.o proto_conne/clie_obje.c

${OBJECTDIR}/proto_conne/conatt.o: proto_conne/conatt.c
	${MKDIR} -p ${OBJECTDIR}/proto_conne
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/proto_conne/conatt.o proto_conne/conatt.c

${OBJECTDIR}/proto_conne/conve_utili.o: proto_conne/conve_utili.c
	${MKDIR} -p ${OBJECTDIR}/proto_conne
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/proto_conne/conve_utili.o proto_conne/conve_utili.c

${OBJECTDIR}/proto_conne/cstri_utili.o: proto_conne/cstri_utili.c
	${MKDIR} -p ${OBJECTDIR}/proto_conne
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/proto_conne/cstri_utili.o proto_conne/cstri_utili.c

${OBJECTDIR}/proto_conne/hand_method.o: proto_conne/hand_method.c
	${MKDIR} -p ${OBJECTDIR}/proto_conne
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/proto_conne/hand_method.o proto_conne/hand_method.c

${OBJECTDIR}/proto_conne/osco_socks.o: proto_conne/osco_socks.c
	${MKDIR} -p ${OBJECTDIR}/proto_conne
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/proto_conne/osco_socks.o proto_conne/osco_socks.c

${OBJECTDIR}/proto_conne/proto_conne.o: proto_conne/proto_conne.c
	${MKDIR} -p ${OBJECTDIR}/proto_conne
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution -I../../../serv_solution/third_party -I../../../serv_solution/osev_common -I../../../serv_solution/stora_engine -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/proto_conne/proto_conne.o proto_conne/proto_conne.c

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
