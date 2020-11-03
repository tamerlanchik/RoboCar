include_directories(
    src
)
add_library(Vector SHARED Vector/Vector.cpp Vector.h Vector/VectorDefinitions.h Vector/VectorIterator.h)