#if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
#    add_compile_definitions(UNIT_TEST)
#endif()
add_compile_options(-fPIC)
include_directories(
        Controller
        Model
        Chassis
        Tachometr
#        Eeprom
#        pins
)
add_library(CarModules STATIC Controller/Controller.cpp
        Model/Model.cpp
        Chassis/Chassis.cpp
        Tachometr/Tachometr.cpp
        Tachometr/Tachometr.h
#        Eeprom/Eeprom.hpp
        Config/Config.cpp
        Config/Config.h
        Chassis/pins.h)
target_link_libraries(CarModules Modules LeOS2Mock)
#target_link_libraries(CarModules STATIC LeOS2Mock)