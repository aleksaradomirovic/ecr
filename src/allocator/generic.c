/*
 * Copyright (C) 2025 Aleksa Radomirovic
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ecr/allocator.h"

ecr_status_t ecr_free(ecr_allocator_t allocator, void **__restrict__ mem_ptr) {
    return allocator->vtable->free(allocator, mem_ptr);
}

ecr_status_t ecr_free_all(ecr_allocator_t allocator) {
    if(!allocator->vtable->free_all_supported) {
        return ECR_ERROR_NOT_SUPPORTED;
    }

    return allocator->vtable->free_all(allocator);
}

ecr_status_t ecr_allocate(ecr_allocator_t allocator, void **__restrict__ mem_ptr, size_t mem_size) {
    return allocator->vtable->allocate(allocator, mem_ptr, mem_size);
}

ecr_status_t ecr_reallocate(ecr_allocator_t allocator, void **__restrict__ mem_ptr, size_t mem_size) {
    if(!allocator->vtable->reallocate_supported) {
        return ECR_ERROR_NOT_SUPPORTED;
    }

    return allocator->vtable->reallocate(allocator, mem_ptr, mem_size);
}
