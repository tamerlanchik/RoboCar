aux_source_directory(. SRC_LIST)
aux_source_directory(fakeit SRC_LIST)
aux_source_directory(arduino SRC_LIST)

add_library(${PROJECT_NAME} STATIC ${SRC_LIST})

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")