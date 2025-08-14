# Copyright (C) 2025 Aleksa Radomirovic
# SPDX-License-Identifier: Apache-2.0

option(BUILD_TESTING "Build tests" OFF)

if(NOT BUILD_TESTING)
    return()
endif()

enable_language(CXX)
include(CTest)
find_package(GTest REQUIRED)
