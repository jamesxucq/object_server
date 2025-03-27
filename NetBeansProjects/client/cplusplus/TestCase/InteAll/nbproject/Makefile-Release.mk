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
	${OBJECTDIR}/InteLevFP/LevFP_Create.o \
	${OBJECTDIR}/InteLevFP/LevFP_Drop.o \
	${OBJECTDIR}/InteLevFP/LevFP_Echo.o \
	${OBJECTDIR}/InteLevFP/LevFP_Factory.o \
	${OBJECTDIR}/InteLevFP/LevFP_Insert.o \
	${OBJECTDIR}/InteLevFP/LevFP_Invoke.o \
	${OBJECTDIR}/InteLevFP/LevFP_Search.o \
	${OBJECTDIR}/InteLevFP/LevFP_Update.o \
	${OBJECTDIR}/InteLevTh/LevTh_Create.o \
	${OBJECTDIR}/InteLevTh/LevTh_Drop.o \
	${OBJECTDIR}/InteLevTh/LevTh_Echo.o \
	${OBJECTDIR}/InteLevTh/LevTh_Insert.o \
	${OBJECTDIR}/InteLevTh/LevTh_Invoke.o \
	${OBJECTDIR}/InteLevTh/LevTh_Search.o \
	${OBJECTDIR}/InteLevTh/LevTh_Update.o \
	${OBJECTDIR}/earth_lv2p/txxt.o \
	${OBJECTDIR}/lev3_test.o \
	${OBJECTDIR}/lv4p_test.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/inteall

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/inteall: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/inteall ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/InteLevFP/LevFP_Create.o: InteLevFP/LevFP_Create.cpp
	${MKDIR} -p ${OBJECTDIR}/InteLevFP
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InteLevFP/LevFP_Create.o InteLevFP/LevFP_Create.cpp

${OBJECTDIR}/InteLevFP/LevFP_Drop.o: InteLevFP/LevFP_Drop.cpp
	${MKDIR} -p ${OBJECTDIR}/InteLevFP
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InteLevFP/LevFP_Drop.o InteLevFP/LevFP_Drop.cpp

${OBJECTDIR}/InteLevFP/LevFP_Echo.o: InteLevFP/LevFP_Echo.cpp
	${MKDIR} -p ${OBJECTDIR}/InteLevFP
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InteLevFP/LevFP_Echo.o InteLevFP/LevFP_Echo.cpp

${OBJECTDIR}/InteLevFP/LevFP_Factory.o: InteLevFP/LevFP_Factory.cpp
	${MKDIR} -p ${OBJECTDIR}/InteLevFP
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InteLevFP/LevFP_Factory.o InteLevFP/LevFP_Factory.cpp

${OBJECTDIR}/InteLevFP/LevFP_Insert.o: InteLevFP/LevFP_Insert.cpp
	${MKDIR} -p ${OBJECTDIR}/InteLevFP
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InteLevFP/LevFP_Insert.o InteLevFP/LevFP_Insert.cpp

${OBJECTDIR}/InteLevFP/LevFP_Invoke.o: InteLevFP/LevFP_Invoke.cpp
	${MKDIR} -p ${OBJECTDIR}/InteLevFP
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InteLevFP/LevFP_Invoke.o InteLevFP/LevFP_Invoke.cpp

${OBJECTDIR}/InteLevFP/LevFP_Search.o: InteLevFP/LevFP_Search.cpp
	${MKDIR} -p ${OBJECTDIR}/InteLevFP
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InteLevFP/LevFP_Search.o InteLevFP/LevFP_Search.cpp

${OBJECTDIR}/InteLevFP/LevFP_Update.o: InteLevFP/LevFP_Update.cpp
	${MKDIR} -p ${OBJECTDIR}/InteLevFP
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InteLevFP/LevFP_Update.o InteLevFP/LevFP_Update.cpp

${OBJECTDIR}/InteLevTh/LevTh_Create.o: InteLevTh/LevTh_Create.cpp
	${MKDIR} -p ${OBJECTDIR}/InteLevTh
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InteLevTh/LevTh_Create.o InteLevTh/LevTh_Create.cpp

${OBJECTDIR}/InteLevTh/LevTh_Drop.o: InteLevTh/LevTh_Drop.cpp
	${MKDIR} -p ${OBJECTDIR}/InteLevTh
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InteLevTh/LevTh_Drop.o InteLevTh/LevTh_Drop.cpp

${OBJECTDIR}/InteLevTh/LevTh_Echo.o: InteLevTh/LevTh_Echo.cpp
	${MKDIR} -p ${OBJECTDIR}/InteLevTh
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InteLevTh/LevTh_Echo.o InteLevTh/LevTh_Echo.cpp

${OBJECTDIR}/InteLevTh/LevTh_Insert.o: InteLevTh/LevTh_Insert.cpp
	${MKDIR} -p ${OBJECTDIR}/InteLevTh
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InteLevTh/LevTh_Insert.o InteLevTh/LevTh_Insert.cpp

${OBJECTDIR}/InteLevTh/LevTh_Invoke.o: InteLevTh/LevTh_Invoke.cpp
	${MKDIR} -p ${OBJECTDIR}/InteLevTh
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InteLevTh/LevTh_Invoke.o InteLevTh/LevTh_Invoke.cpp

${OBJECTDIR}/InteLevTh/LevTh_Search.o: InteLevTh/LevTh_Search.cpp
	${MKDIR} -p ${OBJECTDIR}/InteLevTh
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InteLevTh/LevTh_Search.o InteLevTh/LevTh_Search.cpp

${OBJECTDIR}/InteLevTh/LevTh_Update.o: InteLevTh/LevTh_Update.cpp
	${MKDIR} -p ${OBJECTDIR}/InteLevTh
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InteLevTh/LevTh_Update.o InteLevTh/LevTh_Update.cpp

${OBJECTDIR}/earth_lv2p/txxt.o: earth_lv2p/txxt.cpp
	${MKDIR} -p ${OBJECTDIR}/earth_lv2p
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/earth_lv2p/txxt.o earth_lv2p/txxt.cpp

${OBJECTDIR}/lev3_test.o: lev3_test.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lev3_test.o lev3_test.cpp

${OBJECTDIR}/lv4p_test.o: lv4p_test.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lv4p_test.o lv4p_test.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

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
