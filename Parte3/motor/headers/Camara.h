//
// Created by 87 Dolly on 28/04/2018.
//

#ifndef PROJECT_CAMARA_H
#define PROJECT_CAMARA_H

#endif //PROJECT_CAMARA_H
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <math.h>

class Camara{
    float rotY, rotX; //angulo de rotaçao da camara
    float lX, lY, lZ; //posição da camara
    float llX, llY, llZ; // direção da camara
    float speed, rotSpeed;
    int frame = 0;
    int timebase = 0;

    bool cima = false, baixo = false, esq = false, dir = false; // camaraMove
public:
    Camara();
    //Camara();
    float getRotY(){ return rotY;}
    float getRotX(){ return rotX;}
    float getLX(){ return lX;}
    float getLY(){ return lY;}
    float getLZ(){ return lZ;}
    float getLLX(){ return llX;}
    float getLLY(){ return llY;}
    float getLLZ(){ return llZ;}
    float getSpeed(){ return speed;}
    float getRotSpeed(){ return rotSpeed;}
    void setLX(float lx){ lX = lx;}
    void setLY(float ly){ lY = ly;}
    void setLZ(float lz){ lZ = lz;}
    void setLLX(float llx){ llX = llx;}
    void setLLY(float lly){ llY = lly;}
    void setLLZ(float llz){ llZ = llz;}
    void setSpeed(float s){ speed = s;}
    void setRotSpeed(float rspeed){ rotSpeed = speed;}

    void displayFPS();
    void mouseMove(int x, int y);
    void camaraMove();
    void pressKeys(unsigned char key, int x, int y);
    void releaseKeys(unsigned char key, int x, int y);
};