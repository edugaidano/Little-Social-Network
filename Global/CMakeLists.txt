add_library(Global
    logs/logs.cpp
    config/config.cpp
    serialization/serialization.cpp
    communication/communication.cpp
)

target_include_directories(Global PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)