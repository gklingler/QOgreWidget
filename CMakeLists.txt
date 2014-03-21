project(demo)
cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(WIN32)
    set(CMAKE_LIBRARY_PATH  "C:\\Program Files (x86)\\Windows Kits\\8.0\\Lib\\win8\\um\\x64")
    cmake_policy(SET CMP0020 NEW)   # to avoid cmake warning
endif()

set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(OpenGL REQUIRED)
if(UNIX)
    find_package(Qt5X11Extras REQUIRED)
    find_package(Boost REQUIRED COMPONENTS system thread)
endif()

set(OGRE_RESOURCE_FOLDER ${PROJECT_SOURCE_DIR}/resources)

if(UNIX)
    include_directories(/usr/include/OGRE)
    set(BOOST_LINK_LIBS 
        boost_system
        boost_thread
    )
    set(OGRE_PLUGIN_FOLDER /usr/lib/OGRE/)
elseif(WIN32)
    include_directories(
        "${OGRE_HOME}\\include"
        "${OGRE_HOME}\\include\\OGRE"
        "${OGRE_HOME}\\include\\OGRE\\RenderSystems\\GL"
        "${OGRE_HOME}\\boost"
    )
    set(BOOST_LINK_LIBS 
        libboost_system-vc100-mt-1_55 
        libboost_thread-vc100-mt-1_55
    )

    link_directories(
        ${LINK_DIRECORIES}
        "${OGRE_HOME}\\lib\\Release"
        "${OGRE_HOME}\\boost\\lib"
    )
    set(OGRE_PLUGIN_FOLDER "${OGRE_HOME}\\bin\\Release")
endif()

add_executable(QOgreWidgetDemo   
  QOgreWidget.cpp 
  QOgreWidgetDemo.cpp
  main.cpp
  )

if(UNIX)
    qt5_use_modules(QOgreWidgetDemo OpenGL Widgets X11Extras)
elseif(WIN32)
    qt5_use_modules(QOgreWidgetDemo OpenGL Widgets)
endif()

target_link_libraries(QOgreWidgetDemo
    ${OPENGL_LIBRARIES}
    ${BOOST_LINK_LIBS}
    OgreMain
    OIS
  )

configure_file (
  "${PROJECT_SOURCE_DIR}/plugins.cfg.in"
  "${PROJECT_BINARY_DIR}/plugins.cfg"
  )

configure_file (
  "${PROJECT_SOURCE_DIR}/resources.cfg.in"
  "${PROJECT_BINARY_DIR}/resources.cfg"
)

install(TARGETS QOgreWidgetDemo RUNTIME DESTINATION bin)
