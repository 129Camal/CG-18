//
// Created by 87 Dolly on 27/03/2018.
//
#include "headers/motor.h"


// esta merda tem que sair daqi depois e ir para o motor.h

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

using namespace std;
using namespace tinyxml2;

float zz = -4, angleX=0.0, angleY=0.0;
vector<Transforms> transformacoes;
vector<Ponto> pontos;

void renderScene(void){
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();

    //draw instructions
    glTranslatef(0, -1, zz);
    glRotatef(angleY, 0.0, 1.0, 0.0);
    glRotatef(angleX, 1.0, 0.0, 0.0);
    //translate????
    glBegin(GL_TRIANGLES);
    int i;
    for(i = 0; i < transformacoes.size(); i++) {
        glPushMatrix();
        Transformacao transform = transformacoes[i].getTrans();
        glRotatef(transform.getRotacao().getAngle(), transform.getRotacao().getX(), transform.getRotacao().getY(),
                  transform.getRotacao().getZ());
        glTranslatef(transform.getTrans().getX(), transform.getTrans().getY(), transform.getTrans().getZ());
        glScalef(transform.getEscala().getX(), transform.getEscala().getY(), transform.getEscala().getZ());

        for (int j = 0; j < pontos.size(); j++)
            glVertex3f(pontos[j].getX(), pontos[j].getY(), pontos[j].getZ());
    }
    glEnd();
    glPopMatrix();

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
void keyboardspecial(int key, int a, int b){}


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



Transformacao PerformTransf(Translacao trans, Escala es, Rotacao rot, Transformacao transf){


    Transformacao pt;

    trans.setX(trans.getX() + transf.getTrans().getX());
    trans.setY(trans.getY() + transf.getTrans().getY());
    trans.setZ(trans.getZ() +  transf.getTrans().getZ());
    es.setX(es.getX() * transf.getEscala().getX());
    es.setY(es.getY() * transf.getEscala().getY());
    es.setZ(es.getZ() * transf.getEscala().getZ());
    rot.setX(rot.getAngle() + transf.getRotacao().getAngle());
    rot.setY(rot.getX() + transf.getRotacao().getX());
    rot.setY(rot.getY() + transf.getRotacao().getY());
    rot.setZ(rot.getZ() + transf.getRotacao().getZ());


    pt = Transformacao(trans,rot,es);

    return pt;

}

//Parse do XML tendo em conta os níveis hierarquicos

void Parser(XMLElement *group , Transformacao transf){

    Transformacao trf;
    Translacao trl;
    Escala esc;
    Rotacao rot;

    float transX, transY, transZ, ang, esX, esY,esZ, rotX, rotY, rotZ;



    if(strcmp(group->FirstChildElement()->Value(),"group")==0){
        group = group->FirstChildElement();

    }

    XMLElement* transfor = group->FirstChildElement();

    for(transfor; (strcmp(transfor->Value(),"models")!=0); transfor = transfor->NextSiblingElement()){
        if(strcmp(transfor->Value(), "translate")==0){
            if(transfor->Attribute("X")) transX = stof(transfor->Attribute("X"));
            else transX = 0;
            if(transfor->Attribute("Y")) transY = stof(transfor->Attribute("Y"));
            else transY=0;
            if(transfor->Attribute("Z")) transZ = stof(transfor->Attribute("Z"));
            else transZ=0;
            trl = Translacao(transX,transY,transZ);

        }
        if(strcmp(transfor->Value(), "scale")==0){
            if(transfor->Attribute("X")) esX = stof(transfor->Attribute("X"));
            else esX=0;
            if(transfor->Attribute("Y")) esY = stof(transfor->Attribute("Y"));
            else esY=0;
            if(transfor->Attribute("Z")) esZ = stof(transfor->Attribute("Z"));
            else esZ=0;
            esc.setX(esX);
            esc.setY(esY);
            esc.setZ(esZ);
        }
        if(strcmp(transfor->Value(), "rotate")==0){
            if(transfor->Attribute("angle")) ang = stof(transfor->Attribute("angle"));
            else ang=0;
            if(transfor->Attribute("X")) rotX = stof(transfor->Attribute("X"));
            else rotX =0;
            if(transfor->Attribute("Y")) rotY = stof(transfor->Attribute("Y"));
            else rotY=0;
            if(transfor->Attribute("Z")) rotZ = stof(transfor->Attribute("Z"));
            else rotZ=0;
            rot =Rotacao(ang,rotX,rotY,rotZ);
        }
    }

    trf= PerformTransf(trl,esc,rot,transf);

    for(XMLElement* models = group->FirstChildElement("models")->FirstChildElement("model"); models; models = models -> NextSiblingElement("modelo")){
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