/*
 * Copyright (C) 2025 Aleksa Radomirovic
 * SPDX-License-Identifier: Apache-2.0
 */

#include <limits.h>

#include "ecr/status.h"

const char * ecr_status_string(ecr_status_t status) {
    switch(status) {
        case ECR_SUCCESS:
            return "success";
        
        default:
        case ECR_ERROR_UNKNOWN:
            return "unknown error";

        case ECR_ERROR_NOT_SUPPORTED:
            return "not supported";

        case ECR_ERROR_END_OF_STREAM:
            return "end of file or stream reached";
    }
}
