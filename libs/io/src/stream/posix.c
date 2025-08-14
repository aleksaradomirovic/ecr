/*
 * Copyright (C) 2025 Aleksa Radomirovic
 * SPDX-License-Identifier: Apache-2.0
 */

#include <limits.h>

#include <ecr/allocator.h>

#include <ecr/allocator/standard.h>

#include "ecr/stream/fd.h"

#include "posix.h"

#if _POSIX_C_SOURCE >= 1

ecr_status_t ecr_stream_fd_close(void *data_ptr) {
    struct posix_stream_data *data = data_ptr;
    if(close(data->fd)) {
        return ECR_STATUS_ERRNO;
    }

    ecr_allocator_t allocator = ECR_ALLOCATOR_STANDARD_INIT;
    ECR_ERROR_GUARD(ecr_free(&allocator, &data_ptr));

    return ECR_SUCCESS;
}

ecr_status_t ecr_stream_fd_read(void *data, void *buffer, size_t *restrict length) {
    int fd = ((struct posix_stream_data *) data)->fd;

    size_t read_length = *length;
    if(read_length > SSIZE_MAX) {
        read_length = SSIZE_MAX;
    }

    ssize_t actual_read_length = read(fd, buffer, read_length);
    if(actual_read_length < 0) {
        *length = 0;
        return ECR_STATUS_ERRNO;
    } else if(actual_read_length == 0) {
        *length = 0;
        return ECR_ERROR_END_OF_FILE;
    }

    *length = (size_t) actual_read_length;
    return ECR_SUCCESS;
}

ecr_status_t ecr_stream_fd_write(void *data, const void *buffer, size_t *restrict length) {
    int fd = ((struct posix_stream_data *) data)->fd;

    size_t write_length = *length;
    if(write_length > SSIZE_MAX) {
        write_length = SSIZE_MAX;
    }

    ssize_t actual_write_length = write(fd, buffer, write_length);
    if(actual_write_length < 0) {
        *length = 0;
        return ECR_STATUS_ERRNO;
    }

    *length = (size_t) actual_write_length;
    return ECR_SUCCESS;
}

ecr_status_t ecr_stream_fd_init_nodup(ecr_stream_t *stream, int fd) {
    ecr_allocator_t allocator = ECR_ALLOCATOR_STANDARD_INIT;
    struct posix_stream_data *data;
    ECR_ERROR_GUARD(ecr_allocate(&allocator, (void **) &data, sizeof(struct posix_stream_data)));

    data->fd = fd;
    
    stream->version = ECR_VERSION(0, 0);
    stream->data = data;

    stream->close = ecr_stream_fd_close;
    stream->read = ecr_stream_fd_read;
    stream->write = ecr_stream_fd_write;

    return ECR_SUCCESS;
}

ecr_status_t ecr_stream_fd_init(ecr_stream_t *stream, int fd) {
    fd = dup(fd);
    if(fd < 0) {
        return ECR_STATUS_ERRNO;
    }

    ECR_ERROR_GUARD_DESTRUCT(ecr_stream_fd_init_nodup(stream, fd), { close(fd); });
    return ECR_SUCCESS;
}

#endif
