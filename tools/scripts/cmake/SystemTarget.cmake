# Copyright (C) 2025 Aleksa Radomirovic
# SPDX-License-Identifier: Apache-2.0

if((CMAKE_SYSTEM_NAME STREQUAL CMAKE_HOST_SYSTEM_NAME) AND (CMAKE_SYSTEM_PROCESSOR STREQUAL CMAKE_HOST_SYSTEM_PROCESSOR))
    set(CMAKE_CROSSCOMPILING FALSE)
else()
    set(CMAKE_CROSSCOMPILING TRUE)
endif()

set(ECR_SUPPORTED_SYSTEMS Linux)

if(NOT CMAKE_SYSTEM_NAME IN_LIST ECR_SUPPORTED_SYSTEMS)
    message(WARNING "Unsupported system/environment '${CMAKE_SYSTEM_NAME}' - this build is not officially supported")
endif()
