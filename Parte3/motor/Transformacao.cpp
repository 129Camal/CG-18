//
// Created by 87 Dolly on 28/03/2018.
//

#include "headers/Transformacao.h"

Transformacao::Transformacao(){
    trans = Translacao();
    rotacao = Rotacao();
    escala = Escala();
    cor = Cor();
}
Transformacao::Transformacao(Translacao trans, Rotacao rotacao, Escala escala, Cor cor){
    this->trans = trans;
    this->rotacao = rotacao;
    this->escala = escala;
    this->cor = cor;
}

bool Transformacao::semTranformacao() {

    return (trans.semTranslacao() && rotacao.semRotacao() && escala.semEscala() && cor.semCor());
}
