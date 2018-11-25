cmake_minimum_required(VERSION 3.0)

project(wormy)
add_subdirectory(win)

add_executable(
	wormy

	src/main.cpp
)

target_link_libraries(wormy PRIVATE win)
target_include_directories(wormy PRIVATE include win/include)
