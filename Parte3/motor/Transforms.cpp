//
// Created by 87 Dolly on 28/03/2018.
//

#include "headers/Transforms.h"

Transforms::Transforms() {
    tipo = "";
    t = Transformacao();
    subgrupo = vector<Transforms>();
    pontos = vector<Ponto>();
}

Transforms::Transforms(string tipo, Transformacao t, vector<Transforms> sub, vector<Ponto> pontos) {
    this->tipo = tipo;
    this->t = t;
    this->subgrupo = sub;
    this->pontos = pontos;
}

