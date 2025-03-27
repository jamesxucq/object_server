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
	${OBJECTDIR}/_ext/13d9cc0c/txxt.o \
	${OBJECTDIR}/InsertLevTh.o


# C Compiler Flags
CFLAGS=-Wno-register

# CC Compiler Flags
CCFLAGS=-Wno-register
CXXFLAGS=-Wno-register

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/insertlevth

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/insertlevth: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/insertlevth ${OBJECTFILES} ${LDLIBSOPTIONS} -lOSEVClieCPP -lpacking

${OBJECTDIR}/_ext/13d9cc0c/txxt.o: ../earth_lv2p/txxt.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/13d9cc0c
	${RM} "$@.d"
	$(COMPILE.c) -g -I../../../../serv_solution/third_party -I../../../../serv_solution -I../../OSEVClieCPP -I../../../../serv_solution/osev_common -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/13d9cc0c/txxt.o ../earth_lv2p/txxt.cpp

${OBJECTDIR}/InsertLevTh.o: InsertLevTh.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../serv_solution/third_party -I../../../../serv_solution -I../../OSEVClieCPP -I../../../../serv_solution/osev_common -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InsertLevTh.o InsertLevTh.cpp

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
