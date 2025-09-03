/*
 * Copyright (C) 2025 Aleksa Radomirovic
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ecr/stream.h"

ecr_status_t ecr_stream_close(ecr_stream_t stream) {
    if(!stream->vtable->closeable) {
        return ECR_SUCCESS;
    }

    return stream->vtable->close(stream);
}

ecr_status_t ecr_stream_read(ecr_stream_t stream, void *buffer, size_t *__restrict__ length) {
    if(!stream->vtable->read_supported) {
        return ECR_ERROR_NOT_SUPPORTED;
    }

    return stream->vtable->read(stream, buffer, length);
}

ecr_status_t ecr_stream_write(ecr_stream_t stream, const void *buffer, size_t *__restrict__ length) {
    if(!stream->vtable->write_supported) {
        return ECR_ERROR_NOT_SUPPORTED;
    }

    return stream->vtable->write(stream, buffer, length);
}


ecr_status_t ecr_stream_read_full(ecr_stream_t stream, void *buffer, size_t *__restrict__ length) {
    ecr_status_t status = ECR_SUCCESS;

    size_t total = 0;
    while(total < *length) {
        size_t remaining = *length - total;
        status = ecr_stream_read(stream, buffer + total, &remaining);
        total += remaining;

        if(status != ECR_SUCCESS) {
            break;
        }
    }

    *length = total;
    return status;
}

ecr_status_t ecr_stream_write_full(ecr_stream_t stream, const void *buffer, size_t *__restrict__ length) {
    ecr_status_t status = ECR_SUCCESS;

    size_t total = 0;
    while(total < *length) {
        size_t remaining = *length - total;
        status = ecr_stream_write(stream, buffer + total, &remaining);
        total += remaining;

        if(status != ECR_SUCCESS) {
            break;
        }
    }

    *length = total;
    return status;
}
