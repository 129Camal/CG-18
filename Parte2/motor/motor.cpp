//
// Created by 87 Dolly on 27/03/2018.
//
#include <zconf.h>
#include "headers/motor.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

using namespace std;
using namespace tinyxml2;

float xx = 0, yy = 0, zz = -4, angleX=0.0, angleY=0.0, lx = 6.0, ly = 6.0, lz = 6.0;
vector<Transforms> transformacoes;
vector<Ponto> pontos;

void renderScene(void){
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(lx+150,ly+150,lz+150, //todo: alterar aqui
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);
    //glTranslatef(0, -1, zz);

    //draw instructions
    glRotatef(angleY, 0.0, 1.0, 0.0);
    glRotatef(angleX, 1.0, 0.0, 0.0);
    glTranslatef(-xx,0,-yy);

    glBegin(GL_TRIANGLES);
    int i;
    for(i = 0; i < transformacoes.size(); i++) {
        glPushMatrix();
        Transformacao transform = transformacoes[i].getTrans();
        glRotatef(transform.getRotacao().getAngle(), transform.getRotacao().getX(), transform.getRotacao().getY(),
                  transform.getRotacao().getZ());
        glTranslatef(transform.getTrans().getX(), transform.getTrans().getY(), transform.getTrans().getZ());
        glScalef(transform.getEscala().getX(), transform.getEscala().getY(), transform.getEscala().getZ());

        pontos.clear();
        pontos = transformacoes[i].getPontos();

        glBegin(GL_TRIANGLES);
        glColor3f(1.0,1.0,1.0);
        for (int j = 0; j < pontos.size(); j++)
            glVertex3f(pontos[j].getX(), pontos[j].getY(), pontos[j].getZ());

        glEnd();
        glPopMatrix();
    }
    glEnd();
    glColor3f(1.0,0.0,1.0);
    glPushMatrix();
    glutWireCube(2);
    glPopMatrix();

    glutSwapBuffers();
    //se fizermos o anel de saturno fica aqui
}

void reshape(int w, int h){
    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;
    float ratio = w *1.0 / h;
    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}
void keyboard(unsigned char key, int a, int b){}
void keyboardspecial(int key, int a, int b){
    switch(key) {
        case '-':
            gluLookAt(lx += 2, ly += 2, lz += 2, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);
            break;

        case '+':
            gluLookAt(lx -= 2, ly -= 2, lz -= 2, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);
            break;
    }
}


//método para ler o ficheiro e preencher vetor

void readFile(string fich){
    string linha;
    string novo;
    string delimiter = ",";
    int pos;
    float xx,yy,zz;
    Ponto p ;

    ifstream file(fich);

    if(file.is_open()){

        while(getline (file,linha)) {

            pos = linha.find(delimiter);
            novo = linha.substr(0, pos);
            xx = atof(novo.c_str());
            linha.erase(0, pos + delimiter.length());
            p.setX(xx);

            pos = linha.find(delimiter);
            novo = linha.substr(0, pos);
            yy = atof(novo.c_str());
            linha.erase(0, pos + delimiter.length());
            p.setY(yy);

            pos = linha.find(delimiter);
            novo = linha.substr(0, pos);
            zz = atof(novo.c_str());
            linha.erase(0, pos + delimiter.length());
            p.setZ(zz);

            pontos.push_back(p);

        }

        file.close();


    }
    else {

        cout << "ERRO AO LER FICHEIRO" << endl;
    }
}



Transformacao PerformTransf(Translacao trans, Escala es, Rotacao rot, Cor cor, Transformacao transf){

    Transformacao pt;

    trans.setX(trans.getX() + transf.getTrans().getX());
    trans.setY(trans.getY() + transf.getTrans().getY());
    trans.setZ(trans.getZ() +  transf.getTrans().getZ());
    es.setX(es.getX() * transf.getEscala().getX());
    es.setY(es.getY() * transf.getEscala().getY());
    es.setZ(es.getZ() * transf.getEscala().getZ());
    rot.setAngle(rot.getAngle() + transf.getRotacao().getAngle());
    rot.setX(rot.getX() + transf.getRotacao().getX());
    rot.setY(rot.getY() + transf.getRotacao().getY());
    rot.setZ(rot.getZ() + transf.getRotacao().getZ());
    cor.setR(rot.getX() + transf.getCor().getR());
    cor.setG(rot.getY() + transf.getCor().getG());
    cor.setB(rot.getZ() + transf.getCor().getB());

    pt = Transformacao(trans,rot,es,cor);

    return pt;

}

//Parse do XML tendo em conta os níveis hierarquicos

void Parser(XMLElement *group , Transformacao transf){

    Transformacao trf;
    Translacao trl;
    Escala esc;
    Rotacao rot;
    Cor cor;

    float transX = 0.0, transY = 0.0, transZ = 0.0, ang = 0.0, esX = 0.0, esY=0.0,esZ=0.0, rotX=0.0, rotY=0.0, rotZ=0.0;



    if(strcmp(group->FirstChildElement()->Value(),"group")==0){
        group = group->FirstChildElement();

    }

    XMLElement* transfor = group->FirstChildElement();
    XMLAttribute* at;
    XMLAttribute* as;
    XMLAttribute* ar;
    for(transfor; (strcmp(transfor->Value(),"models")!=0); transfor = transfor->NextSiblingElement()){
        if(strcmp(transfor->Value(), "translate")==0) {

           at = const_cast<XMLAttribute *>(transfor->FirstAttribute());
            if(strcmp(at->Name(),"X")==0) transX = stof(transfor->Attribute("X"));
            else transX = 0;
            if(strcmp(at->Name(),"Y")==0) transY = stof(transfor->Attribute("Y"));
            else transY=0;
            if(strcmp(at->Name(),"Z")==0) transZ = stof(transfor->Attribute("Z"));
            else transZ=0;
            trl = Translacao(transX,transY,transZ);

        }
        if(strcmp(transfor->Value(), "scale")==0){

            as = const_cast<XMLAttribute *>(transfor->FirstAttribute());
            esX = stof(transfor->Attribute("X"));
            esY = stof(transfor->Attribute("Y"));
            esZ = stof(transfor->Attribute("Z"));

            esc.setX(esX);
            esc.setY(esY);
            esc.setZ(esZ);
        }
        if(strcmp(transfor->Value(), "rotate")==0){

            ar = const_cast<XMLAttribute *>(transfor->FirstAttribute());
            ang = stof(transfor->Attribute("angle"));

            rotX = stof(transfor->Attribute("X"));

            rotY = stof(transfor->Attribute("Y"));

            rotZ = stof(transfor->Attribute("Z"));
            rot =Rotacao(ang,rotX,rotY,rotZ);
        }
    }

    trf= PerformTransf(trl,esc,rot,cor,transf);

    for(XMLElement* models = group->FirstChildElement("models")->FirstChildElement("model"); models; models = models -> NextSiblingElement("model")){
        Transforms tran;

        tran.setTipo(models->Attribute("fich"));
        cout << tran.getTipo() << endl;
        readFile(tran.getTipo());
        tran.setPontos(pontos);
        pontos.clear();
        tran.setTrans(trf);

        cout << "Translacao ->" << trf.getTrans().getX() << "-" << trf.getTrans().getY() << "-" << trf.getTrans().getZ() << endl;
        cout << "Escala ->" << trf.getEscala().getX() << "-" << trf.getEscala().getY() << "-" << trf.getEscala().getZ() << endl;
        cout << "Rotacao -> " << trf.getRotacao().getAngle() << "-" << trf.getRotacao().getX() << "-" << trf.getRotacao().getY() << "-" << trf.getRotacao().getZ() << endl;

        transformacoes.push_back(tran);
    }
        // faz parse dos filhos
    if(group->FirstChildElement("group")){
            Parser(group->FirstChildElement("group"),trf);
    }

        //faz parse nos irmãos
    if(group->NextSiblingElement("group")){
        Parser(group->NextSiblingElement("group"),transf);

    }

}


//método para ler ficheiro xml

void lerXML(string fich) {
    XMLDocument doc;

    if (!(doc.LoadFile(fich.c_str()))) {

            XMLElement * scene = doc.FirstChildElement("scene");
            XMLElement * group = scene-> FirstChildElement("group");

            Transformacao t = Transformacao();
            Escala esc = Escala(0.5,0.5,0.5);
            t.setEscala(esc);
            Parser(group,t);
        }else {
        cout << "Ficheiro XML não foi encontrado" << endl;
    }
}



int main(int argc, char** argv){

    if (argc > 1){
        lerXML(argv[1]);
    }

//init glut and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("CG_Project");

// put callback registration here
    glutDisplayFunc( renderScene );
    glutReshapeFunc( reshape );
    glutIdleFunc( renderScene);
    glutSpecialFunc(keyboardspecial);
    glutKeyboardFunc(keyboard);
// OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

// enter GLUT's main loop
    glutMainLoop();

    return 1;

}
#pragma clang diagnostic pop