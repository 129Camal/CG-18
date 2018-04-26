//
// Created by 87 Dolly on 28/03/2018.
//
#include <vector>
#include <stdlib.h>
#include <math.h>
#include "ponto.h"

using namespace std;

#ifndef PROJECT_TRANSLACAO_H
#define PROJECT_TRANSLACAO_H

class Translacao{
    float x_eixo;
    float y_eixo;
    float z_eixo;

    float time;
    int size;
    vector<Ponto> transl;
    vector<Ponto> curvas;

public:
    Translacao();
    Translacao(float x, float y, float z, float ti, int s, vector<Ponto> t);
    float getX(){ return x_eixo; }
    float getY(){ return y_eixo; }
    float getZ(){ return z_eixo; }
    float getTime(){ return time; }
    int getSize(){ return size; }
    vector<Ponto> getTransl(){ return transl; }
    vector<Ponto> getCurvas(){ return curvas; }
    void setX(float x){ x_eixo = x;}
    void setY(float y){ y_eixo = y;}
    void setZ(float z){ z_eixo = z;}
    void setTime(float x){ time = x;}
    void setSize(float y){ size = y;}
    void setTransl(vector<Ponto> t){ transl = t;}
    void setTransl(vector<Ponto> c){ transl = c;}
    void getCatmullRomPoint(float t, int* pos, int* deriv, vector<Ponto> tr);
    void getGlobalCatmullRomPoint(float t, int* deriv, vector<Ponto> tr);
    void encurvar();
    bool semTranslacao();
};
#endif //PROJECT_TRANSLACAO_H
