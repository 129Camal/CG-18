//
// Created by 87 Dolly on 28/03/2018.
//

#include "headers/Escala.h"

Escala::Escala(){
    x_eixo = 0.0;
    y_eixo = 0.0;
    z_eixo = 0.0;
}

Escala::Escala(float x, float y, float z) {
    x_eixo = x;
    y_eixo = y;
    z_eixo = z;
}

bool Escala::semEscala(){
    return (x_eixo == 0 && y_eixo == 0 && z_eixo == 0);
}