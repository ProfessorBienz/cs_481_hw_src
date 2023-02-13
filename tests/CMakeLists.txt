include_directories(${hw_INCDIR})

add_executable(proc_run_test proc_run_test.cpp)
target_link_libraries(proc_run_test homework gtest)
add_test(ProcRunTests ./proc_run_test)

add_executable(proc_order_test proc_order_test.cpp)
target_link_libraries(proc_order_test homework gtest)
add_test(ProcOrderTests ./proc_order_test)

add_executable(proc_exit_test proc_exit_test.cpp)
target_link_libraries(proc_exit_test homework gtest)
add_test(ProcExitTests ./proc_exit_test)

add_executable(pri_run_test pri_run_test.cpp)
target_link_libraries(pri_run_test homework gtest)
add_test(PriRunTests ./pri_run_test)

add_executable(pri_rr_run_test pri_rr_run_test.cpp)
target_link_libraries(pri_rr_run_test homework gtest)
add_test(PriRRRunTests ./pri_rr_run_test)


add_executable(pri_order_test pri_order_test.cpp)
target_link_libraries(pri_order_test homework gtest)
add_test(PriOrderTests ./pri_order_test)

add_executable(pri_rr_order_test pri_rr_order_test.cpp)
target_link_libraries(pri_rr_order_test homework gtest)
add_test(PriRROrderTests ./pri_rr_order_test)

add_executable(pri_high_test pri_high_test.cpp)
target_link_libraries(pri_high_test homework gtest)
add_test(PriHighTests ./pri_high_test)

add_executable(pri_rr_high_test pri_rr_high_test.cpp)
target_link_libraries(pri_rr_high_test homework gtest)
add_test(PriHighRRTests ./pri_rr_high_test)


add_executable(pri_timer pri_timer.cpp)
target_link_libraries(pri_timer homework)
