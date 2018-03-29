//
// Created by 87 Dolly on 28/03/2018.
//

#include "headers/Rotacao.h"

Rotacao::Rotacao() {
    angle = 0.0;
    x_eixo = 0.0;
    y_eixo = 0.0;
    z_eixo = 0.0;
}

Rotacao::Rotacao(float angle, float x, float y, float z) {
    this->angle = angle;
    x_eixo = x;
    y_eixo = y;
    z_eixo = z;
}