/*
 * Copyright (C) 2025 Aleksa Radomirovic
 * SPDX-License-Identifier: Apache-2.0
 */

#include <limits.h>

#include "posix.h"

static ecr_status_t ecr_stream_posix_close(ecr_stream_t stream_ptr) {
    struct ecr_stream_posix *stream = (struct ecr_stream_posix *) stream_ptr;
    int fd = stream->fd;

    if(close(fd)) {
        int err = errno;
        __builtin_assume(err != 0);
        return ecr_status_from_errnum(err);
    }

    return ECR_SUCCESS;
}

static ecr_status_t ecr_stream_posix_read(ecr_stream_t stream_ptr, void *buffer, size_t *__restrict__ length) {
    struct ecr_stream_posix *stream = (struct ecr_stream_posix *) stream_ptr;
    int fd = stream->fd;

    size_t read_length = *length;
    if(read_length > SSIZE_MAX) {
        read_length = SSIZE_MAX;
    }

    ssize_t actual_read_length = read(fd, buffer, read_length);
    if(actual_read_length < 0) {
        *length = 0;
        int err = errno;
        __builtin_assume(err != 0);
        return ecr_status_from_errnum(err);
    }
    if(actual_read_length == 0) {
        *length = 0;
        return ECR_ERROR_END_OF_STREAM;
    }

    *length = (size_t) actual_read_length;
    return ECR_SUCCESS;
}

static ecr_status_t ecr_stream_posix_write(ecr_stream_t stream_ptr, const void *buffer, size_t *__restrict__ length) {
    struct ecr_stream_posix *stream = (struct ecr_stream_posix *) stream_ptr;
    int fd = stream->fd;

    size_t write_length = *length;
    if(write_length > SSIZE_MAX) {
        write_length = SSIZE_MAX;
    }

    ssize_t actual_write_length = write(fd, buffer, write_length);
    if(actual_write_length < 0) {
        *length = 0;
        int err = errno;
        __builtin_assume(err != 0);
        return ecr_status_from_errnum(err);
    }

    *length = (size_t) actual_write_length;
    return ECR_SUCCESS;
}

static const struct ecr_stream_vtable ecr_stream_posix_vtable = {
    .version = { 0, 0 },

    .closeable = 1,
    .read_supported = 1,
    .write_supported = 1,

    .close = ecr_stream_posix_close,
    .read = ecr_stream_posix_read,
    .write = ecr_stream_posix_write,
};

ecr_status_t ecr_stream_posix_nodupfd(struct ecr_stream_posix *stream, int fd) {
    stream->vtable = &ecr_stream_posix_vtable;
    stream->fd = fd;

    return ECR_SUCCESS;
}

ecr_status_t ecr_stream_posix_dupfd(struct ecr_stream_posix *stream, int fd) {
    fd = dup(fd);
    if(fd < 0) {
        int err = errno;
        __builtin_assume(err != 0);
        return ecr_status_from_errnum(err);
    }

    return ecr_stream_posix_nodupfd(stream, fd);
}

static struct ecr_stream_posix ecr_streams_std_posix[3] = {
    {
        &ecr_stream_posix_vtable,
        STDIN_FILENO,
    },
    {
        &ecr_stream_posix_vtable,
        STDOUT_FILENO,
    },
    {
        &ecr_stream_posix_vtable,
        STDERR_FILENO,
    }
};

ecr_stream_t ecr_stdin = (ecr_stream_t) &ecr_streams_std_posix[0];
ecr_stream_t ecr_stdout = (ecr_stream_t) &ecr_streams_std_posix[1];
ecr_stream_t ecr_stderr = (ecr_stream_t) &ecr_streams_std_posix[2];
