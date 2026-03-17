add_library(utils
    logs/logs.cpp
    config/config.cpp
)

target_include_directories(utils PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)