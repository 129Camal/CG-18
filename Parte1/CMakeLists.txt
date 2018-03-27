cmake_minimum_required(VERSION 3.9)
project(gerador1)

set(CMAKE_CXX_STANDARD 17)

add_executable(gerador1 gerador/gerador.cpp)


project(motor1)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
add_executable(motor1 motor/motor.cpp motor/tinyxml2.cpp)

target_link_libraries(motor1 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})