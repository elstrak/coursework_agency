cmake_minimum_required(VERSION 3.5)

project(CourseWork VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CourseWork
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET CourseWork APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(CourseWork SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(CourseWork
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(CourseWork PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


########## Моя писанина
add_library(ListRealtorsLib ListRealtors.cpp)
add_library(ListDealsLib ListDeals.cpp)

add_library(HTRealtorsLib HashTableRealtors.cpp)
add_library(HTDealsLib HashTableDeals.cpp)
add_library(TreeRealtorsLib TreeRealtors.cpp)
add_library(TreeDealsLib TreeDeals.cpp)
add_library(ParserLib Parser.cpp)

target_link_libraries(TreeRealtorsLib ListRealtorsLib)
target_link_libraries(TreeDealsLib ListDealsLib)

add_library(StructuresLib Structures.cpp)
add_library(ToStringLib ToString.cpp)
target_link_libraries(ToStringLib PUBLIC StructuresLib)
target_link_libraries(HTRealtorsLib PUBLIC ToStringLib)
target_link_libraries(HTDealsLib PUBLIC ToStringLib)

add_library(realtorsLib Realtors.cpp)
target_link_libraries(realtorsLib PUBLIC HTRealtorsLib TreeRealtorsLib ParserLib ToStringLib)
add_library(dealsLib Deals.cpp)
target_link_libraries(dealsLib PUBLIC HTDealsLib TreeDealsLib ParserLib ToStringLib)

add_library(databaseLib Database.cpp)
target_link_libraries(databaseLib PUBLIC realtorsLib dealsLib)

target_link_libraries(CourseWork PUBLIC databaseLib)
########## Конец моей писанины

set_target_properties(CourseWork PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CourseWork)
endif()
