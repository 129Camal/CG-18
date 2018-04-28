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
    int window;

    float angleX = 0.0, angleY = 0.0, angleZ = 0.0;
    float cX = 0.0, cY = 0.0, cZ = 0.0;
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
    float getAngleX(){ return angleX;}
    float getAngleY(){ return angleY;}
    float getAngleZ(){ return angleZ;}
    float getCX(){ return cX;}
    float getCY(){ return cY;}
    float getCZ(){ return cZ;}
    void setLX(float lx){ lX = lx;}
    void setLY(float ly){ lY = ly;}
    void setLZ(float lz){ lZ = lz;}
    void setLLX(float llx){ llX = llx;}
    void setLLY(float lly){ llY = lly;}
    void setLLZ(float llz){ llZ = llz;}
    void setSpeed(float s){ speed = s;}
    void setRotSpeed(float rspeed){ rotSpeed = speed;}
    void setWindow(int w){ window = w;}
    void setAngleX(float ax){ angleX = ax;}
    void setAngleY(float ay){ angleY = ay;}
    void setAngleZ(float az){ angleZ = az;}
    void setCX(float cx){ cX = cx;}
    void setCY(float cy){ cY = cy;}
    void setCZ(float cz){ cZ = cz;}
    void displayFPS();
    void keyboard(unsigned char key, int a, int b);
    void specialKeys(int key);
    void mouseMove(int x, int y);
};