# Copyright (C) 2025 Aleksa Radomirovic
# SPDX-License-Identifier: Apache-2.0

if((NOT DEFINED CMAKE_BUILD_TYPE) OR (CMAKE_BUILD_TYPE STREQUAL ""))
    set(CMAKE_BUILD_TYPE "Release")
endif()

if(BUILD_FREESTANDING AND NOT DEFINED BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS OFF)
endif()

option(BUILD_SHARED_LIBS "Build as shared libraries" ON)

if(BUILD_SHARED_LIBS)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
endif()
