cmake_minimum_required(VERSION 3.11)
project(bomberman)

include_directories(BEFORE include)
set(CMAKE_MODULE_PATH include)
include(include/FindIrrlicht.cmake)

set(SFML_DIR "./include/lib/cmake/SFML")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-std=c++17)
if (NOT ${Irrlicht_FOUND})
	message (send_error "Could not find Irrlicht")
else()
	message ("Irrlicht Found")
endif()

file (GLOB_RECURSE source srcs/*.cpp)
file (GLOB_RECURSE header include/*.hpp)
add_executable(bomberman ${source} ${header})

install(TARGETS bomberman DESTINATION .)

if (UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lIrrlicht -lsfml-system -lsfml-audio -lstdc++fs")
else()
	#set(SFML_STATIC_LIBRARIES TRUE)
	find_package(SFML 2 COMPONENTS audio system REQUIRED)
	include_directories(bomberman ${Irrlicht_INCLUDE_DIRS})
	target_link_libraries(bomberman ${Irrlicht_LIBRARIES} sfml-system sfml-audio)
endif()


