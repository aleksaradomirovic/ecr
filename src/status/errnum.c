/*
 * Copyright (C) 2025 Aleksa Radomirovic
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ecr/status.h"

ecr_status_t ecr_status_from_errnum(int errnum) {
    if(errnum <= 0) {
        return ECR_ERROR_UNKNOWN;
    }

    switch(errnum) {
#if defined(ENOTSUP)
        case ENOTSUP:
            return ECR_ERROR_NOT_SUPPORTED;
#endif
#if defined(EOPNOTSUPP) && (!defined(ENOTSUP) || EOPNOTSUPP != ENOTSUP)
        case EOPNOTSUPP:
            return ECR_ERROR_NOT_SUPPORTED;
#endif
    }

    return (ecr_status_t) (-errnum);
}
