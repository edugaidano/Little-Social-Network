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
    src/WidgetController/ProfileEditorController.cpp
    src/WidgetController/MessageController.cpp
    src/WidgetController/InboxController.cpp
    src/WidgetController/MessageEditorController.cpp

    src/Widget/ConfigWidget.cpp
    src/Widget/LoginWidget.cpp
    src/Widget/MainMenuWidget.cpp
    src/Widget/MessageItemWidget.cpp
    src/Widget/MessageWidget.cpp
    src/Widget/InboxWidget.cpp
    src/Widget/ProfileEditorWidget.cpp
    src/Widget/ProfileWidget.cpp
    src/Widget/SearchWidget.cpp
    src/Widget/MessageEditorWidget.cpp
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
    include/WidgetController/ProfileEditorController.h
    include/WidgetController/MessageController.h
    include/WidgetController/InboxController.h
    include/WidgetController/MessageEditorController.h

    include/Widget/ConfigWidget.h
    include/Widget/LoginWidget.h
    include/Widget/MainMenuWidget.h
    include/Widget/MessageItemWidget.h
    include/Widget/MessageWidget.h
    include/Widget/InboxWidget.h
    include/Widget/ProfileEditorWidget.h
    include/Widget/ProfileWidget.h
    include/Widget/SearchWidget.h
    include/Widget/MessageEditorWidget.h
)

set(UI_FILES
    ui/ConfigWidget.ui
    ui/LoginWidget.ui
    ui/MainMenuWidget.ui
    ui/MessageItemWidget.ui
    ui/MessageWidget.ui
    ui/InboxWidget.ui
    ui/ProfileEditorWidget.ui
    ui/ProfileWidget.ui
    ui/SearchWidget.ui
    ui/MessageEditorWidget.ui
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