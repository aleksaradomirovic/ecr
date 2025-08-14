/*
 * Copyright (C) 2025 Aleksa Radomirovic
 * SPDX-License-Identifier: Apache-2.0
 */

#include <unistd.h>

#include <gtest/gtest.h>

#include <ecr/stream.h>

#include <ecr/stream/fd.h>

class stream_fd_test : public ::testing::Test {
  protected:
    ecr_stream_t in, out;

    void SetUp() override {
        ASSERT_EQ(ecr_stream_fd_init(&in, STDIN_FILENO), ECR_SUCCESS);
        ASSERT_EQ(ecr_stream_fd_init(&out, STDOUT_FILENO), ECR_SUCCESS);
    }

    void TearDown() override {
        ASSERT_EQ(ecr_stream_close(&in), ECR_SUCCESS);
        ASSERT_EQ(ecr_stream_close(&out), ECR_SUCCESS);
    }
};

TEST_F(stream_fd_test, open_close) {
    
}
