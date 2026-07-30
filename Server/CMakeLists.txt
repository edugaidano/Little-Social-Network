project(Server)

set(SOURCES
    src/main.cpp

    src/server/start_server.cpp
    src/server/ServerController.cpp
    
    src/users/UserManager.cpp

    src/users/handlers/loginRequest.cpp
    src/users/handlers/registrationRequest.cpp
    src/users/handlers/updateProfileRequest.cpp
    src/users/handlers/sendMessageRequest.cpp
    src/users/handlers/searchProfileRequest.cpp
    src/users/handlers/getIndexRequest.cpp
    src/users/handlers/getMessageRequest.cpp
    src/users/handlers/deleteMessageRequest.cpp
    
    src/storage/UserIndex.cpp
    src/storage/StorageController.cpp

    src/storage/FilesManager/FilesManager.cpp
    src/storage/FilesManager/MessagesManager.cpp
    src/storage/FilesManager/ProfilesManager.cpp
)

set(INCLUDE_FILES

    includes/server/start_server.h
    include/server/ServerController.h

    include/users/UserManager.h
    include/users/handlers.h

    include/storage/storage_values.h
    include/storage/StorageController.h
    include/storage/UserIndex.h
    
    include/storage/FilesManager/FilesManager.h
    include/storage/FilesManager/MessagesManager.h
    include/storage/FilesManager/ProfilesManager.h
)

add_executable(Server 
    ${SOURCES}
    ${INCLUDES_FILES}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
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