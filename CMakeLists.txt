# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project ("ApexServer")

# 包含子项目。
if (MSVC)
    add_compile_options(/utf-8)
endif()

add_subdirectory ("DMAlib")
add_subdirectory ("spdlog")
add_subdirectory ("ApexServer")
