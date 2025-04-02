cmake_minimum_required(VERSION 3.18)
# 1.create a Project
set(PROJECT_NAME "C_002")
set(PROJECT_TEST_NAME "C_002_test")
PROJECT(${PROJECT_NAME} C CXX)

find_package(GSL REQUIRED)
message(STATUS "GSL found: ${GSL_FOUND}")
message(STATUS "GSL_INCLUDE_DIRS: ${GSL_INCLUDE_DIRS}")
message(STATUS "GSL_LIBRARIES: ${GSL_LIBRARIES}")
find_package(GTest REQUIRED)
message(STATUS "GTEST_FOUND:        ${GTEST_FOUND}")
message(STATUS "GTEST_INCLUDE_DIRS: ${GTEST_INCLUDE_DIRS}")
message(STATUS "GTEST_LIBRARIES:    ${GTEST_BOTH_LIBRARIES}")
message(STATUS "CMAKE_C_COMPILER:    ${CMAKE_C_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER:    ${CMAKE_CXX_COMPILER}")
# find_package(PETSC REQUIRED)
# message(STATUS "$PETSC_DIR:    ${$PETSC_DIR}")
# 2. add subdirectory and include directory
# add_subdirectory(dll)
# add_subdirectory(lib)

set(MAIN_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/main)
set(GSL_MATH_DIR    ${CMAKE_CURRENT_SOURCE_DIR}/gslmath)
set(DLL_DIR         ${CMAKE_CURRENT_SOURCE_DIR}/dll)
set(LIB_DIR         ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(MC_DIR          ${CMAKE_CURRENT_SOURCE_DIR}/mc)
set(PTHREAD_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/pthread)
set(TIME_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/time)
set(GTEST_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/gtest)

# set(GTEST_DIR   ${CMAKE_CURRENT_SOURCE_DIR}/test/gtest)
set(TEST_DIR   ${CMAKE_CURRENT_SOURCE_DIR}/test)

include_directories(${MAIN_DIR}/inc)
include_directories(${GSL_MATH_DIR}/inc)
include_directories(${DLL_DIR}/inc)
include_directories(${LIB_DIR}/inc)
include_directories(${MC_DIR}/inc)
include_directories(${PTHREAD_DIR}/inc)
include_directories(${TIME_DIR}/inc)

file(GLOB MAIN_INC      CONFIGURE_DEPENDS   ${MAIN_DIR}/inc/*.h)
file(GLOB GSL_MATH_INC  CONFIGURE_DEPENDS   ${GSL_MATH_DIR}/inc/*.h)
file(GLOB DLL_INC       CONFIGURE_DEPENDS   ${DLL_DIR}/inc/*.h)
file(GLOB LIB_INC       CONFIGURE_DEPENDS   ${LIB_DIR}/inc/*.h)
file(GLOB MC_INC        CONFIGURE_DEPENDS   ${MC_DIR}/inc/*.h)
file(GLOB PTHREAD_INC   CONFIGURE_DEPENDS   ${PTHREAD_DIR}/inc/*.h)
file(GLOB TIME_INC      CONFIGURE_DEPENDS   ${TIME_DIR}/inc/*.h)
file(GLOB GTEST_INC     CONFIGURE_DEPENDS   ${GTEST_DIR}/inc/*.h)

# file(GLOB GTEST_INC CONFIGURE_DEPENDS   ${GTEST_DIR}/include/*.h
#                                         ${GTEST_DIR}/include/gtest/*.h
#                                         ${GTEST_DIR}/include/gtest/internal/*.h)
# file(GLOB TEST_INC  CONFIGURE_DEPENDS   ${TEST_DIR}/inc/*.h)

# message(STATUS "GTEST_INC " ${GTEST_INC})

# 2. to get all source files
aux_source_directory(${MAIN_DIR}/src        MAIN_SRC)
aux_source_directory(${GSL_MATH_DIR}/src    GSL_MATH_SRC)
aux_source_directory(${DLL_DIR}/src         DLL_SRC)
aux_source_directory(${LIB_DIR}/src         LIB_SRC)
aux_source_directory(${MC_DIR}/src          MC_SRC)
aux_source_directory(${PTHREAD_DIR}/src     PTHREAD_SRC)
aux_source_directory(${TIME_DIR}/src     TIME_SRC)

aux_source_directory(${GTEST_DIR}/src   GTEST_FUN_SRC)
aux_source_directory(${GTEST_DIR}/test   GTEST_TEST_SRC)


message(STATUS "MAIN_SRC is"        ${MAIN_SRC})
message(STATUS "GSL_MATH_SRC is"    ${GSL_MATH_SRC})
message(STATUS "DLL_SRC is"         ${DLL_SRC})
message(STATUS "LIB_SRC is"         ${LIB_SRC})
message(STATUS "MC_SRC is"          ${MC_SRC})
message(STATUS "PTHREAD_INC is"        ${PTHREAD_INC})
message(STATUS "PTHREAD_SRC is"        ${PTHREAD_SRC})
message(STATUS "TIME_INC is"        ${TIME_INC})
message(STATUS "TIME_SRC is"        ${TIME_SRC})
message(STATUS "TEST_SRC is"        ${GTEST_FUN_SRC})
message(STATUS "TEST_SRC is"        ${GTEST_TEST_SRC})

# 3. create a executable file

add_executable(${PROJECT_NAME} 
                            ${MAIN_SRC}     # 可执行文件只需main入口
                            ${MAIN_INC}
                            ${GSL_MATH_SRC}
                            ${GSL_MATH_INC}
                            ${DLL_SRC}    
                            ${DLL_INC}
                            ${LIB_SRC}
                            ${LIB_INC}
                            ${MC_SRC}
                            ${MC_INC}
                            ${PTHREAD_SRC}
                            ${PTHREAD_INC}
                            ${TIME_SRC}
                            ${TIME_INC}
                            ${GTEST_INC}
                            # ${GSL_INCLUDE_DIRS}
)

# 4. add include directory
target_include_directories(${PROJECT_NAME} PRIVATE 
                                        ${MAIN_DIR}/inc
                                        ${GSL_MATH_DIR}/inc
                                        ${DLL_DIR}/inc
                                        ${LIB_DIR}/inc
                                        ${MC_DIR}/inc
                                        ${PTHREAD_DIR}/inc
                                        ${TIME_DIR}/inc
                                        ${GSL_INCLUDE_DIRS}
                                        ${GTEST_DIR}/inc
                                        # ${GSL_INCLUDE_DIRS}/gsl
                                        )

target_link_libraries(${PROJECT_NAME} PRIVATE
                            # ${GSL_LIBRARIES}
                            ${GTEST_LIBRARIES}
                            ${GSL_LIBRARIES})

# message(STATUS "GSL_LIBRARIES " ${GSL_LIBRARIES})
# target_link_libraries(gsl_demo
#     gsl
#     gslcblas
#     ${catkin_LIBRARIES}
# )
# target_link_libraries(${PROJECT_TEST_NAME} PRIVATE GSL::GSL)
# message(STATUS "PROJECT_SOURCE_DIR This is SOURCE dir " ${PROJECT_SOURCE_DIR})
# message(STATUS "CMAKE_CURRENT_SOURCE_DIR This is SOURCE dir " ${CMAKE_CURRENT_SOURCE_DIR})
#################################################################
# 启用测试功能（新增）
# ------------------------------------------------------------------------------------
enable_testing()
include(GoogleTest)

add_executable(${PROJECT_TEST_NAME} 
                ${GTEST_FUN_SRC}
                ${GTEST_TEST_SRC}
                ${GTEST_INC}
                )

target_include_directories(${PROJECT_TEST_NAME} PRIVATE
                            ${GTEST_DIR}/inc
                            )
message(STATUS "GTEST_DIR is " ${GTEST_DIR})

target_link_libraries(${PROJECT_TEST_NAME} PRIVATE 
    GTest::GTest
    GTest::Main
    ${GSL_LIBRARIES}
    ${GTEST_BOTH_LIBRARIES}
)

gtest_discover_tests(${PROJECT_TEST_NAME})
# ------------------------------------------------------------------------------------


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

# ## 注册测试并添加属性（新增属性设置）
# # set_tests_properties(AllUnitTests PROPERTIES
# #     FAIL_FAST TRUE
# #     TIMEOUT 30
# # )
