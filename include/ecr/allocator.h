/*
* Copyright 2025 Aleksa Radomirovic
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*     https://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef ECR_ALLOCATOR_H_
#define ECR_ALLOCATOR_H_


#include <stdckdint.h>
#include <stddef.h>

#include <ecr/status.h>
#include <ecr/version.h>

#include <ecr/macro/restrict.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef ecr_status_t ecr_allocator_free_fn_t(void *data, void **restrict mem_ptr);
typedef ecr_status_t ecr_allocator_allocate_fn_t(void *data, void **restrict mem_ptr, size_t mem_size);
typedef ecr_status_t ecr_allocator_reallocate_fn_t(void *data, void **restrict mem_ptr, size_t mem_size);
typedef ecr_status_t ecr_allocator_allocate_array_fn_t(void *data, void **restrict mem_ptr, size_t mem_size, size_t mem_count);
typedef ecr_status_t ecr_allocator_reallocate_array_fn_t(void *data, void **restrict mem_ptr, size_t mem_size, size_t mem_count);

typedef struct ecr_allocator {
    ecr_version_t version;

    void *data;

    ecr_allocator_free_fn_t *free;
    ecr_allocator_allocate_fn_t *allocate;
    ecr_allocator_reallocate_fn_t *reallocate;

    ecr_allocator_allocate_array_fn_t *allocate_array;
    ecr_allocator_reallocate_array_fn_t *reallocate_array;
} ecr_allocator_t;

[[maybe_unused]]
static ecr_status_t ecr_free(ecr_allocator_t *allocator, void **restrict mem_ptr) {
    if(!allocator->free) {
        return ECR_ERROR_NOT_SUPPORTED;
    }

    return allocator->free(allocator->data, mem_ptr);
}

[[maybe_unused]]
static ecr_status_t ecr_allocate(ecr_allocator_t *allocator, void **restrict mem_ptr, size_t mem_size) {
    if(!allocator->allocate) {
        return ECR_ERROR_NOT_SUPPORTED;
    }

    return allocator->allocate(allocator->data, mem_ptr, mem_size);
}

[[maybe_unused]]
static ecr_status_t ecr_reallocate(ecr_allocator_t *allocator, void **restrict mem_ptr, size_t mem_size) {
    if(!allocator->reallocate) {
        return ECR_ERROR_NOT_SUPPORTED;
    }

    return allocator->reallocate(allocator->data, mem_ptr, mem_size);
}

[[maybe_unused]]
static ecr_status_t ecr_allocate_array(ecr_allocator_t *allocator, void **restrict mem_ptr, size_t mem_size, size_t mem_count) {
    if(!allocator->allocate_array) {
        size_t total_mem_size;
        if(ckd_mul(&total_mem_size, mem_size, mem_count)) {
            return ECR_ERROR_NUMERICAL_OVERFLOW;
        }

        return ecr_allocate(allocator, mem_ptr, total_mem_size);
    }

    return allocator->allocate_array(allocator->data, mem_ptr, mem_size, mem_count);
}

[[maybe_unused]]
static ecr_status_t ecr_reallocate_array(ecr_allocator_t *allocator, void **restrict mem_ptr, size_t mem_size, size_t mem_count) {
    if(!allocator->reallocate_array) {
        size_t total_mem_size;
        if(ckd_mul(&total_mem_size, mem_size, mem_count)) {
            return ECR_ERROR_NUMERICAL_OVERFLOW;
        }

        return ecr_reallocate(allocator, mem_ptr, total_mem_size);
    }

    return allocator->reallocate_array(allocator->data, mem_ptr, mem_size, mem_count);
}


#ifdef __cplusplus
}
#endif


#endif
