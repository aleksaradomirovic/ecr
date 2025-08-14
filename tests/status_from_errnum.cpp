/*
 * Copyright (C) 2025 Aleksa Radomirovic
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include <ecr/status.h>

#if __STDC_HOSTED__

TEST(status_from_errnum, enotsup) {
    EXPECT_EQ(ecr_status_from_errnum(ENOTSUP), ECR_ERROR_NOT_SUPPORTED);
}

TEST(status_from_errnum, einval) {
    EXPECT_EQ(ecr_status_from_errnum(EINVAL), ECR_ERROR_INVALID_ARGUMENT);
}

TEST(status_from_errnum, eoverflow) {
    EXPECT_EQ(ecr_status_from_errnum(EOVERFLOW), ECR_ERROR_NUMERICAL_OVERFLOW);
}

TEST(status_from_errnum, enomem) {
    EXPECT_EQ(ecr_status_from_errnum(ENOMEM), ECR_ERROR_OUT_OF_MEMORY);
}

#endif
