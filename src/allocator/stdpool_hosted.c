/*
 * Copyright (C) 2025 Aleksa Radomirovic
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdlib.h>

#include "ecr/allocator.h"

static ecr_status_t ecr_stdpool_free(ecr_allocator_t, void **__restrict__ mem_ptr) {
    free(*mem_ptr);
    return ECR_SUCCESS;
}

static ecr_status_t ecr_stdpool_allocate(ecr_allocator_t, void **__restrict__ mem_ptr, size_t mem_size) {
    void *mem = malloc(mem_size);
    if(!mem) {
        int err = errno;
        __builtin_assume(err != 0);
        return ecr_status_from_errnum(err);
    }

    *mem_ptr = mem;
    return ECR_SUCCESS;
}

static ecr_status_t ecr_stdpool_reallocate(ecr_allocator_t, void **__restrict__ mem_ptr, size_t mem_size) {
    void *mem = realloc(*mem_ptr, mem_size);
    if(!mem) {
        int err = errno;
        __builtin_assume(err != 0);
        return ecr_status_from_errnum(err);
    }

    *mem_ptr = mem;
    return ECR_SUCCESS;
}

static const struct ecr_allocator_vtable ecr_stdpool_vtable = {
    .version = { 0, 0 },

    .free_all_supported = 0,
    .reallocate_supported = 1,

    .free = ecr_stdpool_free,
    .allocate = ecr_stdpool_allocate,
    .reallocate = ecr_stdpool_reallocate,
};

static struct ecr_allocator ecr_stdpool = {
    .vtable = &ecr_stdpool_vtable,
};

ecr_allocator_t ecr_allocator_stdpool = &ecr_stdpool;
