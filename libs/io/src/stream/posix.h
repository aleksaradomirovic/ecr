/*
 * Copyright (C) 2025 Aleksa Radomirovic
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#if __STDC_HOSTED__ && __has_include(<features.h>)
#include <features.h>
#endif

#if _POSIX_C_SOURCE >= 1

#include <ecr/macro/internal.h>

#include "ecr/stream.h"

struct posix_stream_data {
    int fd;
};

internal ecr_status_t ecr_stream_fd_init_nodup(ecr_stream_t *stream, int fd);

internal ecr_status_t ecr_stream_fd_close(void *data);
internal ecr_status_t ecr_stream_fd_read(void *data, void *buffer, size_t *restrict length);
internal ecr_status_t ecr_stream_fd_write(void *data, const void *buffer, size_t *restrict length);

#endif
