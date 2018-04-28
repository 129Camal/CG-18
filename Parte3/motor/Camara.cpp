//
// Created by 87 Dolly on 28/04/2018.
//
#include "Camara.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
Camara::Camara() {
    rotY = 0.0;
    rotX = 0.0;
    lX = 30.0;
    lY = 0.0;
    lZ = 15.0;
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

void Camara::specialKeys(int key){

    switch (key) {
        case GLUT_KEY_UP:
            lX += llX * speed;
            lY += llY * speed;
            lZ += llZ * speed;
            break;

        case GLUT_KEY_DOWN:
            lX -= llX * speed;
            lY -= llY * speed;
            lZ -= llZ * speed;
            break;

        case GLUT_KEY_LEFT:
            lX += llZ * speed;
            lZ -= llX * speed;
            break;

        case GLUT_KEY_RIGHT:
            lX -= llZ * speed;
            lZ += llX * speed;
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

    int dx = x -100;
    int dy = y - 100;

    rotX += dx*rotSpeed;
    rotY += dy*rotSpeed;
    llX=sin(rotY)*sin(rotX);
    llY=-cos(rotY);
    llZ=-sin(rotY)*cos(rotX);

    if(mouseCaptured){
        warping = true;
        glutWarpPointer(100,100);
    }
}
#pragma clang diagnostic pop