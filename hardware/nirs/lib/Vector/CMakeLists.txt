include_directories(
    src
)
add_library(Vector STATIC src/Vector.cpp src/Vector.h src/VectorDefinitions.h src/VectorIterator.h)