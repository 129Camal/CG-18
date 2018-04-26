//
// Created by 87 Dolly on 28/03/2018.
//

#include "headers/Rotacao.h"

Rotacao::Rotacao() {
    time = 0.0;
    angle = 0.0;
    x_eixo = 0.0;
    y_eixo = 0.0;
    z_eixo = 0.0;
}

Rotacao::Rotacao(float ti, float a, float x, float y, float z) {
    time = ti;
    angle  = a;
    x_eixo = x;
    y_eixo = y;
    z_eixo = z;
}

bool Rotacao::semRotacao(){
    return (time == 0.0 && angle == 0.0 && x_eixo == 0.0 && y_eixo == 0.0 && z_eixo == 0.0);
}