/*
 * Copyright (C) 2025 Aleksa Radomirovic
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ecr/stream.h>

int main() {
    ecr_status_t status;

    char buf[8192];
    size_t len = sizeof(buf);
    status = ecr_stream_read(ecr_stdin, buf, &len);
    if(status) {
        return 1;
    }

    status = ecr_stream_write_full(ecr_stdout, buf, &len);
    if(status) {
        return 2;
    }

    return 0;
}
