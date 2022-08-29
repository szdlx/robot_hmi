##############################################################################
# CMake
##############################################################################

cmake_minimum_required(VERSION 2.8.0)
project(cyrobot_monitor)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#添加c++11的支持
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
set(CMAKE_PREFIX_PATH /opt/ros/noetic)	# 这是ubuntu20.04  18： /opt/ros/medolic

##############################################################################
# Catkin
##############################################################################

# qt_build provides the qt cmake glue, roscpp the comms for a default talker
find_package (catkin REQUIRED COMPONENTS rviz roscpp sensor_msgs
    cv_bridge
    std_msgs
    image_transport
    rviz
    )

find_package(road_recognition_msgs REQUIRED)
find_package(Boost REQUIRED)

find_package(Qt5 REQUIRED Core Widgets Multimedia Location QuickWidgets PrintSupport)

set(QT_LIBRARIES Qt5::Widgets Qt5::Multimedia Qt5::Location Qt5::QuickWidgets Qt5::PrintSupport)
include_directories(
    ${road_recognition_msgs_INCLUDE_DIRS}
    ${catkin_INCLUDE_DIRS}
    include/cyrobot_monitor
    include/cyrobot_monitor/RoadLabel
    include/cyrobot_monitor/RoadPlot
    include/cyrobot_monitor/RvizPanel
)
link_directories(/lib)
# Use this to define what the package will export (e.g. libs, headers).
# Since the default here is to produce only a binary, we don't worry about
# exporting anything. 
catkin_package()

#如果要生成debug版本
SET(CMAKE_BUILD_TYPE "Debug")
#如果要生成release版本
#SET(CMAKE_BUILD_TYPE "Release")
#添加的支持debug和release支持
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
#SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")



##############################################################################
# Qt Environment
##############################################################################

# this comes from qt_build's qt-ros.cmake which is automatically 
# included via the dependency call in package.xml
#rosbuild_prepare_qt4(QtCore QtGui) # Add the appropriate components to the component list here

##############################################################################
# Sections
##############################################################################

file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ui/*.ui)
file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources/*.qrc)
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS include/cyrobot_monitor/*.hpp *.h)


QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})
QT5_WRAP_CPP(QT_MOC_HPP ${QT_MOC})
QT5_WRAP_UI(QT_FORMS_HPP ${QT_FORMS})

##############################################################################
# Sources
##############################################################################

file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)


##############################################################################
# Binaries
##############################################################################

#add_executable(cyrobot_monitor ${QT_SOURCES} ${QT_RESOURCES_CPP} ${QT_FORMS_HPP} ${QT_MOC_HPP})
add_library(quc STATIC IMPORTED)
set_property(TARGET quc PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libquc.a)

add_executable(cyrobot_monitor ${QT_FORMS_HPP} ${QT_MOC_HPP} ${QT_SOURCES} ${QT_RESOURCES_CPP})

add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(cyrobot_monitor ${QT_LIBRARIES} ${catkin_LIBRARIES} ${Boost_LIBRARIES} quc)
install(TARGETS cyrobot_monitor RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION} )
