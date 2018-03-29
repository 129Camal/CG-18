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
    trans = trans;
    rotacao = rotacao;
    escala = escala;
    cor = cor;
}
