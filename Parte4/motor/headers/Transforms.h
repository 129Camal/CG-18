//
// Created by 87 Dolly on 28/03/2018.
//
#include <vector>
#include "Transformacao.h"
#include "Ponto.h"
#include <fstream>
#include <iostream>
#include <string>

#ifdef __APPLE__
#include <IL/il.h>
#include <GL/glut.h>
#else
#include <IL/il.h>
#include <GL/glew.h>
#include <GL/glut.h>
#endif



using namespace std;
#ifndef PROJECT_TRANSFORMS_H
#define PROJECT_TRANSFORMS_H


class Transforms{
    string text; //nome da imagem que se vai buscar ao XML
    string tipo;
    Transformacao t;
    vector<Ponto> pontos;
    GLuint buffer[3];
    int pos;
    vector<Transforms> subgrupo;
    vector<Ponto> normal;
    vector<Ponto> textura;

    //Textura:
    unsigned int tt, width, height;
    unsigned int texID;
    unsigned char *data;

public:
    Transforms();
    Transforms(string tipo, Transformacao t, vector<Transforms> sub, vector<Ponto> pontos);
    string getTipo(){ return tipo; }
    Transformacao getTransformacao(){ return t; }
    vector<Transforms> getSubgrupo(){ return subgrupo; }
    vector<Ponto> getPontos(){ return pontos; }
    void setTipo(string t){ tipo = t; }
    void setTrans(Transformacao trans){ t = trans;}
    void setSubgrupo(vector<Transforms> sub){ subgrupo = sub; }
    void setPontos(vector<Ponto> p){ pontos = p;}
    void toVertex();
    void setVBO();
    void draw();
    void push_child(Transforms t){subgrupo.push_back(t);}
    void newText();
};


#endif //PROJECT_TRANSFORMS_H