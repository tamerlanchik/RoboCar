include_directories(
        ByteArray
        config
        Logger
        Logger/Serial
#        RadioExtended
#        RadioMessage
)
add_library(Modules SHARED ByteArray/ByteArray.cpp Logger/Logger.cpp Logger/Serial/Serial.cpp
#        RadioExtended/RadioExtended.cpp RadioMessage/RadioMessage.cpp
        )