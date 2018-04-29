//
// Created by 87 Dolly on 28/03/2018.
//

#include <iostream>
#include "headers/Translacao.h"
#include "../../Parte2/motor/headers/Ponto.h"

Translacao::Translacao(){
    x_eixo = 0.0;
    y_eixo = 0.0;
    z_eixo = 0.0;
    time = 0.0;
    cima[0] = 0.0;
    cima[1] = 1.0;
    cima[2] = 0.0;
}

Translacao :: Translacao(float x, float y, float z, float t, int num, vector<Ponto>tr) {
    x_eixo = x;
    y_eixo = y;
    z_eixo = z;
    time = t;
    size = num;
    transl = tr;
}

void Translacao::getCatmullRomPoint(float t, int* pos, float* deriv, float* res, vector<Ponto> tr) {
    float auxR[4], auxD[4];
    float quad, cubo;
    int i1, i2, i3, i4;
    Ponto p0, p1, p2, p3;

    quad = t*t;
    cubo = t*t*t;
    res[0] = res[1] = res[2] = 0;

    float m[4][4] = {{-0.5f, 1.5f,  -1.5f, 0.5f},
                     {1.0f,  -2.5f, 2.0f,    -0.5f},
                     {-0.5f, 0.0f,    0.5f,  0.0f},
                     {0.0f,    1.0f,    0.0f,    0.0f}};

    auxR[0] = cubo * m[0][0] + quad * m[1][0] + t * m[2][0] + 1 * m[3][0];
    auxR[1] = cubo * m[0][1] + quad * m[1][1] + t * m[2][1] + 1 * m[3][1];
    auxR[2] = cubo * m[0][2] + quad * m[1][2] + t * m[2][2] + 1 * m[3][2];
    auxR[3] = cubo * m[0][3] + quad * m[1][3] + t * m[2][3] + 1 * m[3][3];

    auxD[0] = 3*quad*m[0][0] + 2*t*m[1][0] + m[2][0];
    auxD[1] = 3*quad*m[0][1] + 2*t*m[1][1] + m[2][1];
    auxD[2] = 3*quad*m[0][2] + 2*t*m[1][2] + m[2][2];
    auxD[3] = 3*quad*m[0][3] + 2*t*m[1][3] + m[2][3];


    i1 = pos[0];
    i2 = pos[1];
    i3 = pos[2];
    i4 = pos[3];

    p0 = transl[i1];
    p1 = transl[i2];
    p2 = transl[i3];
    p3 = transl[i4];

    res[0] = auxR[0] * p0.getX() + auxR[1] * p1.getX() + auxR[2] * p2.getX() + auxR[3] * p3.getX();
    res[1] = auxR[0] * p0.getY() + auxR[1] * p1.getY() + auxR[2] * p2.getY() + auxR[3] * p3.getY();
    res[2] = auxR[0] * p0.getZ() + auxR[1] * p1.getZ() + auxR[2] * p2.getZ() + auxR[3] * p3.getZ();

    deriv[0] = auxD[0] * p0.getX() + auxD[1]*p1.getX() + auxD[2]*p2.getX() + auxD[3]*p3.getX();
    deriv[1] = auxD[0] * p0.getY() + auxD[1]*p1.getY() + auxD[2]*p2.getY() + auxD[3]*p3.getY();
    deriv[2] = auxD[0] * p0.getZ() + auxD[1]*p1.getZ() + auxD[2]*p2.getZ() + auxD[3]*p3.getZ();

}

void Translacao::getGlobalCatmullRomPoint(float gt, float* deriv, float* res, vector<Ponto> tr){
    float gtt;
    int size, i;
    int ind[4];

    size = tr.size();
    gtt = size * gt;
    i = floor(gtt); //arredonda
    gtt = gtt - i;

    ind[0] = (i + size-1) % size;
    ind[1] = (ind[0] + 1) %size;
    ind[2] = (ind[1] + 1) %size;
    ind[3] = (ind[0] + 1) %size;

    getCatmullRomPoint(gtt, ind, deriv, res, tr);
}

void Translacao::renderCatmullRomCurve( vector<Ponto> pontos, float r, float g, float b) {
    int x = (int) pontos.size();
    float npts[3];
    int i;

    glBegin(GL_LINE_LOOP);

    for(i=0; i < x ; i ++) {
        npts[0] = pontos.at(i).getX();
        npts[1] = pontos.at(i).getY();
        npts[2] = pontos.at(i).getZ();
        glColor3f(r,g,b);
        glVertex3fv(npts);
    }

    glEnd();
}

vector<Ponto> Translacao::encurvar() {
    float res[3];
    float deriv[3];
    float t;

    for (t = 0; t < 1; t += 0.01) {

        getGlobalCatmullRomPoint(t, deriv, res, transl);
        Ponto p = Ponto(res[0], res[1], res[2]);
        curvas.push_back(p);
    }
    return curvas;
}

bool Translacao::semTranslacao() {
    return (time == 0.0 && transl.empty());
}