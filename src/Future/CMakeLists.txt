SET(MAIN_HEADERS
  Future.hpp
  Promise.hpp
  Event.hpp
  SharedState.hpp
  StateMachine.hpp
)

SET(IMPL_HEADERS
  Impl/Future_inl.hpp
  Impl/Promise_inl.hpp
  Impl/SharedState_inl.hpp
)

ADD_LIBRARY(Future INTERFACE)

TARGET_SOURCES(Future INTERFACE
  ${MAIN_HEADERS}
  ${IMPL_HEADERS}
)

TARGET_INCLUDE_DIRECTORIES(Future INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}
)

IF (futex_like_POPULATED)
  TARGET_INCLUDE_DIRECTORIES(Future INTERFACE
    ${futex_like_SOURCE_DIR}/source
  )
ENDIF()

TARGET_LINK_LIBRARIES(Future INTERFACE
  third_party_futex_like
  Utils
)

GET_TARGET_PROPERTY(future_incs Future INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "Future include dirs: ${future_incs}")

GET_TARGET_PROPERTY(future_libs Future INTERFACE_LINK_LIBRARIES)
message(STATUS "Future link libs: ${future_libs}")
