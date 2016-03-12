#Specipecify the version being used aswell as the language
cmake_minimum_required(VERSION 2.9)
#Name your project here
project(raaga)
#Sends the -std=c++11 flag to the gcc compiler
add_definitions(-std=c++11)

INCLUDE(FindPkgConfig)

pkg_check_modules(GST REQUIRED gstreamer-1.0)
include_directories(${GST_INCLUDE_DIRS})
link_directories(${GST_LIBRARY_DIRS})

add_executable( raaga main.cpp  
Raaga.cpp Raaga.h
Config.cpp Config.h
GstPlayer.cpp GstPlayer.h
DefaultIO.cpp DefaultIO.h
IMediaPlayer.h IInOut.h
)

target_link_libraries(raaga ${GST_LIBRARIES})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
  target_compile_options(PUBLIC raaga "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
  target_link_libraries(raaga "${CMAKE_THREAD_LIBS_INIT}")
endif()

find_package( Boost REQUIRED COMPONENTS program_options )
include_directories( ${Boost_INCLUDE_DIRS} )
target_link_libraries( raaga ${Boost_LIBRARIES} )

