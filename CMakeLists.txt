# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project information
project(raylib-grid LANGUAGES CXX)

# Set C++ standard to C++17 (or other version if desired)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
	include(FetchContent)
	FetchContent_Declare(
		raylib
		DOWNLOAD_EXTRACT_TIMESTAMP OFF
		URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
		)
	FetchContent_GetProperties(raylib)
	if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
		set(FETCHCONTENT_QUIET NO)
		FetchContent_Populate(raylib)
		set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
		add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
	endif()
endif()

# Define source files
set(SOURCES
	src/main.cc
	src/world.cc
	src/pathfinder.cc
)

# Add the executable
add_executable(raylib-grid ${SOURCES})

# Include directories
target_include_directories(raylib-grid PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/lib/raygui-cpp/icons
	)

# Optionally, set some warning flags (these can be adjusted as needed)
target_compile_options(raylib-grid PRIVATE
	-Wall
	-Wextra
	-Wpedantic
	)

#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# This doesn't work :( why?
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/raygui/projects/CMake)
# target_link_libraries(${PROJECT_NAME} raygui)


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/raygui-cpp)
target_link_libraries(${PROJECT_NAME} raygui_cpp)
# target_link_libraries(${PROJECT_NAME} raygui_icons)

# Add debugging flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set (symlink_src "${CMAKE_SOURCE_DIR}/assets")
set (symlink_dest "${CMAKE_CURRENT_BINARY_DIR}/assets")
add_custom_command(
	TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E create_symlink ${symlink_src} ${symlink_dest}
	DEPENDS ${symlink_dest}
	COMMENT "Created a symbolic link to the assets folder"
	)


