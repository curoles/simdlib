cmake_minimum_required(VERSION 3.16)

# Top CMake script for building SIMDLIB.
# Author: Igor Lesik 2022

if(DEFINED CROSS_TOOLCHAIN)
    set(CMAKE_CROSSCOMPILING TRUE)
    set(CMAKE_TOOLCHAIN_FILE ${CROSS_TOOLCHAIN}-toolchain.cmake)
    if(NOT EXISTS ${CMAKE_SOURCE_DIR}/${CROSS_TOOLCHAIN}-toolchain.cmake)
        message(FATAL_ERROR "wrong Toolchain name, file ${CROSS_TOOLCHAIN}-toolchain.cmake does not exist")
    endif()
    if (${CROSS_TOOLCHAIN} MATCHES "tachyum") # cmake -DCROSS_TOOLCHAIN=tachyum
        if(NOT DEFINED TACHY_TOOLCHAIN_HOME)
            message(FATAL_ERROR "TACHY_TOOLCHAIN_HOME not defined, do 'cmake -DTACHY_TOOLCHAIN_HOME=your_toolchain/install/set0'")
        endif()
    endif()
endif()

project(SIMDLIB
    VERSION 0.1.0
    DESCRIPTION "C++ SIMD Library"
    LANGUAGES ASM C CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_FLAGS "-O2 -Werror -Wall -Wextra -static")
set(CMAKE_CXX_FLAGS "-O2 -Werror -Wall -Wextra -static")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--gc-sections")

message(STATUS "Host   CPU: ${CMAKE_HOST_SYSTEM_PROCESSOR}")
message(STATUS "Target CPU: ${CMAKE_SYSTEM_PROCESSOR}")
set(SIMDLIB_TARGET_ARCH ${CMAKE_SYSTEM_PROCESSOR})
if (${CROSS_TOOLCHAIN} MATCHES "tachyum")
    set(SIMDLIB_TARGET_ARCH "tachyum")
    set(FSIM ${TACHY_TOOLCHAIN_HOME}/bin/tachy-run)
endif()
message(STATUS "Target ARCH: ${SIMDLIB_TARGET_ARCH}")

include_directories(.)

# Install inside the build directory.
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

enable_testing()

add_subdirectory(test)