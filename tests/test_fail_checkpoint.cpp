// EXPECT_EQ and ASSERT_EQ are macros
// EXPECT_EQ test execution and continues even if there is a failure
// ASSERT_EQ test execution and aborts if there is a failure
// The ASSERT_* variants abort the program execution if an assertion fails 
// while EXPECT_* variants continue with the run.

#include "gtest/gtest.h"
#include "hw5_src/file_system.hpp"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}

TEST(TLBTest, TestsIntests)
{
    remove("journal.txt");
    write_to_journal(5, "txe12", 2, "ib", 2, "bb", 11, "hello world", 0, "");

    sleep(1);

    int err = checkpoint(5, "txe21");
    ASSERT_EQ(err, -1);
}
