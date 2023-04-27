cmake_minimum_required(VERSION 3.5)

project(cmakeGif VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#******* lib *******
include_directories("${PROJECT_SOURCE_DIR}/src/3rdParty/giflib")
include_directories("${PROJECT_SOURCE_DIR}/src/gifimage")
# include_directories("${PROJECT_SOURCE_DIR}/include/")



set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

add_library(${PROJECT_NAME}_lib STATIC ${PROJECT_SOURCE_DIR}/src/gifimage/qgifimage.cpp
            ${PROJECT_SOURCE_DIR}/src/3rdParty/giflib/dgif_lib.c
            ${PROJECT_SOURCE_DIR}/src/3rdParty/giflib/egif_lib.c
            ${PROJECT_SOURCE_DIR}/src/3rdParty/giflib/gif_err.c
            ${PROJECT_SOURCE_DIR}/src/3rdParty/giflib/gif_font.c
            ${PROJECT_SOURCE_DIR}/src/3rdParty/giflib/gif_hash.c
            ${PROJECT_SOURCE_DIR}/src/3rdParty/giflib/gifalloc.c
            ${PROJECT_SOURCE_DIR}/src/3rdParty/giflib/quantize.c
)

target_include_directories(${PROJECT_NAME}_lib PUBLIC ${PROJECT_SOURCE_DIR} Qt5::Widgets)

#**************************************

# file(GLOB CPP_SOURCE "*.cpp" C_SOURCE "*.c")

# add_executable(${PROJECT_NAME} ${CPP_SOURCE} ${C_SOURCE})

# target_link_libraries( ${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)
