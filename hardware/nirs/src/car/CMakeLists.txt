if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    add_compile_definitions(UNIT_TEST)
endif()
add_compile_options(-fPIC)
include_directories(
        Controller
        Model
        Chassis
        Tachometr
#        Eeprom
#        pins
)
add_library(CarModules SHARED Controller/Controller.cpp
        Model/Model.cpp
        Chassis/Chassis.cpp
        Tachometr/Tachometr.cpp
        Tachometr/Tachometr.h
#        Eeprom/Eeprom.hpp
        config.cpp
        Chassis/pins.h config.h)
target_link_libraries(CarModules Modules LeOS2Mock)
#target_link_libraries(CarModules STATIC LeOS2Mock)