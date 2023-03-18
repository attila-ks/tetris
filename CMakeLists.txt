cmake_minimum_required(VERSION 3.16)

project(tetris VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "$ENV{QTHOME}")

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

qt_add_executable(a.out
    backend/src/main.cpp
    backend/headers/tetrion.h
    backend/src/tetrion.cpp
    backend/headers/gameboard.h
    backend/headers/tetrisboard.h
    backend/src/tetrisboard.cpp
    backend/headers/tetromino.h
    backend/src/tetromino.cpp
    backend/headers/block.h
    backend/src/block.cpp
    backend/headers/index.h
    backend/src/index.cpp
    backend/headers/Key.h
    backend/headers/Settings.h
    backend/headers/KeyEvent.h
    backend/headers/KeyboardEventHandler.h
    backend/src/KeyboardEventHandler.cpp
)

qt_add_qml_module(a.out
    URI tetris
    VERSION 1.0
    QML_FILES
        frontend/main.qml
        frontend/MainMenu.qml
        frontend/TextButton.qml
        frontend/TetrisBoard.qml
        frontend/GameOverMenu.qml
    RESOURCES
        resources/images/background.jpg
        resources/fonts/Streamster.ttf
)

set_target_properties(a.out PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(a.out
    PRIVATE Qt6::Quick)

install(TARGETS a.out
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
