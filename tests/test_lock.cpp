// EXPECT_EQ and ASSERT_EQ are macros
// EXPECT_EQ test execution and continues even if there is a failure
// ASSERT_EQ test execution and aborts if there is a failure
// The ASSERT_* variants abort the program execution if an assertion fails 
// while EXPECT_* variants continue with the run.

#include "gtest/gtest.h"
#include "hw3_src/lock.hpp"

int n;
lock_t my_lock;
int global_sum;
void* thread_add(void* arg)
{
    for (int i = 0; i < n; i++)
    {
        lock(&my_lock);
        global_sum++;
        unlock(&my_lock);
    }
    printf("Ticket %d, Turn %d, Global Sum %d\n", my_lock.ticket, my_lock.turn, global_sum);

    return NULL;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(TLBTest, TestsIntests)
{
    init(&my_lock);
    n = 1000;
    global_sum = 0;
    int num_threads = 2;
    pthread_t* threads = (pthread_t*)malloc(num_threads*sizeof(pthread_t));

    for (int i = 0; i < num_threads; i++)
        pthread_create((&threads[i]), NULL, thread_add, NULL);
    for (int i = 0; i < num_threads; i++)
        pthread_join(threads[i], NULL);

    ASSERT_EQ(global_sum, n*num_threads);

    free(threads);
    destroy(&my_lock);
}
