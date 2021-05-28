cmake_minimum_required(VERSION 2.6)
project(point-cloud)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(include)

add_executable(app
  include/window.hpp src/window.cpp
  include/shaderProgram.hpp src/shaderProgram.cpp
  include/matrix.hpp src/matrix.cpp
  include/camera.hpp src/camera.cpp
  include/pointCloud.hpp src/pointCloud.cpp
  include/pointCloudRenderer.hpp src/pointCloudRenderer.cpp
  src/glad/glad.c
  src/main.cpp
)

target_link_libraries(app ${CMAKE_DL_LIBS})
target_link_libraries(app glfw)
target_link_libraries(app ${OPENGL_gl_LIBRARY})
target_include_directories(app PUBLIC ${OPENGL_INCLUDE_DIR})