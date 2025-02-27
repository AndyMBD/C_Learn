cmake_minimum_required(VERSION 3.18)
set(GTEST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/gtest/include)  # 根据实际路径修改
# message(STATUS "GTEST_ROOT: ${GTEST_ROOT}")


# 启用测试功能（新增）
enable_testing()

# 包含主项目头文件
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../mc/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../dll/inc
)
# message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")

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
add_executable(project_tests 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main_test.cpp  # 需要改为.cpp扩展名
    ${TEST_SOURCES}
    ${TEST_HEADERS}
)

# 修改链接库配置（修复重复链接问题）
target_link_libraries(project_tests PRIVATE
                    ${CMAKE_CURRENT_SOURCE_DIR}/gtest/lib/libgmock_main.a
                    ${CMAKE_CURRENT_SOURCE_DIR}/gtest/lib/libgmock.a
                    ${CMAKE_CURRENT_SOURCE_DIR}/gtest/lib/libgtest_main.a
                    ${CMAKE_CURRENT_SOURCE_DIR}/gtest/lib/libgtest.a
)
target_include_directories(project_tests PRIVATE
    ${GTEST_ROOT}  # 确保该变量已正确定义
    ${GTEST_ROOT}/gtest  # 确保该变量已正确定义
    ${GTEST_ROOT}/gtest/internal  # 确保该变量已正确定义
    # ... 其他包含目录...
)

# 注册测试并添加属性（新增属性设置）
add_test(NAME AllUnitTests COMMAND project_tests)
# set_tests_properties(AllUnitTests PROPERTIES
#     FAIL_FAST TRUE
#     TIMEOUT 30
# )