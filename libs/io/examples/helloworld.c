/*
 * Copyright (C) 2025 Aleksa Radomirovic
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>

#include <ecr/stream.h>

#define HELLO_WORLD "Hello, World!\n"

int main() {
    size_t len = strlen(HELLO_WORLD);
    if(ecr_stream_write_full(ecr_stdout, HELLO_WORLD, &len)) {
        return 1;
    }

    return 0;
}
