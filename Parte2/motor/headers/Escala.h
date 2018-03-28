//
// Created by 87 Dolly on 28/03/2018.
//

#ifndef PROJECT_ESCALA_H
#define PROJECT_ESCALA_H

class Escala{
    float x_eixo, y_eixo, z_eixo;

public:
    Escala();
    Escala(float x, float y, float z){
        x_eixo = x;
        y_eixo = y;
        z_eixo = z;
    }
    float getX(){ return x_eixo; }
    float getY(){ return y_eixo; }
    float getZ(){ return z_eixo; }
    void setX(float x){ x_eixo = x;}
    void setY(float y){ y_eixo = y;}
    void setZ(float z){ z_eixo = z;}
};
#endif //PROJECT_ESCALA_H
