# Copyright (C) 2025 Aleksa Radomirovic
# SPDX-License-Identifier: Apache-2.0

set_directory_properties(PROPERTIES EXCLUDE_FROM_ALL ON)
link_libraries(core GTest::gtest GTest::gtest_main)

add_executable(status_from_errnum status_from_errnum.cpp)
gtest_discover_tests(status_from_errnum)

add_executable(standard_allocator standard_allocator.cpp)
gtest_discover_tests(standard_allocator)
