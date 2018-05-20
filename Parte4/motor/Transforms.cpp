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
    int p = 0;
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    v = (float*) malloc(sizeof(float) * pontos.size()*3);
    n = (float*) malloc(sizeof(float) * normal.size()*3);
    textu = (float*) malloc(sizeof(float) * textura.size()*2);

    for(i=0; i < pontos.size(); i++) {
        v[p] = pontos[i].getX();
        v[p + 1] = pontos[i].getY();
        v[p + 2] = pontos[i].getZ();
        p += 3;
    }

    p = 0;

    for(i=0; i < normal.size(); i++){
        n[p] = normal[i].getX();
        n[p+1] = normal[i].getY();
        n[p+2] = normal[i].getZ();
        p+=3;
    }

    p = 0;
    for(i=0; i < textura.size(); i++){
        textu[p] = textura[i].getX();
        textu[p+1]  = textura[i].getY();
        p+=2;
    }

    p_tam = pontos.size() * 3;
    n_tam = normal.size() * 3;
    tex_tam = textura.size() * 2;

    glGenBuffers(3,buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * p_tam, v, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,buffer[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * n_tam, n, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * tex_tam, textu, GL_STATIC_DRAW);

    free(v);
    free(n);
    free(textu);
    newText();
    }

void Transforms::draw() {
    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glVertexPointer(3 , GL_FLOAT, 0 , 0);
    if(normal.size() != 0){
        glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
        glNormalPointer(GL_FLOAT, 0 , 0);
    }
    if(textura.size() != 0){
        glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
        glTexCoordPointer(2 , GL_FLOAT, 0 , 0); // 2 porque é o numero de coordenadas das texturas
    }
    glDrawArrays(GL_TRIANGLES,0, p_tam);
}

void Transforms::newText() {
    string path = "../../Parte4/texturas/" + text;
    ilGenImages(1, &tt);
    ilBindImage(tt);
    ilLoadImage((ILstring) path.c_str());
    width =  (unsigned int) ilGetInteger(IL_IMAGE_WIDTH);
    height = (unsigned int) ilGetInteger(IL_IMAGE_HEIGHT);
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


