cmake_minimum_required(VERSION 3.16)
project(Robocar)

set(CMAKE_CXX_STANDARD 14)
include_directories(src)
include_directories(test)
include_directories(lib)
include_directories(mock)

add_executable(CarTest1 test/car/test_1.cpp)
add_executable(TestChassis test/car/test_chasssis.cpp)
add_executable(TestTachometr test/car/test_tachometr.cpp)
add_executable(Car src/cmd/car.cpp)

set(TESTS_TARGETS CarTest1 TestChassis TestTachometr)

#if(TARGET Car OR TARGET CarTest1 TestChassis)
#if("bar" IN_LIST TESTS_TARGETS)
add_subdirectory(mock/ArduinoFake)
add_subdirectory(src/car)
add_subdirectory(src/modules)
add_subdirectory(lib/Vector)
#    add_compile_definitions(UNIT_TEST)
#endif()

#if(TARGET Car)
#    add_subdirectory(lib/leOS2)
#endif()
add_subdirectory(mock/leOS2Mock)

if(TARGET CarTest1)
#    include_directories(mock)
#    add_subdirectory(mock/leOS2)
endif()

# Write down all test targets
#set(TESTS_TARGETS CarTest1 Car)
set(LIB_LIST ArduinoFake unity CarModules Modules Vector)
foreach(target ${TESTS_TARGETS})
    target_compile_definitions(${target} PUBLIC UNIT_TEST)
    target_link_libraries(${target} PUBLIC ${LIB_LIST})
endforeach()

#if(TARGET CarTest1)
    target_link_libraries(CarTest1 PUBLIC LeOS2Mock)
#endif()


#add_executable(Robocar src/main/test.cpp src/core/Scheduller.cpp
#        src/core/controller_interface/IPin.h
#        src/core/arduino/Pin.h src/core/arduino/Pin.cpp
#        src/core/controller_interface/IUtils.h
#        src/core/arduino/Utils.cpp src/core/arduino/Utils.h)
#
#target_include_directories(Robocar PUBLIC test/ArduinoFake)