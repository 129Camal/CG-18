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
    Translacao translacao;
    Rotacao rotacao;
    Escala escala;
    Cor cor;


public:
    Transformacao();
    Transformacao(Translacao translacao, Rotacao rotacao, Escala escala, Cor cor);
    Translacao getTranslacao() { return translacao; }
    Rotacao getRotacao() { return rotacao; }
    Escala getEscala(){ return escala;}
    Cor getCor(){ return cor; }
    void setTransl(Translacao t){ translacao = t; }
    void setRotacao(Rotacao r){ rotacao = r; }
    void setEscala(Escala esc){ escala = esc; }
    void setCor(Cor c){ cor = c; }
    bool semTranformacao();
};

#endif