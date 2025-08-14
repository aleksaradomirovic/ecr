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

#ifndef ECR_STATUS_H_
#define ECR_STATUS_H_


#if __STDC_HOSTED__
#include <errno.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


typedef enum ecr_status : int {
    ECR_SUCCESS = 0,

    ECR_ERROR_UNKNOWN = 0x001,

    // API errors
    ECR_ERROR_NOT_SUPPORTED    = 0x010,
    ECR_ERROR_INVALID_ARGUMENT = 0x011,

    // Logic errors
    ECR_ERROR_NUMERICAL_OVERFLOW = 0x020,

    // System errors
    ECR_ERROR_OUT_OF_MEMORY = 0x030,
} ecr_status_t;

const char * ecr_status_string(ecr_status_t status);

#if __STDC_HOSTED__

ecr_status_t ecr_status_from_errnum(int errnum);

#define ECR_STATUS_ERRNO ecr_status_from_errnum(errno)

#endif


#ifdef __cplusplus
}
#endif


#endif
