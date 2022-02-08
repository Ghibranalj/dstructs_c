cmake_minimum_required(VERSION 3.20)

project (dstructs_c VERSION 1.0.0)


FILE(GLOB c ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
FILE(GLOB h ${CMAKE_CURRENT_SOURCE_DIR}/*.h)


add_library(${CMAKE_PROJECT_NAME} STATIC ${c} ${h})

target_include_directories( ${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "Adding module ${CMAKE_PROJECT_NAME}")


add_executable("${CMAKE_PROJECT_NAME}_example" example/main.c)
target_link_libraries("${CMAKE_PROJECT_NAME}_example" PUBLIC ${CMAKE_PROJECT_NAME})
