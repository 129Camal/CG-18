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
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    float* v = (float*) malloc(sizeof(float) * pontos.size()*3);
    float* n = (float*) malloc(sizeof(float) * normal.size()*3);
    float* text = (float*) malloc(sizeof(float) * textura.size()*3);

    for(i=0; i < pontos.size(); i++) {
        v[pos] = pontos[i].getX();
        v[pos + 1] = pontos[i].getY();
        v[pos + 2] = pontos[i].getZ();
        pos += 3;
    }

    for(i=0; i < normal.size(); i++){
        n[pos] = normal[i].getX();
        n[pos+1] = normal[i].getY();
        n[pos+2] = normal[i].getZ();
        pos+=3;
    }

    for(i=0; i < textura.size(); i++){
        text[pos] = textura[i].getX();
        text[pos+1]  = textura[i].getY();
        text[pos+2] = textura[i].getZ();
        pos+=3;
    }

    glGenBuffers(3,buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * pontos.size() * 3, v, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,buffer[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normal.size() * 3, n, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * pontos.size() * 3, text, GL_STATIC_DRAW);

    free(v);
    free(n);
    free(text);
    }

void Transforms::draw() {
    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glVertexPointer(3 , GL_FLOAT, 0 , 0);
    glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
    glVertexPointer(3 , GL_FLOAT, 0 , 0);
    glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
    glTexCoordPointer(2 , GL_FLOAT, 0 , 0); // 2 porque é o numero de coordenadas das texturas
    glDrawArrays(GL_TRIANGLES,0, pos);
}

void Transforms::newText() {
    string path = "../texturas" + text;
    ilGenImages(1, &tt);
    ilBindImage(tt);
    ilLoadImage((ILstring)path.c_str());
    width = ilGetInteger(IL_IMAGE_WIDTH);
    height = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    data = ilGetData();
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}


