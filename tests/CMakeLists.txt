add_subdirectory(extern/googletest)

include(GoogleTest)

file(GLOB_RECURSE TEST_SOURCES "*.cpp")

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests gtest gtest_main ${PROJECT_NAME})

enable_testing()
gtest_discover_tests(tests)