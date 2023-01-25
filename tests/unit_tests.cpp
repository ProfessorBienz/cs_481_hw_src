// EXPECT_EQ and ASSERT_EQ are macros
// EXPECT_EQ test execution and continues even if there is a failure
// ASSERT_EQ test execution and aborts if there is a failure
// The ASSERT_* variants abort the program execution if an assertion fails 
// while EXPECT_* variants continue with the run.

#include "gtest/gtest.h"
#include "cs_481_hw_src/src.hpp"

FILE* fn;

// Declare Functions for autograder test0
void scheduler_test0()
{
    void job0(int time)
    {
        for (int t = 0; t < time; t++)
            counter += 3;
    }

    void job1(int time)
    {
        for (int t = 0; t < time; t++)
            counter *= 2;
    }

    void job2(int time)
    {
        for (int t = 0; t < time; t++)
            counter = 1;
    }

    void create_jobs(int* n_jobs, Job** jobs)
    {
        *n_jobs = 3;

        Job* example_jobs = (Job*)malloc((*n_jobs)*sizeof(Job));
        example_jobs[0].priority = 1;
        example_jobs[0].idx = 0;
        example_jobs[0].time = 2;
        example_jobs[0].run_job = job0;

        example_jobs[1].priority = 1;
        example_jobs[1].idx = 1;
        example_jobs[1].time = 1;
        example_jobs[1].run_job = job1;

        example_jobs[2].priority = 0;
        example_jobs[2].idx = 2;
        example_jobs[2].time = 3;
        example_jobs[2].run_job = job2;

        *jobs = example_jobs;
    }
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}

TEST(PriorityTest, TestsIntests)
{
    int n_jobs;
    Job* jobs;

    // Declare Functions
    scheduler_test0();

    // Run Test
    create_jobs(&n_jobs, &jobs);
    counter = 0;
    priority(n_jobs, jobs);
    ASSERT_EQ(counter, 14);
    free(jobs);
}

TEST(PriorityRRTest, TestInTests)
{
    int n_jobs;
    Job* jobs;
    int time_slice = 1;

    // Declare Functions
    scheduler_test0();

    // Run Test
    create_jobs(&n_jobs, &jobs);
    counter = 0;
    priority_rr(n_jobs, jobs, time_slice);
    ASSERT_EQ(counter, 11);
    free(jobs);

}

TEST(ProcessOrderTest, TestsInTests)
{
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

    fn = fopen("./procs.output", "w");
    create_processes();

    const char* gc = "Grandchild";
    const char* c = "Child";
    const char* p = "Parent";

    fclose(fn);
    fn = fopen("./procs.output", "r");

    char buff[255];
    fscanf(fn, "%s\n", buff);
    for (int i = 0; i < 10; i++)
        if (buff[i] != gc[i])
            printf("i %d, buff %c, gc %c\n", i, buff[i], gc[i]);
    ASSERT_STREQ(buff, gc);

    fscanf(fn, "%s\n", buff);
    for (int i = 0; i < 5; i++)
        if (buff[i] != c[i])
            printf("i %d, buff %c, c %c\n", i, buff[i], c[i]);
    ASSERT_STREQ(buff, gc);

    fscanf(fn, "%s\n", buff);
    for (int i = 0; i < 6; i++)
        if (buff[i] != p[i])
            printf("i %d, buff %c, p %c\n", i, buff[i], p[i]);
    ASSERT_STREQ(buff, gc);

    fclose(fn);
}
