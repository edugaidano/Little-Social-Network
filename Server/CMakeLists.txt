project(Server)

set(SOURCES
    src/main.cpp

    src/server_storage/server_storage.cpp

    src/start_server/start_server.cpp

    src/user_manager/user_manager.cpp

    src/check_login_register/check_login_register.cpp
    src/search_profile/search_profile.cpp
    src/update_profile/update_profile.cpp
    src/find_messages_list/find_messages_list.cpp
    src/find_message/find_message.cpp
    src/delete_message/delete_message.cpp
    src/send_message/send_message.cpp
)

add_executable(Server ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(Server
    utils
    ws2_32
    -static
    -static-libgcc
    -static-libstdc++
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/../utils/config/Server.conf
    ${CMAKE_CURRENT_BINARY_DIR}/Server.conf
    COPYONLY
)

install(FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/../utils/config/Server.conf
    DESTINATION .
)