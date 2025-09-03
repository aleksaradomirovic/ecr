# Copyright (C) 2025 Aleksa Radomirovic
# SPDX-License-Identifier: Apache-2.0

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 23)

enable_language(C)

block()
    set(SUPPORTED_COMPILERS "Clang")
    if(NOT CMAKE_C_COMPILER_ID IN_LIST SUPPORTED_COMPILERS)
        message(WARNING "The current C compiler (${CMAKE_C_COMPILER_ID}) is not "
                "supported by this project. This build is unofficial.\n"
                "Supported C compilers: ${SUPPORTED_COMPILERS}")
    endif()
endblock()

if(BUILD_FREESTANDING)
    add_compile_options(
        $<$<COMPILE_LANGUAGES:C,CXX>:-ffreestanding>
    )
    add_link_options(
        $<$<COMPILE_LANGUAGES:C,CXX>:-nostdlib>
    )
endif()

option(ECR_USE_POSIX "Use POSIX source" ON)
option(ECR_USE_GNU_SOURCE "Use GNU source" ON)

if(ECR_USE_POSIX)
    add_compile_definitions(
        _POSIX_SOURCE=1
        _POSIX_C_SOURCE=202405L
        ECR_USE_POSIX=1
    )
endif()
if(ECR_USE_GNU_SOURCE)
    add_compile_definitions(
        _GNU_SOURCE=1
        ECR_USE_GNU_SOURCE=1
    )
endif()
