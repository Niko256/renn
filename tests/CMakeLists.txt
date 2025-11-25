CMAKE_MINIMUM_REQUIRED(VERSION 3.30)
PROJECT(Tests LANGUAGES CXX)

SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

INCLUDE(GoogleTest)


SET(HASH_SOURCES
    ${smhasher_SOURCE_DIR}/src/City.cpp
    ${smhasher_SOURCE_DIR}/src/MurmurHash3.cpp
)


ADD_EXECUTABLE(SpinlockTests SpinlockTests.cc)
TARGET_LINK_LIBRARIES(SpinlockTests PRIVATE
  Spinlock
  gtest_main
)
gtest_discover_tests(SpinlockTests)


ADD_EXECUTABLE(ThreadPoolTests ThreadPoolTests.cc)
TARGET_LINK_LIBRARIES(ThreadPoolTests PRIVATE
  ThreadPool
  gtest_main
  Scheduling
)
gtest_discover_tests(ThreadPoolTests)


ADD_EXECUTABLE(FiberTests FiberTests.cc)
TARGET_LINK_LIBRARIES(FiberTests PRIVATE
  Fiber
  ThreadPool
  Coroutine
  third_party_sure
  gtest_main
  third_party_futex_like
  # fmt::fmt
)
gtest_discover_tests(FiberTests)
