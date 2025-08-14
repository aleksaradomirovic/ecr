# Copyright (C) 2025 Aleksa Radomirovic
# SPDX-License-Identifier: Apache-2.0

add_library(
    io
        src/stream/posix.c
        src/stream/posix.h
)
set_target_properties(
    io
    PROPERTIES
        OUTPUT_NAME ecr-io
)
target_include_directories(
    io
    PUBLIC
        include
)
target_link_libraries(
    io
    PUBLIC
        core
)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

add_subdirectory(examples)
