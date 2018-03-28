cmake_minimum_required(VERSION 3.9)
project(gerador2)

set(CMAKE_CXX_STANDARD 17)

add_executable(gerador2 gerador/gerador.cpp motor/headers/motor.h motor/motor.cpp motor/headers/tinyxml2.h motor/tinyxml2.cpp motor/Transformacao.cpp motor/headers/Transformacao.h motor/Rotacao.cpp motor/headers/Rotacao.h motor/headers/Translacao.h motor/headers/Escala.h motor/Translacao.cpp motor/Escala.cpp)


project(motor2)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
add_executable(motor2 motor/motor.cpp motor/tinyxml2.cpp)

target_link_libraries(motor2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})