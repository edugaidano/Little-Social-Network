project(Server)

set(SOURCES
    src/main.cpp

    src/server_storage/server_storage.cpp

    src/start_server/start_server.cpp

    src/user_manager/user_manager.cpp
    src/user_manager/functions/makeLogin.cpp
    src/user_manager/functions/makeRegistration.cpp
    src/user_manager/functions/deleteMessage.cpp
    src/user_manager/functions/findMessage.cpp
    src/user_manager/functions/findMessagesList.cpp
    src/user_manager/functions/searchProfile.cpp
    src/user_manager/functions/sendMessage.cpp
    src/user_manager/functions/updateProfile.cpp
)

add_executable(Server ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(Server
    Global
    ws2_32
    -static
    -static-libgcc
    -static-libstdc++
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/../Global/config/Server.conf
    ${CMAKE_CURRENT_BINARY_DIR}/Server.conf
    COPYONLY
)

install(FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/../Global/config/Server.conf
    DESTINATION .
)