# Copyright (C) 2025 Aleksa Radomirovic
# SPDX-License-Identifier: Apache-2.0

add_library(
    ecr-io
)
target_include_directories(
    ecr-io
    PUBLIC
    include
)
target_link_libraries(
    ecr-io
    PUBLIC
    ecr-core
)
target_sources(
    ecr-io
    PRIVATE
        src/stream/generic.c
)
if(NOT ECR_FREESTANDING)
    if(ECR_USE_POSIX)
        target_sources(
            ecr-io
            PRIVATE
                src/stream/posix.c
                src/stream/posix.h
        )
    endif()
endif()
add_subdirectory(tests)
add_subdirectory(examples)
