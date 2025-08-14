/*
 * Copyright (C) 2025 Aleksa Radomirovic
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ecr/stream.h>
#include <ecr/stream/fd.h>

int main() {
    ecr_stream_t stream;
    char buffer[8192];

    if(ecr_stream_fd_init(&stream, STDIN_FILENO)) {
        return 1;
    }

    size_t length = sizeof(buffer);
    if(ecr_stream_read(&stream, buffer, &length)) {
        return 2;
    }
    
    if(ecr_stream_close(&stream)) {
        return 3;
    }

    if(ecr_stream_fd_init(&stream, STDOUT_FILENO)) {
        return 4;
    }

    if(ecr_stream_writen(&stream, buffer, &length)) {
        return 5;
    }
    
    if(ecr_stream_close(&stream)) {
        return 6;
    }

    return 0;
}
