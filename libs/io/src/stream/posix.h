/*
 * Copyright (C) 2025 Aleksa Radomirovic
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ecr/stream/posix.h"

__attribute__((visibility ("hidden"))) ecr_status_t ecr_stream_posix_nodupfd(struct ecr_stream_posix *stream, int fd);
