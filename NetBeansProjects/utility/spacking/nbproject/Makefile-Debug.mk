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
	${OBJECTDIR}/_ext/6bbad5da/config.o \
	${OBJECTDIR}/_ext/6bbad5da/cur_json.o \
	${OBJECTDIR}/_ext/6bbad5da/hex.o \
	${OBJECTDIR}/_ext/6bbad5da/os_alloc.o \
	${OBJECTDIR}/_ext/6bbad5da/os_errno.o \
	${OBJECTDIR}/_ext/6bbad5da/pack_api.o \
	${OBJECTDIR}/_ext/6bbad5da/pack_item.o \
	${OBJECTDIR}/_ext/6bbad5da/pack_stream.o


# C Compiler Flags
CFLAGS=-DJEMALLOC_NO_DEMANGLE

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libpacking.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libpacking.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libpacking.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libpacking.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libpacking.a

${OBJECTDIR}/_ext/6bbad5da/config.o: ../packing/config.c
	${MKDIR} -p ${OBJECTDIR}/_ext/6bbad5da
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/6bbad5da/config.o ../packing/config.c

${OBJECTDIR}/_ext/6bbad5da/cur_json.o: ../packing/cur_json.c
	${MKDIR} -p ${OBJECTDIR}/_ext/6bbad5da
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/6bbad5da/cur_json.o ../packing/cur_json.c

${OBJECTDIR}/_ext/6bbad5da/hex.o: ../packing/hex.c
	${MKDIR} -p ${OBJECTDIR}/_ext/6bbad5da
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/6bbad5da/hex.o ../packing/hex.c

${OBJECTDIR}/_ext/6bbad5da/os_alloc.o: ../packing/os_alloc.c
	${MKDIR} -p ${OBJECTDIR}/_ext/6bbad5da
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/6bbad5da/os_alloc.o ../packing/os_alloc.c

${OBJECTDIR}/_ext/6bbad5da/os_errno.o: ../packing/os_errno.c
	${MKDIR} -p ${OBJECTDIR}/_ext/6bbad5da
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/6bbad5da/os_errno.o ../packing/os_errno.c

${OBJECTDIR}/_ext/6bbad5da/pack_api.o: ../packing/pack_api.c
	${MKDIR} -p ${OBJECTDIR}/_ext/6bbad5da
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/6bbad5da/pack_api.o ../packing/pack_api.c

${OBJECTDIR}/_ext/6bbad5da/pack_item.o: ../packing/pack_item.c
	${MKDIR} -p ${OBJECTDIR}/_ext/6bbad5da
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/6bbad5da/pack_item.o ../packing/pack_item.c

${OBJECTDIR}/_ext/6bbad5da/pack_stream.o: ../packing/pack_stream.c
	${MKDIR} -p ${OBJECTDIR}/_ext/6bbad5da
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/6bbad5da/pack_stream.o ../packing/pack_stream.c

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
