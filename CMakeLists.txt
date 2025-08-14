# Copyright (C) 2025 Aleksa Radomirovic
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.31)
project(extensible-c-runtime LANGUAGES C)

include(tools/scripts/cmake/LanguageStandard.cmake)
include(tools/scripts/cmake/SystemTarget.cmake)
include(tools/scripts/cmake/BuildType.cmake)
include(tools/scripts/cmake/Testing.cmake)

add_library(
    core
        src/status.c
)
set_target_properties(
    core
    PROPERTIES
        OUTPUT_NAME ecr-core
)
target_include_directories(
    core
    PUBLIC
        include
)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

add_subdirectory(libs/io)
