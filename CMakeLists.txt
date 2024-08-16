cmake_minimum_required(VERSION 3.5)

project(VideoPlayer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/home/m7mdodeh/qt/6.7.2/gcc_64/")

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(OpenCV REQUIRED)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    src/fpscalculator.cpp
    include/fpscalculator.h
    src/frameprocessor.cpp
    include/frameprocessor.h
    src/imageloader.cpp
    include/imageloader.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(VideoPlayer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(VideoPlayer SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(VideoPlayer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(VideoPlayer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${OpenCV_LIBS})  # Link against OpenCV

set_target_properties(VideoPlayer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(VideoPlayer)
endif()
