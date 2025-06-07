cmake_minimum_required(VERSION 3.16)

project(gxde-vm LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets DBus X11Extras)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets DBus X11Extras)

find_package(KF5WindowSystem)



add_executable(gxde-vm
  main.cpp
  switchwindow.h switchwindow.cpp
  vmcontroller.h vmcontroller.cpp
  vminstallwindow.h vminstallwindow.cpp
  configreader.h configreader.cpp
  commondefine.h
  qbrowseredit.h qbrowseredit.cpp

)
target_link_libraries(gxde-vm Qt${QT_VERSION_MAJOR}::Core
                              Qt${QT_VERSION_MAJOR}::Widgets
                              Qt${QT_VERSION_MAJOR}::DBus
                              Qt${QT_VERSION_MAJOR}::X11Extras
                              KF5::WindowSystem)

include(GNUInstallDirs)
install(TARGETS gxde-vm
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
