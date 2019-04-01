cmake_minimum_required(VERSION 2.8)

set( PROJECT_NAME "tracker" )
project( ${PROJECT_NAME} )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

# Set a compile command for YouCompleteMe for Vim
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

file( GLOB SOURCES "src/*.cpp" )
file( GLOB PHYS_SOURCES "src/physics/*.cpp" )

# Set the executable (and where it's sources lie)
add_executable( ${PROJECT_NAME} ${SOURCES} ${PHYS_SOURCES} )

# Import OpenCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} )
