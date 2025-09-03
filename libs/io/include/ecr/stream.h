/*
 * Copyright (C) 2025 Aleksa Radomirovic
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ECR_STREAM_H_
#define ECR_STREAM_H_

#include <ecr/features.h>

#include <stddef.h>

#include <ecr/status.h>
#include <ecr/version.h>

#ifdef __cplusplus
extern "C" {
#endif


struct ecr_stream;
typedef struct ecr_stream * ecr_stream_t;

typedef ecr_status_t ecr_stream_close_fn_t(ecr_stream_t stream);
typedef ecr_status_t ecr_stream_read_fn_t(ecr_stream_t stream, void *buffer, size_t *__restrict__ length);
typedef ecr_status_t ecr_stream_write_fn_t(ecr_stream_t stream, const void *buffer, size_t *__restrict__ length);

struct ecr_stream_vtable {
    ecr_version_t version;

    unsigned int closeable : 1;
    unsigned int read_supported : 1;
    unsigned int write_supported : 1;

    ecr_stream_close_fn_t *close;
    ecr_stream_read_fn_t *read;
    ecr_stream_write_fn_t *write;
};

struct ecr_stream {
    const struct ecr_stream_vtable *vtable;
};

ecr_status_t ecr_stream_close(ecr_stream_t stream);
ecr_status_t ecr_stream_read(ecr_stream_t stream, void *buffer, size_t *__restrict__ length);
ecr_status_t ecr_stream_write(ecr_stream_t stream, const void *buffer, size_t *__restrict__ length);
ecr_status_t ecr_stream_read_full(ecr_stream_t stream, void *buffer, size_t *__restrict__ length);
ecr_status_t ecr_stream_write_full(ecr_stream_t stream, const void *buffer, size_t *__restrict__ length);

extern ecr_stream_t ecr_stdin;
extern ecr_stream_t ecr_stdout;
extern ecr_stream_t ecr_stderr;


#ifdef __cplusplus
}
#endif


#endif
