cmake_minimum_required(VERSION 3.16)
project(Robocar)

set(CMAKE_CXX_STANDARD 14)
include_directories(src)
include_directories(test)
add_subdirectory(lib/ArduinoFake)

add_executable(Test test/test_main.cpp)
target_link_libraries(Test PUBLIC ArduinoFake unity)

add_executable(Robocar src/main/test.cpp src/core/Scheduller.cpp
        src/core/controller_interface/IPin.h
        src/core/arduino/Pin.h src/core/arduino/Pin.cpp
        src/core/controller_interface/IUtils.h
        src/core/arduino/Utils.cpp src/core/arduino/Utils.h)
#
#target_include_directories(Robocar PUBLIC test/ArduinoFake)