cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME splitspace-demo)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} src/main.cpp)

include_directories(splitspace/include)

target_link_libraries(${PROJECT_NAME} splitspace-build/splitspace)
