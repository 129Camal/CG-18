//
// Created by 87 Dolly on 29/03/2018.
//
#include "headers/Cor.h"

Cor::Cor() {
    red = 1.0;
    green = 1.0;
    blue = 1.0;
}

Cor::Cor(float r, float g, float b) {
    red = r;
    green = g;
    blue = b;
}

bool Cor::semCor(){
    return (red==0 && green==0 && blue==0);
}


