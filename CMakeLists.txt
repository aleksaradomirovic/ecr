# Copyright (C) 2025 Aleksa Radomirovic
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.31)
project(extensible-c-runtime LANGUAGES NONE)

include(tools/cmake/System.cmake)
include(tools/cmake/Features.cmake)
include(tools/cmake/BuildType.cmake)
include(tools/cmake/Testing.cmake)

add_library(
    ecr-core
)
target_include_directories(
    ecr-core
    PUBLIC
    include
)
target_sources(
    ecr-core
    PRIVATE
        src/allocator/generic.c

        src/status/errnum.c
        src/status/string.c
)
if(NOT BUILD_FREESTANDING)
    target_sources(
        ecr-core
        PRIVATE
            src/allocator/stdpool_hosted.c
    )
endif()
add_subdirectory(tests)
add_subdirectory(examples)

add_subdirectory(libs/io)
