include_directories(${hw_INCDIR})

add_executable(unit_tests unit_tests.cpp)
target_link_libraries(unit_tests homework googletest)
add_test(UnitTests ./unit_tests)
