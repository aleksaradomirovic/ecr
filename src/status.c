/*
 * Copyright (C) 2025 Aleksa Radomirovic
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ecr/status.h"

#if __STDC_HOSTED__

ecr_status_t ecr_status_from_errnum(int errnum) {
    if(errnum <= 0) {
        return ECR_ERROR_UNKNOWN;
    }

    switch(errnum) {
        case ENOTSUP:
            return ECR_ERROR_NOT_SUPPORTED;
        case EINVAL:
            return ECR_ERROR_INVALID_ARGUMENT;

        case EOVERFLOW:
            return ECR_ERROR_NUMERICAL_OVERFLOW;

        case ENOMEM:
            return ECR_ERROR_OUT_OF_MEMORY;
    }

    return (ecr_status_t) (-errnum);
}

#endif
