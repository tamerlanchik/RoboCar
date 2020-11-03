include_directories(
        Controller
    Map
    pins
)
add_library(CarModules SHARED Controller/Controller.cpp Map/Map.cpp)
target_link_libraries(CarModules PUBLIC Modules)