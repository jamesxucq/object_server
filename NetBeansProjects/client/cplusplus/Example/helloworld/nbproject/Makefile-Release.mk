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
	${OBJECTDIR}/_ext/13d9cc0c/txxt.o \
	${OBJECTDIR}/helloworld.o \
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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/helloworld

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/helloworld: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/helloworld ${OBJECTFILES} ${LDLIBSOPTIONS} ../../OSEVClieCPP/dist/Debug/GNU-Linux/libOSEVClieCPP.so ../../../../serv_solution/third_party/packing/libpacking.so

${OBJECTDIR}/_ext/13d9cc0c/txxt.o: ../earth_lv2p/txxt.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/13d9cc0c
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../../../../serv_solution/third_party -I../../../../serv_solution -I../../OSEVClieCPP -I../../../../serv_solution/osev_common -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/13d9cc0c/txxt.o ../earth_lv2p/txxt.cpp

${OBJECTDIR}/helloworld.o: helloworld.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../../../../serv_solution/third_party -I../../../../serv_solution -I../../OSEVClieCPP -I../../../../serv_solution/osev_common -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/helloworld.o helloworld.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../../serv_solution/third_party -I../../../../serv_solution -I../../OSEVClieCPP -I../../../../serv_solution/osev_common -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

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
