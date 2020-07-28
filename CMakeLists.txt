cmake_minimum_required(VERSION 3.16)
project(TodoList)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Quick REQUIRED)
qt5_add_resources(RESOURCES qml.qrc)

set(SOURCES
        addtodoviewmodel.cpp
        addtodoviewmodel.h
        listviewmodel.cpp
        listviewmodel.h
        main.cpp
        todolist.cpp
        todolist.h
        todomodel.cpp
        todomodel.h)

if (APPLE)
    add_executable(TodoList MACOSX_BUNDLE ${SOURCES} macos/icon.icns ${RESOURCES})
    set_source_files_properties(macos/icon.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    set_target_properties(TodoList PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${PROJECT_SOURCE_DIR}/macos/Info.plist)
    find_program(DEPLOY_QT_EXECUTABLE macdeployqt ${CMAKE_PREFIX_PATH})
endif()

target_link_libraries(TodoList Qt5::Quick)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_command(TARGET TodoList POST_BUILD
            COMMAND "${DEPLOY_QT_EXECUTABLE}"
            "$<TARGET_FILE_DIR:TodoList>/../.."
            -qmldir=${PROJECT_SOURCE_DIR}
            COMMENT "Running *deployqt...")
endif()