//
// Created by 87 Dolly on 28/03/2018.
//
#include "Translacao.h"
#include "Rotacao.h"
#include "Escala.h"
#include "Cor.h"
#ifndef PROJECT_TRANSFORMACAO_H
#define PROJECT_TRANSFORMACAO_H


class Transformacao {
    Translacao trans;
    Rotacao rotacao;
    Escala escala;
    Cor cor;


public:
    Transformacao();
    Transformacao(Translacao trans, Rotacao rotacao, Escala escala, Cor cor);
    Translacao getTrans() { return trans; }
    Rotacao getRotacao() { return rotacao; }
    Escala getEscala(){ return escala;}
    Cor getCor(){ return cor; }
    void setTrans(Translacao t){ trans = t; }
    void setRotacao(Rotacao r){ rotacao = r; }
    void setEscala(Escala esc){ escala = esc; }
    void setCor(Cor c){ cor = c; }
};

#endif