# Copyright (C) 2025 Aleksa Radomirovic
# SPDX-License-Identifier: Apache-2.0

if((NOT DEFINED CMAKE_BUILD_TYPE) OR (CMAKE_BUILD_TYPE STREQUAL ""))
    set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()

option(BUILD_SHARED_LIBS "Build as shared libraries" ON)

if(NOT DEFINED CMAKE_INTERPROCEDURAL_OPTIMIZATION)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
endif()
