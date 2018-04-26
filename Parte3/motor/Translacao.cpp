//
// Created by 87 Dolly on 28/03/2018.
//

#include "headers/Translacao.h"
#include "../../Parte2/motor/headers/Ponto.h"

Translacao::Translacao(){
    x_eixo = 0.0;
    y_eixo = 0.0;
    z_eixo = 0.0;
    time = 0.0;
}

Translacao :: Translacao(float x, float y, float z, float t, int num, vector<Ponto>tr) {
    time = t;
    size = num;
    transl = tr;
}

void Translacao::getCatmullRomPoint(float t, int* pos, int* deriv, vector<Ponto> tr) {
    float aux[4];
    float quad, cubo;
    int i1, i2, i3, i4;
    Ponto p0, p1, p2, p3;

    quad = pow(t, 2);
    cubo = pow(t, 3);
    deriv[0] = deriv[1] = deriv[2] = 0;

    float m[4][4] = {{-0.5, 1.5,  -1.5, 0.5},
                     {1.0,  -2.5, 2,    -0.5},
                     {-0.5, 0,    0.5,  0},
                     {0,    1,    0,    0}};

    aux[0] = cubo * m[0][0] + quad * m[1][0] + t * m[2][0] + 1 * m[3][0];
    aux[1] = cubo * m[0][1] + quad * m[1][1] + t * m[1][2] + 1 * m[1][3];
    aux[2] = cubo * m[0][2] + quad * m[2][1] + t * m[2][2] + 1 * m[2][3];
    aux[3] = cubo * m[0][3] + quad * m[3][1] + t * m[3][2] + 1 * m[3][3];

    i1 = pos[0];
    i2 = pos[1];
    i3 = pos[2];
    i4 = pos[3];

    p0 = transl[i1];
    p1 = transl[i2];
    p2 = transl[i3];
    p3 = transl[i4];

    deriv[0] = aux[0] * p0.getX() + aux[1] * p1.getX() + aux[2] * p2.getX() + aux[3] * p3.getX();
    deriv[1] = aux[0] * p0.getY() + aux[1] * p1.getY() + aux[2] * p2.getY() + aux[3] * p3.getY();
    deriv[2] = aux[0] * p0.getZ() + aux[1] * p1.getZ() + aux[2] * p2.getZ() + aux[3] * p3.getZ();
}

void Translacao::getGlobalCatmullRomPoint(float gt, int* deriv, vector<Ponto> tr){
    float gtt;
    int size, i;
    int ind[4];

    size = tr.size();
    gtt = size * gt;
    i = floor(gtt); //arredonda
    gtt -= i;

    ind[0] = (i + size-1) % size;
    ind[1] = (ind[0] + size-1) %size;
    ind[2] = (ind[1] + size-1) %size;
    ind[3] = (ind[0] + size-1) %size;

    getCatmullRomPoint(gtt, ind, deriv, tr);
}

void Translacao::encurvar() {
    int res[3]; //todo: VERIFICAR SE É INT OU FLOAT
    float t;

    for (t = 0; t < 1; t += 0.01) {

        getGlobalCatmullRomPoint(t, res, transl);

        Ponto p = Ponto(res[0], res[1], res[2]);
        curvas.push_back(p);
    }
}

bool Translacao::semTranslacao() {
    return (time == 0.0 && transl.empty());
}