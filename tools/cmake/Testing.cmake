# Copyright (C) 2025 Aleksa Radomirovic
# SPDX-License-Identifier: Apache-2.0

macro(ecr_tests_dir)
    if(NOT BUILD_TESTING)
        return()
    endif()

    set_directory_properties(PROPERTIES EXCLUDE_FROM_ALL ON)
endmacro()

macro(ecr_examples_dir)
    if(NOT BUILD_EXAMPLES)
        return()
    endif()

    set_directory_properties(PROPERTIES EXCLUDE_FROM_ALL ON)
endmacro()

option(BUILD_TESTING "Build tests" OFF)
option(BUILD_EXAMPLES "Build examples" OFF)

if(BUILD_TESTING)
    enable_language(CXX)

    find_package(GTest REQUIRED)
endif()
