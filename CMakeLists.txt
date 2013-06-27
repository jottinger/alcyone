cmake_minimum_required (VERSION 2.7)

project (alcyone)

set (default_verbose_value false)
set (default_host_port 8090)
set (default_flare_time 600)
set (min_flare_time 100)
set (max_flare_time 2000)

configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "-Wall -O2 -pedantic")
endif(CMAKE_COMPILER_IS_GNUCXX)

add_executable(alcyone alcyone.cpp midi.cpp alcyoneServer.cpp mcp23008.cpp
flare.cpp serialdevice.cpp log.cpp debounce.cpp)

target_link_libraries(alcyone wiringPi boost_thread-mt boost_program_options)