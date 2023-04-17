// EXPECT_EQ and ASSERT_EQ are macros
// EXPECT_EQ test execution and continues even if there is a failure
// ASSERT_EQ test execution and aborts if there is a failure
// The ASSERT_* variants abort the program execution if an assertion fails 
// while EXPECT_* variants continue with the run.

#include "gtest/gtest.h"
#include "cs_481_hw_src/src.hpp"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}

TEST(TLBTest, TestsIntests)
{
    write_to_journal(5, "txe12", 2, "ib", 2, "bb", 11, "hello world", 5, "txe21");

    int fd = open("journal.txt", O_RDONLY);
    char* sol = "txe12ibbbhello worldtxe21";

    struct stat st;
    stat("journal.txt", &st);
    int size = st.st_size;
    char* file_bytes = (char*)malloc(size*sizeof(char));
    read(fd, file_bytes, size);

    ASSERT_STREQ(file_bytes, sol);
    

