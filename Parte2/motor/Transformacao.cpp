//
// Created by 87 Dolly on 28/03/2018.
//

#include "headers/Transformacao.h"

Transformacao::Transformacao(){
    trans = Translacao::Translacao();
    rotacao = Rotacao::Rotacao();
    escala = Escala::Escala();
}
Transformacao::Transformacao(Translacao trans, Rotacao rotacao, Escala escala){
    trans = trans;
    rotacao = rotacao;
    escala = escala;
}
