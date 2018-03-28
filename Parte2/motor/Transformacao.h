//
// Created by 87 Dolly on 28/03/2018.
//

#ifndef PROJECT_TRANSFORMACAO_H
#define PROJECT_TRANSFORMACAO_H


class Transformacao {
    float x_eixo;
    float y_eixo; // variáveis comuns
    float z_eixo;


public:
    Transformacao();
    Transformacao(float x_eixo, float y_eixo, float z_eixo);
    float get_X(){ return x_eixo; }
    float get_Y(){ return y_eixo; }
    float get_Z(){ return z_eixo; }
    void set_X(float x){ x_eixo = x; }
    void set_Y(float y){ y_eixo = y; }
    void set_Z(float z){ z_eixo = z; }
};
#endif //PROJECT_TRANSFORMACAO_H
