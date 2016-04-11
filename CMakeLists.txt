cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME splitspace-demo)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(${CMAKE_SOURCE_DIR}/splitspace/include)
link_directories(${CMAKE_BUILD_DIR}/splitspace ${CMAKE_SOURCE_DIR}/splitspace/lib)

add_subdirectory(${CMAKE_SOURCE_DIR}/splitspace)

add_executable(${PROJECT_NAME} src/main.cpp)

#TODO add flexible way of specifying library dependencies
target_link_libraries(${PROJECT_NAME} splitspace ${SPLITSPACE_LIBS})
