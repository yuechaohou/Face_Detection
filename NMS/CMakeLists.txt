cmake_minimum_required(VERSION 2.8)
project( picture )
find_package( OpenCV REQUIRED )
add_executable( picture picture.cpp )
target_link_libraries( picture ${OpenCV_LIBS} )

