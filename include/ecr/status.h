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

#ifndef ECR_STATUS_H_
#define ECR_STATUS_H_


#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif


#define ECR_ERROR_API (0x010)
#define ECR_ERROR_API_MAX (0x01f)

#define ECR_ERROR_IO (0x100)
#define ECR_ERROR_IO_MAX (0x10f)

typedef enum : int {
    ECR_SUCCESS = 0,

    ECR_ERROR_UNKNOWN = 0x001,

    ECR_ERROR_NOT_SUPPORTED = ECR_ERROR_API + 0,

    ECR_ERROR_END_OF_STREAM = ECR_ERROR_IO + 0,
} ecr_status_t;

const char * ecr_status_string(ecr_status_t status);

ecr_status_t ecr_status_from_errnum(int errnum);

#define ecr_status_errno (ecr_status_from_errnum(errno))


#ifdef __cplusplus
}
#endif


#endif
