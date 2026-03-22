project(Server)

file(GLOB_RECURSE SRC_FILES
    src/main.cpp
    src/start_server/start_server.cpp
    src/user_manager/user_manager.cpp
    src/check_login_register/check_login_register.cpp
    src/search_profile/search_profile.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(Server
    utils
    ws2_32
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/../utils/config/config_file.conf
    ${CMAKE_CURRENT_BINARY_DIR}/config_file.conf
    COPYONLY
)

install(FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/../utils/config/config_file.conf
    DESTINATION .
)