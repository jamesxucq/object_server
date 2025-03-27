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
	${OBJECTDIR}/_ext/693ca2d9/commo_string.o \
	${OBJECTDIR}/_ext/693ca2d9/crypto_utili.o \
	${OBJECTDIR}/_ext/693ca2d9/encoding.o \
	${OBJECTDIR}/_ext/693ca2d9/errmsg.o \
	${OBJECTDIR}/_ext/693ca2d9/hash_table_ex.o \
	${OBJECTDIR}/_ext/693ca2d9/linux_os.o \
	${OBJECTDIR}/_ext/693ca2d9/obid.o \
	${OBJECTDIR}/_ext/693ca2d9/packa_entit.o \
	${OBJECTDIR}/_ext/693ca2d9/parms_style.o \
	${OBJECTDIR}/_ext/693ca2d9/parse_utili.o \
	${OBJECTDIR}/_ext/693ca2d9/respo_pack.o \
	${OBJECTDIR}/_ext/693ca2d9/stoid.o \
	${OBJECTDIR}/_ext/693ca2d9/stri_utili.o \
	${OBJECTDIR}/_ext/74f98836/action_hmap.o \
	${OBJECTDIR}/_ext/74f98836/adler32.o \
	${OBJECTDIR}/_ext/74f98836/base64.o \
	${OBJECTDIR}/_ext/74f98836/cache_hmap.o \
	${OBJECTDIR}/_ext/74f98836/checksum.o \
	${OBJECTDIR}/_ext/74f98836/hash_map.o \
	${OBJECTDIR}/_ext/74f98836/hash_table.o \
	${OBJECTDIR}/_ext/74f98836/last_stri.o \
	${OBJECTDIR}/_ext/74f98836/md5.o \
	${OBJECTDIR}/_ext/74f98836/oidoid_hmap.o \
	${OBJECTDIR}/_ext/74f98836/strptime.o \
	${OBJECTDIR}/_ext/85cdc912/dmmap64.o \
	${OBJECTDIR}/_ext/85cdc912/logger.o \
	${OBJECTDIR}/_ext/85cdc912/memory_utility.o \
	${OBJECTDIR}/clie_bzl.o \
	${OBJECTDIR}/clie_obje.o \
	${OBJECTDIR}/conatt.o \
	${OBJECTDIR}/debug_funct_clang.o \
	${OBJECTDIR}/dstri_utili.o \
	${OBJECTDIR}/excep_msg.o \
	${OBJECTDIR}/function/fstoid.o \
	${OBJECTDIR}/hand_method.o \
	${OBJECTDIR}/osco_socks.o \
	${OBJECTDIR}/osev_clie_clang.o \
	${OBJECTDIR}/parse_respo.o \
	${OBJECTDIR}/pinvo.o


# C Compiler Flags
CFLAGS=-Wall -D_CLANG_CLIE -D_DEBUG -D_LARGEFILE64_SOURCE -D_FILEOFFSET_BITS==64 -fno-strict-aliasing -Wno-maybe-uninitialized

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libosev_clie_clang.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libosev_clie_clang.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libosev_clie_clang.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libosev_clie_clang.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libosev_clie_clang.a

${OBJECTDIR}/_ext/693ca2d9/commo_string.o: ../../../serv_solution/osev_common/commo_string.c
	${MKDIR} -p ${OBJECTDIR}/_ext/693ca2d9
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/693ca2d9/commo_string.o ../../../serv_solution/osev_common/commo_string.c

${OBJECTDIR}/_ext/693ca2d9/crypto_utili.o: ../../../serv_solution/osev_common/crypto_utili.c
	${MKDIR} -p ${OBJECTDIR}/_ext/693ca2d9
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/693ca2d9/crypto_utili.o ../../../serv_solution/osev_common/crypto_utili.c

${OBJECTDIR}/_ext/693ca2d9/encoding.o: ../../../serv_solution/osev_common/encoding.c
	${MKDIR} -p ${OBJECTDIR}/_ext/693ca2d9
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/693ca2d9/encoding.o ../../../serv_solution/osev_common/encoding.c

${OBJECTDIR}/_ext/693ca2d9/errmsg.o: ../../../serv_solution/osev_common/errmsg.c
	${MKDIR} -p ${OBJECTDIR}/_ext/693ca2d9
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/693ca2d9/errmsg.o ../../../serv_solution/osev_common/errmsg.c

${OBJECTDIR}/_ext/693ca2d9/hash_table_ex.o: ../../../serv_solution/osev_common/hash_table_ex.c
	${MKDIR} -p ${OBJECTDIR}/_ext/693ca2d9
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/693ca2d9/hash_table_ex.o ../../../serv_solution/osev_common/hash_table_ex.c

${OBJECTDIR}/_ext/693ca2d9/linux_os.o: ../../../serv_solution/osev_common/linux_os.c
	${MKDIR} -p ${OBJECTDIR}/_ext/693ca2d9
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/693ca2d9/linux_os.o ../../../serv_solution/osev_common/linux_os.c

${OBJECTDIR}/_ext/693ca2d9/obid.o: ../../../serv_solution/osev_common/obid.c
	${MKDIR} -p ${OBJECTDIR}/_ext/693ca2d9
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/693ca2d9/obid.o ../../../serv_solution/osev_common/obid.c

${OBJECTDIR}/_ext/693ca2d9/packa_entit.o: ../../../serv_solution/osev_common/packa_entit.c
	${MKDIR} -p ${OBJECTDIR}/_ext/693ca2d9
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/693ca2d9/packa_entit.o ../../../serv_solution/osev_common/packa_entit.c

${OBJECTDIR}/_ext/693ca2d9/parms_style.o: ../../../serv_solution/osev_common/parms_style.c
	${MKDIR} -p ${OBJECTDIR}/_ext/693ca2d9
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/693ca2d9/parms_style.o ../../../serv_solution/osev_common/parms_style.c

${OBJECTDIR}/_ext/693ca2d9/parse_utili.o: ../../../serv_solution/osev_common/parse_utili.c
	${MKDIR} -p ${OBJECTDIR}/_ext/693ca2d9
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/693ca2d9/parse_utili.o ../../../serv_solution/osev_common/parse_utili.c

${OBJECTDIR}/_ext/693ca2d9/respo_pack.o: ../../../serv_solution/osev_common/respo_pack.c
	${MKDIR} -p ${OBJECTDIR}/_ext/693ca2d9
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/693ca2d9/respo_pack.o ../../../serv_solution/osev_common/respo_pack.c

${OBJECTDIR}/_ext/693ca2d9/stoid.o: ../../../serv_solution/osev_common/stoid.c
	${MKDIR} -p ${OBJECTDIR}/_ext/693ca2d9
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/693ca2d9/stoid.o ../../../serv_solution/osev_common/stoid.c

${OBJECTDIR}/_ext/693ca2d9/stri_utili.o: ../../../serv_solution/osev_common/stri_utili.c
	${MKDIR} -p ${OBJECTDIR}/_ext/693ca2d9
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/693ca2d9/stri_utili.o ../../../serv_solution/osev_common/stri_utili.c

${OBJECTDIR}/_ext/74f98836/action_hmap.o: ../../../serv_solution/osev_common/utility/action_hmap.c
	${MKDIR} -p ${OBJECTDIR}/_ext/74f98836
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74f98836/action_hmap.o ../../../serv_solution/osev_common/utility/action_hmap.c

${OBJECTDIR}/_ext/74f98836/adler32.o: ../../../serv_solution/osev_common/utility/adler32.c
	${MKDIR} -p ${OBJECTDIR}/_ext/74f98836
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74f98836/adler32.o ../../../serv_solution/osev_common/utility/adler32.c

${OBJECTDIR}/_ext/74f98836/base64.o: ../../../serv_solution/osev_common/utility/base64.c
	${MKDIR} -p ${OBJECTDIR}/_ext/74f98836
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74f98836/base64.o ../../../serv_solution/osev_common/utility/base64.c

${OBJECTDIR}/_ext/74f98836/cache_hmap.o: ../../../serv_solution/osev_common/utility/cache_hmap.c
	${MKDIR} -p ${OBJECTDIR}/_ext/74f98836
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74f98836/cache_hmap.o ../../../serv_solution/osev_common/utility/cache_hmap.c

${OBJECTDIR}/_ext/74f98836/checksum.o: ../../../serv_solution/osev_common/utility/checksum.c
	${MKDIR} -p ${OBJECTDIR}/_ext/74f98836
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74f98836/checksum.o ../../../serv_solution/osev_common/utility/checksum.c

${OBJECTDIR}/_ext/74f98836/hash_map.o: ../../../serv_solution/osev_common/utility/hash_map.c
	${MKDIR} -p ${OBJECTDIR}/_ext/74f98836
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74f98836/hash_map.o ../../../serv_solution/osev_common/utility/hash_map.c

${OBJECTDIR}/_ext/74f98836/hash_table.o: ../../../serv_solution/osev_common/utility/hash_table.c
	${MKDIR} -p ${OBJECTDIR}/_ext/74f98836
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74f98836/hash_table.o ../../../serv_solution/osev_common/utility/hash_table.c

${OBJECTDIR}/_ext/74f98836/last_stri.o: ../../../serv_solution/osev_common/utility/last_stri.c
	${MKDIR} -p ${OBJECTDIR}/_ext/74f98836
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74f98836/last_stri.o ../../../serv_solution/osev_common/utility/last_stri.c

${OBJECTDIR}/_ext/74f98836/md5.o: ../../../serv_solution/osev_common/utility/md5.c
	${MKDIR} -p ${OBJECTDIR}/_ext/74f98836
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74f98836/md5.o ../../../serv_solution/osev_common/utility/md5.c

${OBJECTDIR}/_ext/74f98836/oidoid_hmap.o: ../../../serv_solution/osev_common/utility/oidoid_hmap.c
	${MKDIR} -p ${OBJECTDIR}/_ext/74f98836
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74f98836/oidoid_hmap.o ../../../serv_solution/osev_common/utility/oidoid_hmap.c

${OBJECTDIR}/_ext/74f98836/strptime.o: ../../../serv_solution/osev_common/utility/strptime.c
	${MKDIR} -p ${OBJECTDIR}/_ext/74f98836
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74f98836/strptime.o ../../../serv_solution/osev_common/utility/strptime.c

${OBJECTDIR}/_ext/85cdc912/dmmap64.o: ../../../serv_solution/third_party/dmmap64.c
	${MKDIR} -p ${OBJECTDIR}/_ext/85cdc912
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/85cdc912/dmmap64.o ../../../serv_solution/third_party/dmmap64.c

${OBJECTDIR}/_ext/85cdc912/logger.o: ../../../serv_solution/third_party/logger.c
	${MKDIR} -p ${OBJECTDIR}/_ext/85cdc912
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/85cdc912/logger.o ../../../serv_solution/third_party/logger.c

${OBJECTDIR}/_ext/85cdc912/memory_utility.o: ../../../serv_solution/third_party/memory_utility.c
	${MKDIR} -p ${OBJECTDIR}/_ext/85cdc912
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/85cdc912/memory_utility.o ../../../serv_solution/third_party/memory_utility.c

${OBJECTDIR}/clie_bzl.o: clie_bzl.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clie_bzl.o clie_bzl.c

${OBJECTDIR}/clie_obje.o: clie_obje.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clie_obje.o clie_obje.c

${OBJECTDIR}/conatt.o: conatt.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/conatt.o conatt.c

${OBJECTDIR}/debug_funct_clang.o: debug_funct_clang.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/debug_funct_clang.o debug_funct_clang.c

${OBJECTDIR}/dstri_utili.o: dstri_utili.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/dstri_utili.o dstri_utili.c

${OBJECTDIR}/excep_msg.o: excep_msg.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/excep_msg.o excep_msg.c

${OBJECTDIR}/function/fstoid.o: function/fstoid.c
	${MKDIR} -p ${OBJECTDIR}/function
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/function/fstoid.o function/fstoid.c

${OBJECTDIR}/hand_method.o: hand_method.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hand_method.o hand_method.c

${OBJECTDIR}/osco_socks.o: osco_socks.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osco_socks.o osco_socks.c

${OBJECTDIR}/osev_clie_clang.o: osev_clie_clang.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osev_clie_clang.o osev_clie_clang.c

${OBJECTDIR}/parse_respo.o: parse_respo.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parse_respo.o parse_respo.c

${OBJECTDIR}/pinvo.o: pinvo.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -O2 -I../../../serv_solution/osev_common -I../../../serv_solution/third_party -I../../../serv_solution/stora_engine -I../../../serv_solution/osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pinvo.o pinvo.c

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
