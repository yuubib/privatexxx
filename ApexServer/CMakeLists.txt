# CMakeList.txt: ApexServer 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)
file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")
file(GLOB_RECURSE HEADERS "*.h")
# 将源代码添加到此项目的可执行文件。
add_executable (ApexServer ${SOURCES} ${HEADERS})
target_link_libraries(ApexServer PUBLIC DMAlib)
target_link_libraries(ApexServer PUBLIC spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ApexServer PROPERTY CXX_STANDARD 20)
endif()

if (WIN32)
    add_custom_command(TARGET ApexServer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/DMALib/leechcore.dll"
            $<TARGET_FILE_DIR:ApexServer>)
    add_custom_command(TARGET ApexServer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/DMALib/FTD3XX.dll"
            $<TARGET_FILE_DIR:ApexServer>)
    add_custom_command(TARGET ApexServer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/DMALib/vmm.dll"
            $<TARGET_FILE_DIR:ApexServer>)
    add_custom_command(TARGET ApexServer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/DMALib/symsrv.dll"
            $<TARGET_FILE_DIR:ApexServer>)
    add_custom_command(TARGET ApexServer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/DMALib/dbghelp.dll"
            $<TARGET_FILE_DIR:ApexServer>)

endif()
