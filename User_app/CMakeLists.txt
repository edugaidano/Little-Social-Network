project(User_app)

find_package(Qt6 6.10 REQUIRED COMPONENTS Core Widgets LinguistTools)

qt_standard_project_setup()

set(SOURCES 
    src/main.cpp
    src/AppController.cpp
    src/Communicator.cpp

    src/make_connection/make_connection.cpp

    src/WidgetController/ConfigController.cpp
    src/WidgetController/LoginController.cpp
    src/WidgetController/MainMenuController.cpp
    src/WidgetController/SearchProfileController.cpp
    src/WidgetController/ProfileSearchedController.cpp
    src/WidgetController/OwnProfileController.cpp
    src/WidgetController/EditorController.cpp
    src/WidgetController/MessageController.cpp
    src/WidgetController/InboxController.cpp
    src/WidgetController/MessageEditorController.cpp

    src/Widget/config_widget.cpp
    src/Widget/login_widget.cpp
    src/Widget/main_menu_widget.cpp
    src/Widget/message_item_widget.cpp
    src/Widget/message_widget.cpp
    src/Widget/messages_interface_widget.cpp
    src/Widget/profile_editor_widget.cpp
    src/Widget/profile_widget.cpp
    src/Widget/search_widget.cpp
    src/Widget/send_message_widget.cpp
)

set(HEADER_FILES
    include/dialog.h
    include/AppController.h
    include/Communicator.h

    src/make_connection/make_connection.h

    include/WidgetController/WidgetController.h
    include/WidgetController/ConfigController.h
    include/WidgetController/LoginController.h
    include/WidgetController/MainMenuController.h
    include/WidgetController/SearchProfileController.h
    include/WidgetController/ProfileSearchedController.h
    include/WidgetController/OwnProfileController.h
    include/WidgetController/EditorController.h
    include/WidgetController/MessageController.h
    include/WidgetController/InboxController.h
    include/WidgetController/MessageEditorController.h

    include/Widget/config_widget.h
    include/Widget/login_widget.h
    include/Widget/main_menu_widget.h
    include/Widget/message_item_widget.h
    include/Widget/message_widget.h
    include/Widget/messages_interface_widget.h
    include/Widget/profile_editor_widget.h
    include/Widget/profile_widget.h
    include/Widget/search_widget.h
    include/Widget/send_message_widget.h
)

set(UI_FILES
    ui/config_widget.ui
    ui/login_widget.ui
    ui/main_menu_widget.ui
    ui/message_item_widget.ui
    ui/message_widget.ui
    ui/messages_interface_widget.ui
    ui/profile_editor_widget.ui
    ui/profile_widget.ui
    ui/search_widget.ui
    ui/send_message_widget.ui
)

set(CMAKE_AUTOUIC_SEARCH_PATHS
    ${CMAKE_CURRENT_SOURCE_DIR}/ui
)

set(TS_FILES
    translations/app_ESP.ts
)

qt_add_executable(User_app
    WIN32
    ${UI_FILES}
    ${HEADER_FILES}
    ${SOURCES}
)

target_include_directories(User_app
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
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