//
// Created by 87 Dolly on 28/03/2018.
//

#ifndef PROJECT_ROTACAO_H
#define PROJECT_ROTACAO_H


class Rotacao {
    float angle, x_eixo, y_eixo, z_eixo;

public:
    Rotacao();
    Rotacao(float angle, float x, float y, float z){
        x_eixo = x;
        y_eixo = y;
        z_eixo = z;
    }
    float getAngle(){ return angle;}
    float getX(){ return x_eixo; }
    float getY(){ return y_eixo; }
    float getZ(){ return z_eixo; }
    void setAngle(float a){ angle = a; }
    void setX(float x){ x_eixo = x;}
    void setY(float y){ y_eixo = y;}
    void setZ(float z){ z_eixo = z;}
};


#endif //PROJECT_ROTACAO_H
