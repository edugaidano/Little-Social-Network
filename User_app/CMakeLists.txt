project(User_app)

find_package(Qt6 6.10 REQUIRED COMPONENTS Core Widgets LinguistTools)

qt_standard_project_setup()

qt_add_executable(User_app
    WIN32
    src/main.cpp
    
    src/appController/app_controller.cpp
    src/appController/app_controller.h

    src/connect_server/connect_server.cpp
    src/connect_server/connect_server.h

    src/communicationController/communication_controller_general.cpp
    src/communicationController/login_request.cpp
    src/communicationController/register_request.cpp
    src/communicationController/search_request.cpp
    src/communicationController/update_request.cpp
    src/communicationController/messages_request.cpp
    src/communicationController/message_request.cpp
    src/communicationController/delete_request.cpp
    src/communicationController/send_request.cpp
    src/communicationController/communication_controller.h

    src/dialog/dialog.cpp
    src/dialog/dialog.h
    src/dialog/dialog.ui

    src/login/login_widget.cpp
    src/login/login_widget.h
    src/login/login_widget.ui

    src/main_menu/main_menu_widget.cpp
    src/main_menu/main_menu_widget.h
    src/main_menu/main_menu_widget.ui

    src/profile/profile_widget.cpp
    src/profile/profile_widget.h
    src/profile/profile_widget.ui

    src/profile_editor/profile_editor_widget.cpp
    src/profile_editor/profile_editor_widget.h
    src/profile_editor/profile_editor_widget.ui

    src/search/search_widget.cpp
    src/search/search_widget.h
    src/search/search_widget.ui

    src/messages_interface/messages_interface_widget.cpp
    src/messages_interface/messages_interface_widget.h
    src/messages_interface/messages_interface_widget.ui

    src/message_item/message_item_widget.cpp
    src/message_item/message_item_widget.h
    src/message_item/message_item_widget.ui

    src/message/message_widget.cpp
    src/message/message_widget.h
    src/message/message_widget.ui

    src/send_message/send_message_widget.cpp
    src/send_message/send_message_widget.h
    src/send_message/send_message_widget.ui

    src/config/config_widget.cpp
    src/config/config_widget.h
    src/config/config_widget.ui
)

set(TS_FILES
    translations/app_ESP.ts
)

qt_add_translations(${PROJECT_NAME}
    TS_FILES ${TS_FILES}
)

target_link_libraries(User_app
    PRIVATE
        Qt::Core
        Qt::Widgets
        utils
        ws2_32
)

include(GNUInstallDirs)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/../utils/config/User.conf
    ${CMAKE_CURRENT_BINARY_DIR}/User.conf
    COPYONLY
)

install(FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/../utils/config/User.conf
    DESTINATION .
)

install(TARGETS User_app
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET User_app
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})