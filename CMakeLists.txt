cmake_minimum_required (VERSION 2.7)
project (alcyone)

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "-Wall -O2 -pedantic")
endif(CMAKE_COMPILER_IS_GNUCXX)

add_executable(alcyone alcyone.cpp midi.cpp alcyoneServer.cpp mcp23008.cpp
flare.cpp serialdevice.cpp log.cpp debounce.cpp)

target_link_libraries(alcyone wiringPi boost_thread-mt boost_program_options)