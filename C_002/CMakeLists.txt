cmake_minimum_required(VERSION 3.18)
# 1.create a Project
set(PROJECT_NAME "C_002")
set(PROJECT_TEST_NAME "C_002_test")
PROJECT(${PROJECT_NAME})

# 2. add subdirectory and include directory
# add_subdirectory(dll)
# add_subdirectory(lib)

set(MAIN_DIR    ${CMAKE_CURRENT_SOURCE_DIR}/main)
set(DLL_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/dll)
set(LIB_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(MC_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/mc)

set(GTEST_DIR   ${CMAKE_CURRENT_SOURCE_DIR}/test/gtest)
set(TEST_DIR   ${CMAKE_CURRENT_SOURCE_DIR}/test)

include_directories(${MAIN_DIR}/inc)
include_directories(${DLL_DIR}/inc)
include_directories(${LIB_DIR}/inc)
include_directories(${MC_DIR}/inc)

file(GLOB MAIN_INC  CONFIGURE_DEPENDS   ${MAIN_DIR}/inc/*.h)
file(GLOB DLL_INC   CONFIGURE_DEPENDS   ${DLL_DIR}/inc/*.h)
file(GLOB LIB_INC   CONFIGURE_DEPENDS   ${LIB_DIR}/inc/*.h)
file(GLOB MC_INC    CONFIGURE_DEPENDS   ${MC_DIR}/inc/*.h)

file(GLOB GTEST_INC CONFIGURE_DEPENDS   ${GTEST_DIR}/include/*.h
                                        ${GTEST_DIR}/include/gtest/*.h
                                        ${GTEST_DIR}/include/gtest/internal/*.h)
file(GLOB TEST_INC  CONFIGURE_DEPENDS   ${TEST_DIR}/inc/*.h)

message(STATUS "GTEST_INC " ${GTEST_INC})

# 2. to get all source files
aux_source_directory(${MAIN_DIR}/src MAIN_SRC)
aux_source_directory(${DLL_DIR}/src  DLL_SRC)
aux_source_directory(${LIB_DIR}/src  LIB_SRC)
aux_source_directory(${MC_DIR}/src  MC_SRC)

aux_source_directory(${TEST_DIR}/src   TEST_SRC)


message(STATUS "MAIN_SRC is" ${MAIN_SRC})
message(STATUS "DLL_SRC is" ${DLL_SRC})
message(STATUS "LIB_SRC is" ${LIB_SRC})
message(STATUS "MC_SRC is" ${MC_SRC})
message(STATUS "TEST_SRC is" ${TEST_SRC})

# 3. create a executable file

add_executable(${PROJECT_NAME} 
                            ${MAIN_SRC}     # 可执行文件只需main入口
                            ${DLL_SRC}    
                            ${LIB_SRC}
                            ${MC_SRC}
                            ${MAIN_INC}
                            ${DLL_INC}
                            ${LIB_INC}
                            ${MC_INC}
)

# 4. add include directory
target_include_directories(${PROJECT_NAME} PUBLIC 
                                        ${MAIN_DIR}/inc
                                        ${DLL_DIR}/inc
                                        ${LIB_DIR}/inc
                                        ${MC_DIR}/inc)

# message(STATUS "PROJECT_SOURCE_DIR This is SOURCE dir " ${PROJECT_SOURCE_DIR})
# message(STATUS "CMAKE_CURRENT_SOURCE_DIR This is SOURCE dir " ${CMAKE_CURRENT_SOURCE_DIR})

# 启用测试功能（新增）
enable_testing()
add_executable(${PROJECT_TEST_NAME} 
                ${TEST_SRC}
                ${TEST_INC}
                ${GTEST_INC}
                ${DLL_SRC}    
                ${DLL_INC}
                ${LIB_SRC}
                ${LIB_INC}
                ${MC_SRC}
                ${MC_INC}
)
target_include_directories(${PROJECT_TEST_NAME}  PRIVATE
                    ${DLL_DIR}/inc
                    ${LIB_DIR}/inc
                    ${MC_DIR}/inc
                    ${TEST_DIR}/inc
                    ${GTEST_DIR}
                    ${GTEST_DIR}/include  # 确保该变量已正确定义
                    ${GTEST_DIR}/include/gtest  # 确保该变量已正确定义
                    ${GTEST_DIR}/include/gtest/internal  # 确保该变量已正确定义
)
target_link_libraries(${PROJECT_TEST_NAME} PRIVATE
                    ${GTEST_DIR}/lib/libgmock_main.a
                    ${GTEST_DIR}/lib/libgmock.a
                    ${GTEST_DIR}/lib/libgtest_main.a
                    ${GTEST_DIR}/lib/libgtest.a
)
# 包含主项目头文件
# include_directories(
#     ${CMAKE_CURRENT_SOURCE_DIR}/../mc/inc
#     ${CMAKE_CURRENT_SOURCE_DIR}/../lib/inc
#     ${CMAKE_CURRENT_SOURCE_DIR}/../dll/inc
# )
# message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")

# # 自动收集测试源文件
# file(GLOB TEST_SOURCES CONFIGURE_DEPENDS 
# 						${CMAKE_CURRENT_SOURCE_DIR}/../mc/src/*.c
# 						${CMAKE_CURRENT_SOURCE_DIR}/../lib/src/*.c
# 						${CMAKE_CURRENT_SOURCE_DIR}/../dll/src/*.c)
# file(GLOB TEST_HEADERS CONFIGURE_DEPENDS 
# 						${CMAKE_CURRENT_SOURCE_DIR}/gtest/include/gtest/*.h
# 						${CMAKE_CURRENT_SOURCE_DIR}/gtest/include/gtest/internal/*.h
# 						${CMAKE_CURRENT_SOURCE_DIR}/../mc/inc/*.h
# 						${CMAKE_CURRENT_SOURCE_DIR}/../lib/inc/*.h
# 						${CMAKE_CURRENT_SOURCE_DIR}/../dll/inc/*.h)

# # message(STATUS "TEST_SOURCES: ${TEST_SOURCES}")
# # message(STATUS "TEST_HEADERS: ${TEST_HEADERS}")


# # 修改测试目标配置

# # 修改链接库配置（修复重复链接问题）



# # 注册测试并添加属性（新增属性设置）
add_test(NAME AllUnitTests COMMAND project_tests)
# # set_tests_properties(AllUnitTests PROPERTIES
# #     FAIL_FAST TRUE
# #     TIMEOUT 30
# # )