// EXPECT_EQ and ASSERT_EQ are macros
// EXPECT_EQ test execution and continues even if there is a failure
// ASSERT_EQ test execution and aborts if there is a failure
// The ASSERT_* variants abort the program execution if an assertion fails 
// while EXPECT_* variants continue with the run.

#include "gtest/gtest.h"
#include "cs_481_hw_src/src.hpp"

FILE* fn;

void grandchild()
{
    fprintf(fn, "Grandchild\n");
}

void child()
{
    fprintf(fn, "Child\n");
}

void parent()
{
    fprintf(fn, "Parent\n");
}

TEST(ProcessOrderTest, TestsInTests)
{
    for (int i = 0; i < 100; i++)
    {
        fn = fopen("./procs.output", "w");
        run_processes();

        const char* comparisons[3] = {"Grandchild", "Child", "Parent"};

        fclose(fn);
        fn = fopen("./procs.output", "r");

        char buff[255];
        for (int i = 0; i < 3; i++)
        {
            fscanf(fn, "%s\n", buff);
             ASSERT_STREQ(buff, comparisons[i]);
        }

        fclose(fn);
    }
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    int ierr = 0;
    ierr += RUN_ALL_TESTS();

    return ierr;

}



