//
// Created by 87 Dolly on 29/03/2018.
//

#ifndef PROJECT_COR_H
#define PROJECT_COR_H

class Cor{
    float red;
    float green;
    float blue;

public:
    Cor();
    Cor(float r, float g, float b);
    float getR(){ return red; }
    float getG(){ return green; }
    float getB(){ return blue; }
    void setR(float r){ red = r; }
    void setG(float g){ green = g; }
    void setB(float b){ blue = b; }
    bool semCor();
};
#endif //PROJECT_COR_H
