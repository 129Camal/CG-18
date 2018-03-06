cmake_minimum_required(VERSION 3.9)
project(gerador)

set(CMAKE_CXX_STANDARD 17)

add_executable(gerador gerador/gerador.cpp)


project(motor)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
add_executable(motor motor/motor.cpp motor/tinyxml2.cpp)

target_link_libraries(motor ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})