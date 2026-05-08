project(User_app)

find_package(Qt6 6.10 REQUIRED COMPONENTS Core Widgets LinguistTools)

qt_standard_project_setup()

qt_add_executable(User_app
    WIN32
    src/main.cpp
    
    src/appController/app_controller.cpp
    src/appController/app_controller.h

    src/communicationController/communication_controller.h
    src/communicationController/constructor.cpp
    src/communicationController/destructor.cpp
    src/communicationController/utils/closeServerConnection.cpp
    src/communicationController/utils/makeConnection.cpp
    src/communicationController/utils/reconnectToServer.cpp
    src/communicationController/utils/serverConnectionIsOk.cpp
    src/communicationController/actions/deleteMessage.cpp
    src/communicationController/actions/login.cpp
    src/communicationController/actions/requestMessageContent.cpp
    src/communicationController/actions/requestMessages.cpp
    src/communicationController/actions/searchOwnProfile.cpp
    src/communicationController/actions/searchProfile.cpp
    src/communicationController/actions/sendMessage.cpp
    src/communicationController/actions/updateProfile.cpp
    
    src/dialog/dialog.cpp
    src/dialog/dialog.h
    src/dialog/dialog.ui

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