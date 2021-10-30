#if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
#    add_compile_definitions(UNIT_TEST)
#endif()
include_directories(
        ByteArray
        config
        Logger
        Communicator
        CircularBuffer
        Math
#        RadioExtended
#        RadioMessage
)
add_library(Modules STATIC ByteArray/ByteArray.cpp Logger/Logger.cpp Logger/Logger.h
        Math/Der.hpp
        Math/Other.hpp
#        RadioExtended/RadioExtended.cpp RadioMessage/RadioMessage.cpp
        CircularBuffer/CircularBuffer.h
        Communicator/Communicator.h Communicator/SerialCommunicator.cpp Communicator/SerialCommunicator.h
        Communicator/Message.h Communicator/Listener.h Communicator/Communicator.cpp Communicator/Message.cpp Communicator/SerialMock.h)