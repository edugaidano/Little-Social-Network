cmake_minimum_required(VERSION 4.2)
project(User_app LANGUAGES CXX)

find_package(Qt6 6.10 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

add_subdirectory(../Utils utils_build)

qt_add_executable(User_app
    WIN32
    src/main.cpp
    
    src/appController/app_controller.cpp
    src/appController/app_controller.h

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
)

target_link_libraries(User_app
    PRIVATE
        Qt::Core
        Qt::Widgets
        utils
)

include(GNUInstallDirs)

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