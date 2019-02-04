cmake_minimum_required(VERSION 2.8)
project( Sharpen )

# Set a compile command for YouCompleteMe for Vim
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

file( GLOB SOURCES "src/*.cpp" )

# Set the executable (and where it's sources lie)
add_executable( Sharpen ${SOURCES} )

# Import OpenCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

target_link_libraries( Sharpen ${OpenCV_LIBS} )
