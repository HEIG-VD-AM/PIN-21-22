cmake_minimum_required(VERSION 3.16)

project(DecontaminationUtility VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui)
qt_standard_project_setup()

set(INCLUDE_DIR include)
set(GUI_HEADERS
        ${INCLUDE_DIR}/canvas.h
        ${INCLUDE_DIR}/canvashelper.h
        ${INCLUDE_DIR}/json.h
        ${INCLUDE_DIR}/mainwindow.h
        ${INCLUDE_DIR}/particle.h
        ${INCLUDE_DIR}/position.h
        ${INCLUDE_DIR}/robot.h
        ${INCLUDE_DIR}/state.h
        ${INCLUDE_DIR}/timeline.h
        ${INCLUDE_DIR}/utility.h)
set(GUI_SOURCES canvas.cpp canvashelper.cpp main.cpp mainwindow.cpp robot.cpp)
set(UI_FILES mainwindow.ui)

add_executable(gui ${GUI_SOURCES} ${GUI_HEADERS} ${UI_FILES})
target_include_directories(gui PRIVATE ${GUI_HEADERS})
target_link_libraries(gui PRIVATE Qt6::Widgets)

set_target_properties(gui
        PROPERTIES WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON)

set(SETUP_SOURCES setup.cpp robot.cpp  ${INCLUDE_DIR}/simulation.h ${INCLUDE_DIR}/strategy.h)

add_executable(setup ${SETUP_SOURCES})