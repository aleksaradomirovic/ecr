/*
 * Copyright (C) 2025 Aleksa Radomirovic
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include <ecr/allocator.h>

#include <ecr/allocator/standard.h>

#if __STDC_HOSTED__

class standard_allocator : public ::testing::Test {
  protected:
    ecr_allocator_t allocator = ECR_ALLOCATOR_STANDARD_INIT;
    volatile void *mem;
};

TEST_F(standard_allocator, allocate) {
    ASSERT_EQ(ecr_allocate(&allocator, (void **) (&mem), 16), ECR_SUCCESS);
    ASSERT_EQ(ecr_free(&allocator, (void **) (&mem)), ECR_SUCCESS);
}

TEST_F(standard_allocator, reallocate) {
    ASSERT_EQ(ecr_allocate(&allocator, (void **) (&mem), 16), ECR_SUCCESS);
    EXPECT_EQ(ecr_reallocate(&allocator, (void **) (&mem), 32), ECR_SUCCESS);
    ASSERT_EQ(ecr_free(&allocator, (void **) (&mem)), ECR_SUCCESS);
}

TEST_F(standard_allocator, allocate_array) {
    ASSERT_EQ(ecr_allocate_array(&allocator, (void **) (&mem), 8, 2), ECR_SUCCESS);
    ASSERT_EQ(ecr_free(&allocator, (void **) (&mem)), ECR_SUCCESS);
}

TEST_F(standard_allocator, reallocate_array) {
    ASSERT_EQ(ecr_allocate_array(&allocator, (void **) (&mem), 8, 2), ECR_SUCCESS);
    EXPECT_EQ(ecr_reallocate_array(&allocator, (void **) (&mem), 8, 4), ECR_SUCCESS);
    ASSERT_EQ(ecr_free(&allocator, (void **) (&mem)), ECR_SUCCESS);
}

TEST_F(standard_allocator, allocate_array_overflow) {
    ecr_status_t status = ecr_allocate_array(&allocator, (void **) (&mem), SIZE_MAX, SIZE_MAX);
    ASSERT_TRUE(status == ECR_ERROR_NUMERICAL_OVERFLOW || status == ECR_ERROR_OUT_OF_MEMORY);
}

TEST_F(standard_allocator, reallocate_array_overflow) {
    ASSERT_EQ(ecr_allocate_array(&allocator, (void **) (&mem), 8, 2), ECR_SUCCESS);
    ecr_status_t status = ecr_reallocate_array(&allocator, (void **) (&mem), SIZE_MAX, SIZE_MAX);
    EXPECT_TRUE(status == ECR_ERROR_NUMERICAL_OVERFLOW || status == ECR_ERROR_OUT_OF_MEMORY);
    ASSERT_EQ(ecr_free(&allocator, (void **) (&mem)), ECR_SUCCESS);
}


#endif
