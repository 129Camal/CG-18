cmake_minimum_required(VERSION 3.9)
project(gerador2)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES motor.cpp Transformacao.cpp)

add_executable(gerador2 gerador/gerador.cpp )


project(motor2)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
add_executable(motor2 motor/motor.cpp motor/Ponto.cpp motor/tinyxml2.cpp motor/Transformacao.cpp motor/Rotacao.cpp motor/Translacao.cpp motor/Escala.cpp motor/Transforms.cpp )

target_link_libraries(motor2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})