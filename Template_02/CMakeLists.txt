cmake_minimum_required(VERSION 3.18)
# 1.create a Project
set(PROJECT_NAME "C_002")
PROJECT(${PROJECT_NAME})
# set(PROJECT_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)
# 2. add subdirectory and include directory
# add_subdirectory(dll)
# add_subdirectory(lib)

set(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/main)
set(DLL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dll)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(MC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/mc)

include_directories(${MAIN_DIR}/inc)
include_directories(${DLL_DIR}/inc)
include_directories(${LIB_DIR}/inc)
include_directories(${MC_DIR}/inc)

file(GLOB main_inc CONFIGURE_DEPENDS ${MAIN_DIR}/inc/*.h)
file(GLOB dll_inc CONFIGURE_DEPENDS  ${DLL_DIR}/inc/*.h)
file(GLOB lib_inc CONFIGURE_DEPENDS  ${LIB_DIR}/inc/*.h)
file(GLOB mc_inc CONFIGURE_DEPENDS   ${MC_DIR}/inc/*.h)


# 2. to get all source files
aux_source_directory(${MAIN_DIR}/src main_src)
aux_source_directory(${DLL_DIR}/src  dll_src)
aux_source_directory(${LIB_DIR}/src  lib_src)
aux_source_directory(${MC_DIR}/src   mc_src)

# 3. create a executable file

add_executable(${PROJECT_NAME} 
                            ${main_src}     # 可执行文件只需main入口
                            ${main_inc}
                            # 移除头文件引用（CMake自动处理头文件）
                            ${dll_src}    
                            ${dll_inc}
                            ${lib_src}
                            ${lib_inc}
                            ${mc_src}
                            ${mc_inc}
)
# 4. add include directory
target_include_directories(${PROJECT_NAME} PUBLIC 
                                        ${MAIN_DIR}/inc
                                        ${DLL_DIR}/inc
                                        ${LIB_DIR}/inc
                                        ${MC_DIR}/inc)

# message(STATUS "PROJECT_SOURCE_DIR This is SOURCE dir " ${PROJECT_SOURCE_DIR})
# message(STATUS "CMAKE_CURRENT_SOURCE_DIR This is SOURCE dir " ${CMAKE_CURRENT_SOURCE_DIR})
# 5. link library, include directory

# 添加测试配置（新增以下内容）
# enable_testing()
# include(CTest)

# # 定义测试目录
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
add_subdirectory(${TEST_DIR})