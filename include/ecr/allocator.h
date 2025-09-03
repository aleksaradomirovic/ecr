/*
 * Copyright (C) 2025 Aleksa Radomirovic
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ECR_ALLOCATOR_H_
#define ECR_ALLOCATOR_H_


#include <stddef.h>

#include <ecr/status.h>
#include <ecr/version.h>

#ifdef __cplusplus
extern "C" {
#endif


struct ecr_allocator;
typedef struct ecr_allocator * ecr_allocator_t;

typedef ecr_status_t ecr_allocator_free_fn_t(ecr_allocator_t allocator, void **__restrict__ mem_ptr);
typedef ecr_status_t ecr_allocator_free_all_fn_t(ecr_allocator_t allocator);

typedef ecr_status_t ecr_allocator_allocate_fn_t(ecr_allocator_t allocator, void **__restrict__ mem_ptr, size_t mem_size);
typedef ecr_status_t ecr_allocator_reallocate_fn_t(ecr_allocator_t allocator, void **__restrict__ mem_ptr, size_t mem_size);

struct ecr_allocator_vtable {
    ecr_version_t version;

    unsigned int free_all_supported : 1;
    unsigned int reallocate_supported : 1;

    ecr_allocator_free_fn_t *free;
    ecr_allocator_free_all_fn_t *free_all;

    ecr_allocator_allocate_fn_t *allocate;
    ecr_allocator_reallocate_fn_t *reallocate;
};

struct ecr_allocator {
    const struct ecr_allocator_vtable *vtable;
};

ecr_status_t ecr_free(ecr_allocator_t allocator, void **__restrict__ mem_ptr);
ecr_status_t ecr_free_all(ecr_allocator_t allocator);
ecr_status_t ecr_allocate(ecr_allocator_t allocator, void **__restrict__ mem_ptr, size_t mem_size);
ecr_status_t ecr_reallocate(ecr_allocator_t allocator, void **__restrict__ mem_ptr, size_t mem_size);

extern ecr_allocator_t ecr_allocator_stdpool;


#ifdef __cplusplus
}
#endif


#endif
