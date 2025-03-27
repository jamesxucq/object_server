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
	${OBJECTDIR}/lev3_test.o \
	${OBJECTDIR}/lv4p_test.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/txxt.o


# C Compiler Flags
CFLAGS=-Wall -D_DEBUG -D_LARGEFILE64_SOURCE -D_FILEOFFSET_BITS==64 -D_CHKVINTV -fno-strict-aliasing

# CC Compiler Flags
CCFLAGS=-Wall -D_DEBUG -D_LARGEFILE64_SOURCE -D_FILEOFFSET_BITS==64 -D_CHKVINTV -fno-strict-aliasing
CXXFLAGS=-Wall -D_DEBUG -D_LARGEFILE64_SOURCE -D_FILEOFFSET_BITS==64 -D_CHKVINTV -fno-strict-aliasing

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/txxttest

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/txxttest: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/txxttest ${OBJECTFILES} ${LDLIBSOPTIONS} ../../OSEVClieCPP/dist/Debug/GNU-Linux/libOSEVClieCPP.so ../../../../serv_solution/third_party/packing/libpacking.a

${OBJECTDIR}/lev3_test.o: lev3_test.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../OSEVClieCPP -I../../../../serv_solution/osev_common -I../../../../serv_solution -I../../../../serv_solution/third_party -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lev3_test.o lev3_test.cpp

${OBJECTDIR}/lv4p_test.o: lv4p_test.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../OSEVClieCPP -I../../../../serv_solution/osev_common -I../../../../serv_solution -I../../../../serv_solution/third_party -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lv4p_test.o lv4p_test.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -O2 -I../../OSEVClieCPP -I../../../../serv_solution/osev_common -I../../../../serv_solution -I../../../../serv_solution/third_party -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/txxt.o: txxt.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../OSEVClieCPP -I../../../../serv_solution/osev_common -I../../../../serv_solution -I../../../../serv_solution/third_party -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/txxt.o txxt.cpp

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
