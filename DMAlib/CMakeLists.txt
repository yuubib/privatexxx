cmake_minimum_required(VERSION 3.0)


set(TARGET_NAME DMAlib)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADER "*.h")


add_library(DMAlib STATIC ${SOURCES} ${HEADER})
target_include_directories(DMAlib PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/libs 
${CMAKE_CURRENT_SOURCE_DIR}/nt 
${CMAKE_CURRENT_SOURCE_DIR}/Memory
)
target_link_libraries(DMAlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/leechcore.lib
									${CMAKE_CURRENT_SOURCE_DIR}/libs/vmm.lib)
# �����Ҫ��Ӱ���Ŀ¼������ȡ�������ע�Ͳ��޸�·��
# target_include_directories(MyStaticLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

