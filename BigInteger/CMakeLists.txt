file(GLOB_RECURSE SOURCES "*.cpp")
add_library(BigInteger SHARED ${SOURCES})
target_include_directories(BigInteger PUBLIC include)