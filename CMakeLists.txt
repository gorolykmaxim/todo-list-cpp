cmake_minimum_required(VERSION 3.16)
project(TodoList)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Quick REQUIRED)
qt5_add_resources(RESOURCES qml.qrc)

add_executable(TodoList
        MACOSX_BUNDLE
        addtodoviewmodel.cpp
        addtodoviewmodel.h
        listviewmodel.cpp
        listviewmodel.h
        main.cpp
        todolist.cpp
        todolist.h
        todomodel.cpp
        todomodel.h
        macos/icon.icns
        ${RESOURCES})

set_source_files_properties(macos/icon.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
set_target_properties(TodoList PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${PROJECT_SOURCE_DIR}/macos/Info.plist)

target_link_libraries(TodoList Qt5::Quick)

find_program(MACDEPLOYQT_EXECUTABLE macdeployqt ${CMAKE_PREFIX_PATH})

add_custom_command(TARGET TodoList POST_BUILD
        COMMAND "${MACDEPLOYQT_EXECUTABLE}"
        "$<TARGET_FILE_DIR:TodoList>/../.."
        -qmldir=${PROJECT_SOURCE_DIR}
        COMMENT "Running macdeployqt...")
