include_directories(${hw5_INCDIR})

add_executable(test_journal test_journal.cpp)
target_link_libraries(test_journal hw5 gtest )
add_test(TestJournal ./test_journal)

add_executable(test_checkpoint test_checkpoint.cpp)
target_link_libraries(test_checkpoint hw5 gtest )
add_test(TestCheckpoint ./test_checkpoint)

add_executable(test_checkpoint2 test_checkpoint2.cpp)
target_link_libraries(test_checkpoint2 hw5 gtest )
add_test(TestCheckpoint2 ./test_checkpoint2)

add_executable(test_fail_checkpoint test_fail_checkpoint.cpp)
target_link_libraries(test_fail_checkpoint hw5 gtest )
add_test(TestFailCheckpoint ./test_fail_checkpoint)

