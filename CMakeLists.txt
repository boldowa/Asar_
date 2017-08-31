#-----------------------------------------------------------
# CMakeList for asar
#-----------------------------------------------------------

cmake_minimum_required(VERSION 3.1)

### option putout macro
macro(putopt opt)
	message("${opt} = ${${opt}}")
endmacro(putopt)

### add common defines
macro(add_common_define target def)
	set(${target} "${${target}} ${DEFINE_PREFIX}${def}")
endmacro(add_common_define)

### specify build type
set(CMAKE_BUILD_TYPE "Release")

### Visual Studio Solution Name
project(asar)

###### specify C and C++ compile option
### soecify unix compile option
if(UNIX OR MINGW)
	## define prefix(gcc)
	set(DEFINE_PREFIX "-D")

        set(CMAKE_C_FLAGS_RELEASE "-O2 -fdata-sections -ffunction-sections")
        set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})

        set(CMAKE_C_FLAGS "-ansi -Wall -Werror -Wno-unused-result -Wno-uninitialized")

	## set linker link flag
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-s -Wl,--gc-sections")
	set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "-T")
	set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "-s -Wl,--gc-sections")
endif()

if(MSVC)
	## define prefix(gcc)
	set(DEFINE_PREFIX "/D")

	# todo : define it
endif(MSVC)

### add common define
if(UNIX)
        add_common_define(CMAKE_C_FLAGS UNIX)
        add_common_define(CMAKE_C_FLAGS linux)
endif(UNIX)
if(MINGW OR MSVC)
        add_common_define(CMAKE_C_FLAGS _WIN32)
        add_common_define(CMAKE_C_FLAGS WIN32)
endif()
if(MINGW)
        set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -static")
        set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS_RELEASE} -static")
        set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} -static")
endif(MINGW)

add_common_define(CMAKE_C_FLAGS stricmp=strcasecmp)


if(CMAKE_BUILD_TYPE MATCHES "Debug")
	add_common_define(CMAKE_C_FLAGS_DEBUG DEBUG)
else()
	add_common_define(CMAKE_C_FLAGS_RELEASE RELEASE)
	add_common_define(CMAKE_C_FLAGS_RELEASE NDEBUG)
endif()


### set C++ option
set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS})

###### specify C++ command option
if(UNIX OR MINGW)
	## no exception
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -fno-rtti")
endif()

if(MSVC)
	# todo : define it
endif(MSVC)


### visual studio directory config
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "libasar")

### build
file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.cpp")
list(REMOVE_ITEM SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/util/AsarBuildTime.cpp")
set(RES "")
if(MINGW OR MSVC)
        set(RES "${CMAKE_CURRENT_SOURCE_DIR}/src/resource/asar.rc")
endif()

set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(libasar SHARED ${SRC_FILES} ${RES} "${CMAKE_CURRENT_SOURCE_DIR}/src/interface-lib.cpp")
target_include_directories(libasar PRIVATE ${INCROOT} ${INCROOT}/common ${INCROOT}/arch ${INCROOT}/lib ${INCROOT}/util)
target_compile_options(libasar PRIVATE ${DEFINE_PREFIX}INTERFACE_LIB)
set_target_properties(libasar PROPERTIES OUTPUT_NAME "asar")
if(MINGW OR WIN32)
        set_target_properties(libasar PROPERTIES PREFIX "")
endif()

add_executable(asar ${SRC_FILES} ${RES} "${CMAKE_CURRENT_SOURCE_DIR}/src/interface-cli.cpp")
target_include_directories(asar PRIVATE ${INCROOT} ${INCROOT}/common ${INCROOT}/arch ${INCROOT}/lib ${INCROOT}/util)
target_compile_options(asar PRIVATE ${DEFINE_PREFIX}INTERFACE_CLI)

