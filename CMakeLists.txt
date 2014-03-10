project(demo)
cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5X11Extras REQUIRED)
find_package(OpenGL)

set(OGRE_LOC /home/gernot/src/external/install/ogre3d_v1.8.1)

LINK_DIRECTORIES(
    ${OGRE_LOC}/lib
    /home/gernot/src/playground/external/install/boost_v1.54/lib
  )

INCLUDE_DIRECTORIES(
    ${OGRE_LOC}/include
    /usr/include/OIS
    /usr/include/OGRE
    /home/gernot/src/playground/external/install/boost_v1.54/include
  )

set(QOgreWidget_SOURCES 
  QOgreWidget.cpp 
  QOgreWidgetDemo.cpp
  main.cpp
  )


add_executable(QOgreWidgetDemo ${QOgreWidget_SOURCES})

qt5_use_modules(QOgreWidgetDemo OpenGL Widgets X11Extras)

target_link_libraries(QOgreWidgetDemo
    ${OPENGL_LIBRARIES}
    OgreMain
    boost_system
    OIS
  )

file(COPY ${PROJECT_SOURCE_DIR}/resources.cfg DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/plugins.cfg DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/resources/ogrehead.mesh DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/resources/Ogre.material DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/resources/DualQuaternion_Common.glsl DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/resources/hdr_tonemap_util.glsl DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/resources/tusk.jpg DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/resources/spheremap.png DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/resources/GreenSkin.jpg DESTINATION ${PROJECT_BINARY_DIR})

install(TARGETS QOgreWidgetDemo RUNTIME DESTINATION bin)
