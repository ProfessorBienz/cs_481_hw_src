// EXPECT_EQ and ASSERT_EQ are macros
// EXPECT_EQ test execution and continues even if there is a failure
// ASSERT_EQ test execution and aborts if there is a failure
// The ASSERT_* variants abort the program execution if an assertion fails 
// while EXPECT_* variants continue with the run.

#include "gtest/gtest.h"
#include "hw3_src/compute_pi.hpp"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(TLBTest, TestsIntests)
{
    double global_sum;
    global_sum = pthread_compute_pi(1, 1000, 0);    
    ASSERT_NEAR(global_sum, 3.14, 1);

    global_sum = pthread_compute_pi(2, 1000, 0);    
    ASSERT_NEAR(global_sum, 3.14, 1);

    global_sum = pthread_compute_pi(4, 1000, 0);    
    ASSERT_NEAR(global_sum, 3.14, 1);

    global_sum = pthread_compute_pi(8, 1000, 0);    
    ASSERT_NEAR(global_sum, 3.14, 1);



    global_sum = pthread_compute_pi(1, 100000, 0);    
    ASSERT_NEAR(global_sum, 3.14, 0.1);

    global_sum = pthread_compute_pi(2, 100000, 0);
    ASSERT_NEAR(global_sum, 3.14, 0.1);

    global_sum = pthread_compute_pi(4, 100000, 0);
    ASSERT_NEAR(global_sum, 3.14, 0.1);

    global_sum = pthread_compute_pi(8, 100000, 0);
    ASSERT_NEAR(global_sum, 3.14, 0.1);

    
    global_sum = pthread_compute_pi(1, 1000000, 0);    
    ASSERT_NEAR(global_sum, 3.14, 0.01);

    global_sum = pthread_compute_pi(2, 1000000, 0);    
    ASSERT_NEAR(global_sum, 3.14, 0.01);

    global_sum = pthread_compute_pi(4, 1000000, 0);    
    ASSERT_NEAR(global_sum, 3.14, 0.01);

    global_sum = pthread_compute_pi(8, 1000000, 0);    
    ASSERT_NEAR(global_sum, 3.14, 0.01);
}
