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
    char journal_name[] = "journal.txt";
    char data_name[] = "data.txt";

    remove(journal_name);

    char txb[] = "txb43";
    char ib[] = "IB";
    char bb[] = "BB";
    char str[] = "checkpoint 1,2,3";
    char txe[] = "TXE150";
    write_to_journal(5, txb, 2, ib, 2, bb, 16, str, 6, txe);

    sleep(1);
    
    int err = checkpoint(6, txe);
    ASSERT_EQ(err, 0);

    sleep(1);

    char sol[] = "txb43IBBBcheckpoint 1,2,3TXE150";

    int fd = open(journal_name, O_RDONLY);
    int fd2 = open(data_name, O_RDONLY);

    struct stat st;
    stat(journal_name, &st);
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

