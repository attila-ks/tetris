cmake_minimum_required(VERSION 3.16)

project(tetris VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "$ENV{QTHOME}")

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Multimedia)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(a.out
    backend/src/main.cpp
    backend/headers/tetrion.h
    backend/src/tetrion.cpp
    backend/headers/gameboard.h
    backend/headers/Playfield.h
    backend/src/Playfield.cpp
    backend/headers/tetromino.h
    backend/src/tetromino.cpp
    backend/headers/GhostTetromino.h
    backend/src/GhostTetromino.cpp
    backend/headers/block.h
    backend/src/block.cpp
    backend/headers/Key.h
    backend/headers/KeyEvent.h
    backend/headers/KeyboardEventHandler.h
    backend/src/KeyboardEventHandler.cpp
    backend/headers/FileError.h
    backend/src/FileError.cpp
    backend/headers/MediaPlayer.h
    backend/src/MediaPlayer.cpp
)

qt_add_qml_module(a.out
    URI tetris
    VERSION 1.0
    QML_FILES
        frontend/Main.qml
        frontend/MainMenu.qml
        frontend/TextButton.qml
        frontend/Playfield.qml
        frontend/GameOverMenu.qml
        frontend/Line.qml
        frontend/CircularProgressBar.qml
        frontend/NextTetrominoDisplay.qml
        frontend/InfoDisplay.qml
        frontend/PauseMenu.qml
    RESOURCES
        resources/images/background.jpg
        resources/fonts/Streamster.ttf
        resources/images/tetrominoes/Tetromino-I.svg
        resources/images/tetrominoes/Tetromino-J.svg
        resources/images/tetrominoes/Tetromino-L.svg
        resources/images/tetrominoes/Tetromino-O.svg
        resources/images/tetrominoes/Tetromino-S.svg
        resources/images/tetrominoes/Tetromino-T.svg
        resources/images/tetrominoes/Tetromino-Z.svg
)

set_target_properties(a.out PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(a.out
  PRIVATE Qt6::Quick Qt6::Multimedia)

install(TARGETS a.out
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
