//
// Created by 87 Dolly on 28/03/2018.
//


#include "headers/Transforms.h"

Transforms::Transforms() {
    tipo = "";
    t = Transformacao();
    subgrupo = vector<Transforms>();
    pontos = vector<Ponto>();
    pos = 0;
}

Transforms::Transforms(string tipo, Transformacao t, vector<Transforms> sub, vector<Ponto> pontos) {
    this->tipo = tipo;
    this->t = t;
    this->subgrupo = sub;
    this->pontos = pontos;
}

void Transforms::toVertex() {
    int i;

    glBegin(GL_TRIANGLES);
    for(i=0; i < pontos.size(); i++){
        glVertex3f(pontos.at(i).getX(), pontos.at(i).getY(), pontos.at(i).getZ());
    }
    glEnd();
}

void Transforms::setVBO() {
    int i;

    glEnableClientState(GL_VERTEX_ARRAY);

    float* v = (float*) malloc(sizeof(float)*pontos.size()*3);

    for(i=0; i < pontos.size(); i++) {
        v[pos] = pontos.at(i).getX();
        v[pos + 1] = pontos.at(i).getY();
        v[pos + 2] = pontos.at(i).getZ();
        pos += 3;
    }

    glGenBuffers(1,buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * pos, v, GL_STATIC_DRAW);
    free(v);
    }

void Transforms::draw() {
    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glVertexPointer(3 , GL_FLOAT, 0 , 0);
    glDrawArrays(GL_TRIANGLES,0, pos);
}


