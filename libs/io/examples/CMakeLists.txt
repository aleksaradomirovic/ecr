# Copyright (C) 2025 Aleksa Radomirovic
# SPDX-License-Identifier: Apache-2.0

ecr_examples_dir()
link_libraries(ecr-io)

add_executable(
    echoback
        echoback.c
)

add_executable(
    helloworld
        helloworld.c
)
