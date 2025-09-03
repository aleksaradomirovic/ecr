# Copyright (C) 2025 Aleksa Radomirovic
# SPDX-License-Identifier: Apache-2.0

# supported systems

block()
    set(SUPPORTED_SYSTEMS "Linux")
    if(NOT CMAKE_SYSTEM_NAME IN_LIST SUPPORTED_SYSTEMS)
        message(WARNING "The current target system (${CMAKE_SYSTEM_NAME}) is not "
                "supported by this project. This build is unofficial.\n"
                "Supported systems: ${SUPPORTED_SYSTEMS}")
    endif()
endblock()

# freestanding builds

block(PROPAGATE BUILD_FREESTANDING)
    set(INHERENTLY_FREESTANDING_SYSTEMS "Generic" "Generic-ELF" "Generic-ADSP")

    if(CMAKE_SYSTEM_NAME IN_LIST INHERENTLY_FREESTANDING_SYSTEMS)
        set(BUILD_FREESTANDING ON)
    endif()
endblock()

option(BUILD_FREESTANDING "Build for a freestanding system" OFF)
