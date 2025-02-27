#include "gtest.h"

extern "C"
{
#include <windows.h>
#include "stdio.h"
#include "stdint.h"
#include "mc_Parameter.h"
#include "mc_control.h"
#include "my_dll.h"
#include "my_lib.h"
}

// 删除旧测试函数声明
// void test_case_1();
// void test_case_2();
// void test_suit();

// 使用GoogleTest测试框架替代原有测试
TEST(MyLibTest, BasicAdd)
{
    EXPECT_EQ(add(2, 3), 5);
}

TEST(MyLibTest, EdgeCaseAdd)
{
    EXPECT_EQ(add(UINT16_MAX, 1), UINT16_MAX ); // 示例溢出测试
}
main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}