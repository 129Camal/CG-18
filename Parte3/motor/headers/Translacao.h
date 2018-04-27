//
// Created by 87 Dolly on 28/03/2018.
//
#include <vector>
#include <stdlib.h>
#include <math.h>
#include "Ponto.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


using namespace std;

#ifndef PROJECT_TRANSLACAO_H
#define PROJECT_TRANSLACAO_H

class Translacao{
    float x_eixo;
    float y_eixo;
    float z_eixo;

    float time;
    int size;
    float cima[3];
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
    float* getCima(){ return cima;}
    vector<Ponto> getTransl(){ return transl; }
    vector<Ponto> getCurvas(){ return curvas; }
    void setX(float x){ x_eixo = x;}
    void setY(float y){ y_eixo = y;}
    void setZ(float z){ z_eixo = z;}
    void setTime(float x){ time = x;}
    void setSize(float y){ size = y;}
    void setTransl(vector<Ponto> t){ transl = t;}
    void setCurvas(vector<Ponto> c){ curvas = c;}
    void getCatmullRomPoint(float t, int* pos, float* deriv, float* res, vector<Ponto> tr);
    void getGlobalCatmullRomPoint(float t, float* deriv, float* res, vector<Ponto> tr);
    void renderCatmullRomCurve( vector<Ponto> pontos, float r, float g, float b);
    void normaliza(float* f);
    void cruz(float* f, float* f2, float* res);
    void rodaCurva(float* deriv, float* cima);
    vector<Ponto> encurvar();
    bool semTranslacao();
};
#endif //PROJECT_TRANSLACAO_H
