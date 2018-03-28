//
// Created by 87 Dolly on 28/03/2018.
//

#include "headers/Transforms.h"

Transforms::Transforms() {
    tipo = "";
    t = Transformacao::Transformacao();
    subgrupo = vector<Transforms>();
    pontos = vector<Point>();
}

Transforms::Transforms(string tipo, Transformacao t, vector<Transforms> sub, vector<Point> pontos) {
    tipo = tipo;
    t = t;
    subgrupo = sub;
    pontos = pontos;
}