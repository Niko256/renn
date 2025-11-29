ADD_SUBDIRECTORY(ThreadPool)
# ADD_SUBDIRECTORY(Sandbox)
# ADD_SUBDIRECTORY(WorkStealing)
# ADD_SUBDIRECTORY(Strand)

ADD_LIBRARY(Runtime STATIC
  Core/Runtime.cc
)

TARGET_SOURCES(Runtime PUBLIC
  Core/Runtime.hpp
  Core/IExecutor.hpp
  Core/RtView.hpp
  Core/Submit.hpp
)

TARGET_INCLUDE_DIRECTORIES(Runtime PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Core>
)

TARGET_LINK_LIBRARIES(Runtime PUBLIC
  third_party_function2
  Utils
  ThreadPool
  Timers
)
