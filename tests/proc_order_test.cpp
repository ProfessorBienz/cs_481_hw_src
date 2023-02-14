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
    int rc = fork();
    int pid = getpid();

    if (rc == 0)
    {
        fn = fopen("./procs.output", "w");
        run_processes();

        if (pid == getpid())
            fclose(fn);
        exit(1);
    }
    else
    {
        wait(NULL);

        const char* comparisons[3] = {"Grandchild", "Child", "Parent"};

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



