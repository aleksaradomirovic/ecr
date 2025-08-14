# Copyright (C) 2025 Aleksa Radomirovic
# SPDX-License-Identifier: Apache-2.0

set(ECR_SUPPORTED_C_STANDARDS 23)

if(NOT DEFINED CMAKE_C_STANDARD)
    list(GET ECR_SUPPORTED_C_STANDARDS -1 CMAKE_C_STANDARD)
elseif(NOT CMAKE_C_STANDARD IN_LIST ECR_SUPPORTED_C_STANDARDS)
    message(SEND_ERROR "Unsupported C standard '${CMAKE_C_STANDARD}'")
endif()

if(NOT DEFINED CMAKE_C_EXTENSIONS)
    set(CMAKE_C_EXTENSIONS OFF)
endif()

if(NOT DEFINED ECR_POSIX_SOURCE)
    set(ECR_POSIX_SOURCE 202405L)
endif()

if(ECR_POSIX_SOURCE)
    add_compile_definitions(
        _POSIX_SOURCE=1
        _POSIX_C_SOURCE=${ECR_POSIX_SOURCE}
    )
endif()
