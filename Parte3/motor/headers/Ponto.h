//
// Created by filipe on 29-03-2018.
//

#ifndef PROJECT_PONTO_H
#define PROJECT_PONTO_H


class Ponto {

    float x;
    float y;
    float z;

public:
    Ponto();
    Ponto(float, float, float);
    float getX() { return x; }
    float getY() { return y; }
    float getZ() { return z; }
    void setX( float a) {  x = a; }
    void setY( float a) {  y = a; }
    void setZ( float a) {  z = a; }


};


#endif //PROJECT_PONTO_H
