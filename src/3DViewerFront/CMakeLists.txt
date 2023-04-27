cmake_minimum_required(VERSION 3.5)

project(3DViewerFront VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)
find_package(Qt6 REQUIRED COMPONENTS OpenGL)

include_directories(../3DViewerBack/)
include_directories("${PROJECT_SOURCE_DIR}/qtgifimage/src/gifimage")
include_directories("${PROJECT_SOURCE_DIR}/qtgifimage/src/3rdParty/giflib")

set(PROJECT_SOURCES
    main.cc
    mainwindow.cc
    mainwindow.h
    openglwidget.cc
    openglwidget.h
    mainwindow.ui
    qtgifimage/src/gifimage/qgifglobal.h
    qtgifimage/src/gifimage/qgifimage.h
    qtgifimage/src/gifimage/qgifimage_p.h
    qtgifimage/src/gifimage/qgifimage.cpp
    qtgifimage/src/3rdParty/giflib/dgif_lib.c
    qtgifimage/src/3rdParty/giflib/egif_lib.c
    qtgifimage/src/3rdParty/giflib/gifalloc.c
    qtgifimage/src/3rdParty/giflib/gif_err.c
    qtgifimage/src/3rdParty/giflib/gif_font.c
    qtgifimage/src/3rdParty/giflib/gif_hash.c
    qtgifimage/src/3rdParty/giflib/gif_hash.c
    qtgifimage/src/3rdParty/giflib/quantize.c
)
set(C_SOURCES
    3DViewer.h
    struct.h
    fill_struct.c
    scale_struct.c
    rotate_struct.c
    translate_struct.c
    remove_struct.c
)
list(TRANSFORM C_SOURCES PREPEND "../3DViewerBack/")
set(MATRIX_SOURCES
    matrix.h
    matrix_struct.h
    operation_functions/create_matrix.c
    operation_functions/remove_matrix.c
)
list(TRANSFORM MATRIX_SOURCES PREPEND "../3DViewerBack/matrix/")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3DViewerFront
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${C_SOURCES}
        ${MATRIX_SOURCES}
    )

# Define target properties for Android with Qt 6 as:
# set_property(TARGET 3DViewerFront APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
# ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(3DViewerFront SHARED
            ${PROJECT_SOURCES}
            ${C_SOURCES}
            ${MATRIX_SOURCES}
        )

    # Define properties for Android with Qt 5 after find_package() calls as:
    # set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(3DViewerFront
            ${PROJECT_SOURCES}
            ${C_SOURCES}
            ${MATRIX_SOURCES}
        )
    endif()
endif()

target_link_libraries(3DViewerFront PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(3DViewerFront PRIVATE Qt${QT_VERSION_MAJOR}::OpenGLWidgets)
target_link_libraries(3DViewerFront PRIVATE Qt${QT_VERSION_MAJOR}::OpenGL)

set_target_properties(3DViewerFront PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS 3DViewerFront
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3DViewerFront)
endif()
