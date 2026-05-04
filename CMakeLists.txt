cmake_minimum_required(VERSION 3.24)
project(VulkanGPGPU_CXX23 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_compile_options(-fno-exceptions -fno-rtti)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if(CLANG_TIDY_EXE)
    message(STATUS "Clang-Tidy found: ${CLANG_TIDY_EXE}")
    set(CMAKE_CXX_CLANG_TIDY 
        "${CLANG_TIDY_EXE};-config-file=${CMAKE_SOURCE_DIR}/.clang-tidy"
    )
else()
    message(AUTHOR_WARNING "Clang-Tidy not found. Style enforcement is disabled.")
endif()

find_package(Vulkan REQUIRED)
add_subdirectory(src)