//
// Created by 87 Dolly on 28/03/2018.
//

#ifndef PROJECT_TRANSLACAO_H
#define PROJECT_TRANSLACAO_H

class Translacao{
    float x_eixo, y_eixo, z_eixo;

public:
    Translacao();
    Translacao(float x, float y, float z);
    float getX(){ return x_eixo; }
    float getY(){ return y_eixo; }
    float getZ(){ return z_eixo; }
    void setX(float x){ x_eixo = x;}
    void setY(float y){ y_eixo = y;}
    void setZ(float z){ z_eixo = z;}
};
#endif //PROJECT_TRANSLACAO_H
