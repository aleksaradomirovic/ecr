# Copyright (C) 2025 Aleksa Radomirovic
# SPDX-License-Identifier: Apache-2.0

set_directory_properties(PROPERTIES EXCLUDE_FROM_ALL ON)
link_libraries(io GTest::gtest GTest::gtest_main)

add_executable(stream_fd_test stream_fd_test.cpp)
gtest_discover_tests(stream_fd_test)
