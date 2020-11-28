cmake_minimum_required(VERSION 3.16)
project(Robocar)

set(CMAKE_CXX_STANDARD 14)
include_directories(src)
include_directories(test)
include_directories(lib)
include_directories(mock)

# Все тесты (входные точки)
add_executable(CarTest1 test/car/test_1.cpp)
add_executable(TestChassis test/car/test_chasssis.cpp)
add_executable(TestTachometr test/car/test_tachometr.cpp)
#add_executable(Car src/cmd/car.cpp)

set(TESTS_TARGETS CarTest1 TestChassis TestTachometr)

add_subdirectory(mock/ArduinoFake)
add_subdirectory(src/car)
add_subdirectory(src/modules)
add_subdirectory(lib/Vector)
add_subdirectory(mock/leOS2Mock)

# Write down all test targets
set(LIB_LIST ArduinoFake unity CarModules Modules Vector)
foreach(target ${TESTS_TARGETS})
    target_compile_definitions(${target} PUBLIC UNIT_TEST)
    target_link_libraries(${target} PUBLIC ${LIB_LIST})
endforeach()

target_link_libraries(CarTest1 PUBLIC LeOS2Mock)