cmake_minimum_required(VERSION 3.9)
project(gerador4)

set(CMAKE_CXX_STANDARD 17)

add_executable(gerador4 gerador/gerador.cpp motor/headers/Camara.h)

project(motor4)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(DevIL REQUIRED)

add_executable(motor4 motor/motor.cpp motor/Ponto.cpp motor/tinyxml2.cpp motor/Transformacao.cpp motor/Rotacao.cpp motor/Translacao.cpp motor/Escala.cpp motor/Transforms.cpp motor/Cor.cpp motor/Camara.cpp)

target_link_libraries(motor4 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${IL_LIBRARIES})
include_directories(ยง{IL_INCLUDE_DIR})
include_directories(motor/headers)