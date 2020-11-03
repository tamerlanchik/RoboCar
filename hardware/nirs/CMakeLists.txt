cmake_minimum_required(VERSION 3.16)
project(Robocar)

set(CMAKE_CXX_STANDARD 14)
include_directories(src)
include_directories(test)
include_directories(mock)
include_directories(lib)

add_executable(Test test/test_main.cpp)

add_executable(CarTest1 test/car/test_1.cpp)

add_executable(Car src/cmd/car.cpp)

if(TARGET Car OR TARGET CarTest1)
    add_subdirectory(mock/ArduinoFake)
    add_subdirectory(src/car)
    add_subdirectory(src/modules)
    add_subdirectory(lib/Vector)
#    add_compile_definitions(UNIT_TEST)
endif()

# Write down all test targets
set(TESTS_TARGETS Test CarTest1 Car)
set(LIB_LIST ArduinoFake unity CarModules Modules Vector)
foreach(target ${TESTS_TARGETS})
    target_compile_definitions(${target} PUBLIC UNIT_TEST)
    target_link_libraries(${target} PUBLIC ${LIB_LIST})
endforeach()


#add_executable(Robocar src/main/test.cpp src/core/Scheduller.cpp
#        src/core/controller_interface/IPin.h
#        src/core/arduino/Pin.h src/core/arduino/Pin.cpp
#        src/core/controller_interface/IUtils.h
#        src/core/arduino/Utils.cpp src/core/arduino/Utils.h)
#
#target_include_directories(Robocar PUBLIC test/ArduinoFake)