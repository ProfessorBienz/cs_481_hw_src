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
    write_to_journal(5, "txb43", 2, "IB", 2, "BB", 16, "checkpoint 1,2,3", 6, "TXE150");

    sleep(1);
    
    int err = checkpoint(6, "TXE150");
    ASSERT_EQ(err, 0);

    sleep(1);

    char* sol = "txb43IBBBcheckpoing 1,2,3TXE150";

    int fd = open("journal.txt", O_RDONLY);
    int fd2 = open("data.txt", O_RDONLY);

    struct stat st;
    stat("journal.txt", &st);
    int size = st.st_size;
    ASSERT_GT(size, 0);

    char* journal_bytes = (char*)malloc(size);
    char* data_bytes = (char*)malloc(size);
    read(fd, journal_bytes, size);
    read(fd2, data_bytes, size);
    ASSERT_STREQ(journal_bytes, data_bytes);
    ASSERT_STREQ(sol, journal_bytes);

    free(journal_bytes);
    free(data_bytes);
    close(fd);
    close(fd2);
}

