cmake_minimum_required(VERSION 3.9)
project(gerador3)

set(CMAKE_CXX_STANDARD 17)

add_executable(gerador3 gerador/gerador.cpp motor/headers/Camara.h)


project(motor3)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
add_executable(motor3 motor/motor.cpp motor/Ponto.cpp motor/tinyxml2.cpp motor/Transformacao.cpp motor/Rotacao.cpp motor/Translacao.cpp motor/Escala.cpp motor/Transforms.cpp motor/Cor.cpp motor/Camara.cpp)

target_link_libraries(motor3 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
include_directories(motor/headers)