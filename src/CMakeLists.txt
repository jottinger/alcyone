#for config.h

include_directories(${alcyone_SOURCE_DIR})

add_executable(alcyone alcyone.cpp midi.cpp webservice.cpp mcp23008.cpp
	flare.cpp serialdevice.cpp log.cpp debounce.cpp)

target_link_libraries(alcyone wiringPi boost_thread-mt boost_program_options)