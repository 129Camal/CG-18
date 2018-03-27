cmake_minimum_required(VERSION 3.9)
project(gerador2)

set(CMAKE_CXX_STANDARD 17)

add_executable(gerador2 gerador/gerador.cpp motor/motor.h motor/motor.cpp motor/tinyxml2.h motor/tinyxml2.cpp)


project(motor2)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
add_executable(motor2 motor/motor.cpp motor/tinyxml2.cpp)

target_link_libraries(motor2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})