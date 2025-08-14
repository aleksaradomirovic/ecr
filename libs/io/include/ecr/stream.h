/*
* Copyright 2025 Aleksa Radomirovic
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*     https://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef ECR_STREAM_H_
#define ECR_STREAM_H_


#include <stddef.h>

#include <ecr/status.h>
#include <ecr/version.h>

#include <ecr/macro/restrict.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef ecr_status_t ecr_stream_close_fn_t(void *data);

typedef ecr_status_t ecr_stream_read_fn_t(void *data, void *buffer, size_t *restrict length);
typedef ecr_status_t ecr_stream_write_fn_t(void *data, const void *buffer, size_t *restrict length);

typedef struct ecr_stream {
    ecr_version_t version;

    void *data;

    ecr_stream_close_fn_t *close;

    ecr_stream_read_fn_t *read;
    ecr_stream_write_fn_t *write;
} ecr_stream_t;

[[maybe_unused]]
static ecr_status_t ecr_stream_close(ecr_stream_t *stream) {
    if(!stream->close) {
        return ECR_SUCCESS;
    }

    return stream->close(stream->data);
}

[[maybe_unused]]
static ecr_status_t ecr_stream_read(ecr_stream_t *stream, void *buffer, size_t *restrict length) {
    if(!stream->read) {
        return ECR_ERROR_NOT_SUPPORTED;
    }

    return stream->read(stream->data, buffer, length);
}

[[maybe_unused]]
static ecr_status_t ecr_stream_readn(ecr_stream_t *stream, void *buffer, size_t *restrict length) {
    ecr_status_t status;

    size_t total = 0;
    while(total < *length) {
        size_t read_length = *length - total;
        status = ecr_stream_read(stream, (void *) ((unsigned char *) buffer + total), &read_length);
        if(status != ECR_SUCCESS) {
            break;
        }
        total += read_length;
    }

    *length = total;
    return status;
}

[[maybe_unused]]
static ecr_status_t ecr_stream_write(ecr_stream_t *stream, const void *buffer, size_t *restrict length) {
    if(!stream->write) {
        return ECR_ERROR_NOT_SUPPORTED;
    }

    return stream->write(stream->data, buffer, length);
}

[[maybe_unused]]
static ecr_status_t ecr_stream_writen(ecr_stream_t *stream, const void *buffer, size_t *restrict length) {
    ecr_status_t status;

    size_t total = 0;
    while(total < *length) {
        size_t write_length = *length - total;
        status = ecr_stream_write(stream, (const void *) ((const unsigned char *) buffer + total), &write_length);
        if(status != ECR_SUCCESS) {
            break;
        }
        total += write_length;
    }

    *length = total;
    return status;
}


#ifdef __cplusplus
}
#endif


#endif
