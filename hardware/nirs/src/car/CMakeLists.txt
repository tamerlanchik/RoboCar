if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    add_compile_definitions(UNIT_TEST)
endif()
include_directories(
        Controller
        Model
        Chassis
        Tachometr
#        pins
)
add_library(CarModules SHARED Controller/Controller.cpp
        Model/Model.cpp
        Chassis/Chassis.cpp
        Tachometr/Tachometr.cpp
        Chassis/pins.h config.h)
target_link_libraries(CarModules PUBLIC Modules)