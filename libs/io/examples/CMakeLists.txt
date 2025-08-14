# Copyright (C) 2025 Aleksa Radomirovic
# SPDX-License-Identifier: Apache-2.0

set_directory_properties(PROPERTIES EXCLUDE_FROM_ALL ON)
link_libraries(io)

add_executable(
    io_echo
        echo/echo.c
)
