cmake_minimum_required(VERSION 3.18)
# 1.create a Project
set(PROJECT_NAME "C_002")
set(PROJECT_TEST_NAME "C_002_test")
PROJECT(${PROJECT_NAME})

find_package(GSL REQUIRED)
message(STATUS "GSL found: ${GSL_FOUND}")
message(STATUS "${GSL_INCLUDE_DIRS} found: ${${GSL_INCLUDE_DIRS}}")
find_package(GTest REQUIRED)
message(STATUS "GTEST_FOUND:        ${GTEST_FOUND}")
message(STATUS "GTEST_INCLUDE_DIRS: ${GTEST_INCLUDE_DIRS}")
message(STATUS "GTEST_LIBRARIES:    ${GTEST_LIBRARIES}")
# 2. add subdirectory and include directory
# add_subdirectory(dll)
# add_subdirectory(lib)

set(MAIN_DIR    ${CMAKE_CURRENT_SOURCE_DIR}/main)
set(DLL_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/dll)
set(LIB_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(MC_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/mc)

# set(GTEST_DIR   ${CMAKE_CURRENT_SOURCE_DIR}/test/gtest)
set(TEST_DIR   ${CMAKE_CURRENT_SOURCE_DIR}/test)

include_directories(${MAIN_DIR}/inc)
include_directories(${DLL_DIR}/inc)
include_directories(${LIB_DIR}/inc)
include_directories(${MC_DIR}/inc)

file(GLOB MAIN_INC  CONFIGURE_DEPENDS   ${MAIN_DIR}/inc/*.h)
file(GLOB DLL_INC   CONFIGURE_DEPENDS   ${DLL_DIR}/inc/*.h)
file(GLOB LIB_INC   CONFIGURE_DEPENDS   ${LIB_DIR}/inc/*.h)
file(GLOB MC_INC    CONFIGURE_DEPENDS   ${MC_DIR}/inc/*.h)

# file(GLOB GTEST_INC CONFIGURE_DEPENDS   ${GTEST_DIR}/include/*.h
#                                         ${GTEST_DIR}/include/gtest/*.h
#                                         ${GTEST_DIR}/include/gtest/internal/*.h)
# file(GLOB TEST_INC  CONFIGURE_DEPENDS   ${TEST_DIR}/inc/*.h)

# message(STATUS "GTEST_INC " ${GTEST_INC})

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
                            ${GSL_INCLUDE_DIRS}
)

# 4. add include directory
target_include_directories(${PROJECT_NAME} PUBLIC 
                                        ${MAIN_DIR}/inc
                                        ${DLL_DIR}/inc
                                        ${LIB_DIR}/inc
                                        ${MC_DIR}/inc
                                        )
target_include_directories(${PROJECT_NAME} PRIVATE ${GSL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GSL_LIBRARIES})
# target_link_libraries(${PROJECT_TEST_NAME} PRIVATE GSL::GSL)
# message(STATUS "PROJECT_SOURCE_DIR This is SOURCE dir " ${PROJECT_SOURCE_DIR})
# message(STATUS "CMAKE_CURRENT_SOURCE_DIR This is SOURCE dir " ${CMAKE_CURRENT_SOURCE_DIR})
#################################################################
# include(GoogleTest)
# # add_executable(FooTest ${TEST_SRC})
# add_executable(${PROJECT_TEST_NAME} ${TEST_SRC}
#                                     ${TEST_INC}
#                                     ${GTEST_INC}
#                                     ${DLL_SRC}    
#                                     ${DLL_INC}
#                                     ${LIB_SRC}
#                                     ${LIB_INC}
#                                     ${MC_SRC}
#                                     ${MC_INC}
# )
# gtest_add_tests(TARGET      ${PROJECT_TEST_NAME}
#                 TEST_SUFFIX .noArgs
#                 TEST_LIST   noArgsTests
# )
# gtest_add_tests(TARGET      ${PROJECT_TEST_NAME}
#                 EXTRA_ARGS  --someArg someValue
#                 TEST_SUFFIX .withArgs
#                 TEST_LIST   withArgsTests
# )
# set_tests_properties(${noArgsTests}   PROPERTIES TIMEOUT 10)
# set_tests_properties(${withArgsTests} PROPERTIES TIMEOUT 20)
#################################################################
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
)
target_link_libraries(${PROJECT_TEST_NAME} PRIVATE 
                                        # ${GTEST_LIBRARIES}
                                        # ${GTEST_MAIN_LIBRARIES}
                                        ${GTEST_BOTH_LIBRARIES})
target_include_directories(${PROJECT_TEST_NAME} PRIVATE ${GTEST_INCLUDE_DIRS})
message(STATUS GTEST_INCLUDE_DIRS " ${GTEST_INCLUDE_DIRS}")

target_link_libraries(${PROJECT_TEST_NAME} PRIVATE ${GTEST_LIBRARIES})

# 包含主项目头文件
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../mc/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../dll/inc
)
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")

# 自动收集测试源文件
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS 
						${CMAKE_CURRENT_SOURCE_DIR}/../mc/src/*.c
						${CMAKE_CURRENT_SOURCE_DIR}/../lib/src/*.c
						${CMAKE_CURRENT_SOURCE_DIR}/../dll/src/*.c)
file(GLOB TEST_HEADERS CONFIGURE_DEPENDS 
						${CMAKE_CURRENT_SOURCE_DIR}/gtest/include/gtest/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/gtest/include/gtest/internal/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/../mc/inc/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/../lib/inc/*.h
						${CMAKE_CURRENT_SOURCE_DIR}/../dll/inc/*.h)

# message(STATUS "TEST_SOURCES: ${TEST_SOURCES}")
# message(STATUS "TEST_HEADERS: ${TEST_HEADERS}")


# 修改测试目标配置

# 修改链接库配置（修复重复链接问题）



# 注册测试并添加属性（新增属性设置）
add_test(NAME AllUnitTests COMMAND ${PROJECT_TEST_NAME})
# set_tests_properties(AllUnitTests PROPERTIES
#     FAIL_FAST TRUE
#     TIMEOUT 30
# )