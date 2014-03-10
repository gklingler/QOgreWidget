project(demo)
cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5X11Extras REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread)

INCLUDE_DIRECTORIES(
    /usr/include/OGRE
  )


add_executable(QOgreWidgetDemo   
  QOgreWidget.cpp 
  QOgreWidgetDemo.cpp
  main.cpp
  )

qt5_use_modules(QOgreWidgetDemo OpenGL Widgets X11Extras)

target_link_libraries(QOgreWidgetDemo
    ${OPENGL_LIBRARIES}
    OgreMain
    boost_system
    boost_thread
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
