include_directories(${hw_INCDIR})

### Lock Tests
add_executable(test_spin_lock test_spin_lock.cpp)
target_link_libraries(test_spin_lock ticket_spin gtest)
add_test(SpinLockTest ./test_spin_lock)

add_executable(test_yield_lock test_yield_lock.cpp)
target_link_libraries(test_yield_lock ticket_yield gtest)
add_test(YieldLockTest ./test_yield_lock)



### Semaphore Tests
add_executable(test_semaphore test_semaphore.cpp)
target_link_libraries(test_semaphore semaphore gtest)
add_test(SemaphoreTest ./test_semaphore)

add_executable(test_semaphore_lock test_semaphore_lock.cpp)
target_link_libraries(test_semaphore_lock semaphore gtest)
add_test(SemaphoreLockTest ./test_semaphore_lock)

### PI Tests
add_executable(test_pi test_pi.cpp)
target_link_libraries(test_pi mutex gtest)
add_test(PITest ./test_pi)

add_executable(test_pi_ticket_spin test_pi.cpp)
target_link_libraries(test_pi_ticket_spin ticket_spin gtest)
add_test(PITicketSpinTest ./test_pi_ticket_spin)

add_executable(test_pi_ticket_yield test_pi.cpp)
target_link_libraries(test_pi_ticket_yield ticket_yield gtest)
add_test(PITicketYieldTest ./test_pi_ticket_yield)

add_executable(test_pi_queue test_pi.cpp)
target_link_libraries(test_pi_queue queue gtest)
add_test(PIQueueTest ./test_pi_queue)

add_executable(test_pi_semaphore test_pi.cpp)
target_link_libraries(test_pi_semaphore semaphore gtest)
add_test(PISemaphoreTest ./test_pi_semaphore)



### Queue Tests
add_executable(test_queue test_queue.cpp)
target_link_libraries(test_queue queue gtest)
add_test(QueueTest ./test_queue)

add_executable(test_queue_lock test_queue_lock.cpp)
target_link_libraries(test_queue_lock queue gtest)
add_test(QueueLockTest ./test_queue_lock)
