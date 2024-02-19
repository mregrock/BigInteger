
file(GLOB_RECURSE TEST_SOURCES "*.cpp")

find_package(GoogleTest)
if (GoogleTest_FOUND)
    add_subdirectory(extern/googletest)
    include(GoogleTest)
    add_executable(tests ${TEST_SOURCES})
    target_link_libraries(tests gtest gtest_main ${PROJECT_NAME})
    include_directories(include)
    enable_testing()
    gtest_discover_tests(tests)
endif()