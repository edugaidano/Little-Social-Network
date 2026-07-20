project(User_app)

find_package(Qt6 6.10 REQUIRED COMPONENTS Core Widgets LinguistTools)

qt_standard_project_setup()

qt_add_executable(User_app
    WIN32
    src/main.cpp

    src/dialog/dialog.h

    src/widgets/login/login_widget.cpp
    src/widgets/login/login_widget.h
    src/widgets/login/login_widget.ui

    src/widgets/main_menu/main_menu_widget.cpp
    src/widgets/main_menu/main_menu_widget.h
    src/widgets/main_menu/main_menu_widget.ui

    src/widgets/profile/profile_widget.cpp
    src/widgets/profile/profile_widget.h
    src/widgets/profile/profile_widget.ui

    src/widgets/profile_editor/profile_editor_widget.cpp
    src/widgets/profile_editor/profile_editor_widget.h
    src/widgets/profile_editor/profile_editor_widget.ui

    src/widgets/search/search_widget.cpp
    src/widgets/search/search_widget.h
    src/widgets/search/search_widget.ui

    src/widgets/messages_interface/messages_interface_widget.cpp
    src/widgets/messages_interface/messages_interface_widget.h
    src/widgets/messages_interface/messages_interface_widget.ui

    src/widgets/message_item/message_item_widget.cpp
    src/widgets/message_item/message_item_widget.h
    src/widgets/message_item/message_item_widget.ui

    src/widgets/message/message_widget.cpp
    src/widgets/message/message_widget.h
    src/widgets/message/message_widget.ui

    src/widgets/send_message/send_message_widget.cpp
    src/widgets/send_message/send_message_widget.h
    src/widgets/send_message/send_message_widget.ui

    src/widgets/config/config_widget.cpp
    src/widgets/config/config_widget.h
    src/widgets/config/config_widget.ui

    src/AppController/AppController.h
    src/AppController/AppController.cpp
    src/WidgetController/WidgetController.h
    src/WidgetController/ConfigController.cpp
    src/WidgetController/ConfigController.h
    src/WidgetController/LoginController.h
    src/WidgetController/LoginController.cpp
    src/WidgetController/MainMenuController.h
    src/WidgetController/MainMenuController.cpp
    src/Communicator/Communicator.h
    src/Communicator/Communicator.cpp
    src/make_connection/make_connection.h
    src/make_connection/make_connection.cpp
    src/WidgetController/SearchProfileController.h
    src/WidgetController/SearchProfileController.cpp
    src/WidgetController/ProfileSearchedController.h
    src/WidgetController/ProfileSearchedController.cpp
    src/WidgetController/OwnProfileController.h
    src/WidgetController/OwnProfileController.cpp
    src/WidgetController/EditorController.h
    src/WidgetController/EditorController.cpp
    src/WidgetController/MessageController.h
    src/WidgetController/MessageController.cpp
    src/WidgetController/InboxController.h
    src/WidgetController/InboxController.cpp
    src/WidgetController/MessageEditorController.h
    src/WidgetController/MessageEditorController.cpp
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