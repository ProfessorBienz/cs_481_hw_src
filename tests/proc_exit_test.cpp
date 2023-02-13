// EXPECT_EQ and ASSERT_EQ are macros
// EXPECT_EQ test execution and continues even if there is a failure
// ASSERT_EQ test execution and aborts if there is a failure
// The ASSERT_* variants abort the program execution if an assertion fails 
// while EXPECT_* variants continue with the run.

#include "gtest/gtest.h"
#include "cs_481_hw_src/src.hpp"


void grandchild()
{
}

void child()
{
}

void parent()
{
}

TEST(ProcessOrderTest, TestsInTests)
{
    int pid = getpid();
    run_processes();

    ASSERT_EQ(getpid(), pid);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    int ierr = 0;
    for (int i = 0; i < 100; i++)
        ierr += RUN_ALL_TESTS();

    return ierr;

}



