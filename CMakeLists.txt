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
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        find_program(DEPLOY_QT_EXECUTABLE macdeployqt)
        set(OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME})
        set(BUNDLE_DIR ${OUTPUT_DIR}.app)
        add_custom_command(TARGET TodoList POST_BUILD
                COMMAND "${DEPLOY_QT_EXECUTABLE}" ${BUNDLE_DIR} -qmldir=${PROJECT_SOURCE_DIR} -dmg
                BYPRODUCTS ${BUNDLE_DIR} ${OUTPUT_DIR}.dmg
                COMMENT "Running macdeployqt...")
    endif()
elseif(WIN32)
    add_executable(TodoList WIN32 ${SOURCES} ${RESOURCES})
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        find_program(DEPLOY_QT_EXECUTABLE windeployqt)
        set(OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/output")
        add_custom_command(TARGET TodoList POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIR}
                COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:TodoList> ${OUTPUT_DIR}
                COMMAND "${DEPLOY_QT_EXECUTABLE}" ${OUTPUT_DIR} -qmldir=${PROJECT_SOURCE_DIR}
                BYPRODUCTS ${OUTPUT_DIR}
                COMMENT "Running windeployqt...")
        if (DEFINED ENV{NSIS_PATH})
            find_program(NSIS_EXECUTABLE makensis $ENV{NSIS_PATH} REQUIRED)
            add_custom_command(TARGET TodoList POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E env
                        NSIS_INPUT_DIR=${OUTPUT_DIR}
                        NSIS_OUTPUT_DIR=${OUTPUT_DIR}
                    "${NSIS_EXECUTABLE}" "${PROJECT_SOURCE_DIR}/windows/installer.nsi"
                    COMMENT "Compiling an installer...")
        else()
            add_custom_command(TARGET TodoList POST_BUILD
                    COMMENT "NSIS executable was not found - skipping installer compilation.")
        endif ()
    endif()
elseif(ANDROID)
    add_library(TodoList SHARED ${SOURCES} ${RESOURCES})
    set(ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android CACHE INTERNAL "")
endif()

target_link_libraries(TodoList Qt5::Quick)