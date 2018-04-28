//
// Created by 87 Dolly on 28/04/2018.
//
#include "Camara.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
Camara::Camara() {
    rotY = 0.0;
    rotX = 0.0;
    lX = 20.0;
    lY = 50.0;
    lZ = -40.0;
    llX = 0.0;
    llY = 0.0;
    llZ = 0.0;
    speed = 0.5;
    rotSpeed = 0.00175;
}

void Camara::displayFPS(){
    int time;
    char title[20];

    frame++;
    time = glutGet(GLUT_ELAPSED_TIME);
    if (time - timebase > 1000) {
        float fps = frame * 1000.0/(time - timebase);
        timebase = time;
        frame = 0;
        sprintf(title,"Engine  |  %.2f FPS",fps);
        glutSetWindowTitle(title);
    }
}
void Camara::camaraMove(){
    if(cima){
        lX += llX * speed;
        lY += llY * speed;
        lZ += llZ * speed;
    }

    if(baixo){
        lX -= llX * speed;
        lY -= llY * speed;
        lZ -= llZ * speed;
    }

    if(esq){
        lX += llZ * 2*speed;
        lZ -= llX * 2* speed;
    }

    if(dir){
        lX -= llZ * speed;
        lZ += llX * speed;
    }
}
void Camara::pressKeys(unsigned char key, int x, int y){


    switch(key){

        case 'a':
        case 'A':
            esq = true;
            break;

        case 'd':
        case 'D':
            dir = true;
            break;

        case 'w':
        case 'W':
            cima = true;
            break;

        case 's':
        case 'S':
            baixo = true;
            break;

    }
}

void Camara::releaseKeys(unsigned char key, int x, int y){


    switch(key){

        case 'a':
        case 'A':
            esq = false;
            break;

        case 'd':
        case 'D':
            dir = false;
            break;

        case 'w':
        case 'W':
            cima = false;
            break;

        case 's':
        case 'S':
            baixo = false;
            break;

    }
}


bool warping = false;
bool mouseCaptured = true;
void Camara::mouseMove(int x, int y){
    if(warping){
        warping = false;
        return;
    }

    int dx = x -300;
    int dy = y - 300;

    rotX += dx*rotSpeed;
    rotY += dy*rotSpeed;
    llX=sin(rotY)*sin(rotX);
    llY=-cos(rotY);
    llZ=-sin(rotY)*cos(rotX);

    if(mouseCaptured){
        warping = true;
        glutWarpPointer(300,300);
    }
}
#pragma clang diagnostic pop