cmake_minimum_required(VERSION 3.5)

project(Questionnaire LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

#add_subdirectory(3rdparty/)

find_package(Qt5 COMPONENTS Widgets Gui Core PrintSupport REQUIRED)

file(GLOB_RECURSE H_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
                          "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
file(GLOB_RECURSE CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE UI_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")
file(GLOB_RECURSE QRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.qrc")

list(FILTER H_FILES EXCLUDE REGEX ${CMAKE_CURRENT_BINARY_DIR})
list(FILTER H_FILES EXCLUDE REGEX 3rdparty/)
list(FILTER CPP_FILES EXCLUDE REGEX ${CMAKE_CURRENT_BINARY_DIR})
list(FILTER CPP_FILES EXCLUDE REGEX 3rdparty/)
list(FILTER UI_FILES EXCLUDE REGEX ${CMAKE_CURRENT_BINARY_DIR})
list(FILTER QRC_FILES EXCLUDE REGEX ${CMAKE_CURRENT_BINARY_DIR})
list(FILTER QRC_FILES EXCLUDE REGEX 3rdparty/)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer")

add_executable(Questionnaire
    ${H_FILES}
    ${CPP_FILES}
    ${UI_FILES}
    ${QRC_FILES}
)

target_link_libraries(Questionnaire PRIVATE Qt5::Widgets Qt5::Gui Qt5::Core Qt5::PrintSupport)
