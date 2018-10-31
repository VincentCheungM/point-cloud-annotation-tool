cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(point_cloud_annotation_tool)
SET(CMAKE_CXX_FLAGS "-std=c++11 -O2")


# Hide the console window in visual studio projects - Release
if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()
# Use ccache to speed up compile process
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

if(POLICY CMP0071)
    cmake_policy(SET CMP0071 NEW)
endif()

if(POLICY CMP0020)
    cmake_policy(SET CMP0020 NEW)
endif()

FIND_PACKAGE(VTK)
INCLUDE(${VTK_USE_FILE}) # include UseVTK.cmake
message(STATUS "VTK_LIBRARIES: ${VTK_LIBRARIES}")

find_package(PCL REQUIRED COMPONENTS)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
message(STATUS "PCL_LIBRARIES: ${PCL_LIBRARIES}")


include_directories(${CMAKE_SOURCE_DIR})
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON) # For meta object compiler
set(CMAKE_AUTORCC ON) # Resource files
#set(CMAKE_AUTOUIC ON) # UI files
find_package(Qt5 COMPONENTS Widgets REQUIRED)
QT5_WRAP_UI(ui_mainwindow.h mainwindow.ui)

set(project_source 
    # common.h
    main.cpp
    # visualizer.h
    visualizer.cpp
        # vtkBoxWidgetCallback.h
        vtkBoxWidgetCallback.cpp
        # vtkBoxWidgetRestricted.h
        vtkBoxWidgetRestricted.cpp
        # vtkAnnotationBoxSource.h
        vtkAnnotationBoxSource.cpp
    # Annotaion.h
    Annotation.cpp
    # pcl/visualization/pcl_visualizer_extented.h
    pcl/visualization/pcl_visualizer_extented.cpp
    # pcl/visualization/MyCloudLUT.h
    pcl/visualization/MyCloudLUT.cpp
    # pcl/visualization/PointCloudColorHandlerLUT.h
    # view/flowlayout.h
    view/flowlayout.cpp
    )


add_executable(${PROJECT_NAME} ${project_source} ui_mainwindow.h)
target_link_libraries(${PROJECT_NAME} ${PCL_LIBRARIES} Qt5::Widgets)

# option(BUILD_TEST "build test exampes" ON)
# if (BUILD_TEST)
#    add_subdirectory(test)
# endif()

# option(BUILD_TOOLS "build tools" ON)
# if (BUILD_TOOLS)
#    add_subdirectory(tool)
# endif()

## Copy config.json file.
message(STATUS "Copying config file to ${CMAKE_CURRENT_BINARY_DIR}/config/")
FILE(COPY config/config.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/config/)