cmake_minimum_required(VERSION 3.0.0)
project(traqbot_event VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/target) 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/target) 

add_executable(traqbot_event main.cpp)

set_property(TARGET traqbot_event PROPERTY CXX_STANDARD 20)

find_package(yaml-cpp CONFIG REQUIRED)
target_link_libraries(traqbot_event PRIVATE yaml-cpp)

find_package(mstch CONFIG REQUIRED)
target_link_libraries(traqbot_event PRIVATE mstch::mstch)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
