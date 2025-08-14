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

#ifndef ECR_ALLOCATOR_STANDARD_H_
#define ECR_ALLOCATOR_STANDARD_H_


#if __STDC_HOSTED__
#include <stdlib.h>
#endif

#include <ecr/allocator.h>

#ifdef __cplusplus
extern "C" {
#endif


#if __STDC_HOSTED__

[[maybe_unused]]
static ecr_status_t ecr_allocator_standard_free(void *, void **restrict mem_ptr) {
    free(*mem_ptr);
    *mem_ptr = NULL;
    return ECR_SUCCESS;
}

[[maybe_unused]]
static ecr_status_t ecr_allocator_standard_allocate(void *, void **restrict mem_ptr, size_t mem_size) {
    void *mem = malloc(mem_size);
    if(!mem) {
        return ECR_STATUS_ERRNO;
    }

    *mem_ptr = mem;
    return ECR_SUCCESS;
}

[[maybe_unused]]
static ecr_status_t ecr_allocator_standard_reallocate(void *, void **restrict mem_ptr, size_t mem_size) {
    void *mem = realloc(*mem_ptr, mem_size);
    if(!mem) {
        return ECR_STATUS_ERRNO;
    }

    *mem_ptr = mem;
    return ECR_SUCCESS;
}

#define ECR_ALLOCATOR_STANDARD_INIT (ecr_allocator_t) { \
    .version = ECR_VERSION(0, 0), \
    .data = NULL, \
    .free = ecr_allocator_standard_free, \
    .allocate = ecr_allocator_standard_allocate, \
    .reallocate = ecr_allocator_standard_reallocate, \
}

#endif


#ifdef __cplusplus
}
#endif


#endif
