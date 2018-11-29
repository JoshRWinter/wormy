cmake_minimum_required(VERSION 3.0)

project(wormy)
add_subdirectory(win)

if(WIN32)
	if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W1" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
	endif()
endif()

add_custom_command(
	OUTPUT
		${CMAKE_CURRENT_LIST_DIR}/build/assets
	COMMAND
		cd ${CMAKE_CURRENT_LIST_DIR}/assets && roll ../build/assets
)

add_executable(
	wormy

	build/assets
	assets/rollfile
	assets/common.vert
	assets/common.frag

	src/main.cpp
	src/Renderer.cpp

	include/press.h
	include/Renderer.h
	include/wormy.h
)

target_link_libraries(wormy PRIVATE win)
target_include_directories(wormy PRIVATE include win/include)
