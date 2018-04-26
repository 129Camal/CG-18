//
// Created by 87 Dolly on 27/03/2018.
//

#include "headers/motor.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

using namespace std;
using namespace tinyxml2;

float xx = 0, yy = 0, zz = -4, lxx = 0.0, lyy = 0.0, lzz = 0.0, angleX=0.0, angleY=0.0, angleZ = 0.0, lx = 30.0, ly = 30.0, lz = 30.0;

int draw = GL_LINE;
int window;
vector<Transforms> transformacoes;
vector<Ponto> pontos;

void drawAxis(){

    // Draw mode of Axis's Arrow Heads (FILLED)
    glPolygonMode(GL_FRONT_AND_BACK,draw);

    // Arrow Head of X Axis (RED)
    glRotatef(90.f,0,1,0); // Rotation of 90º Degrees, relative to the Y Axis... Now our Z axis, assumes the initial position of the X axis.
    glTranslatef(0,0,5+xx); // Translation of "5+axes_x", relative to the Z Axis
    glColor3f(1.0f,0.0f,0.0f); // Color of our X Arrow Head
    glutSolidCone(0.1,0.3,5,5); // Arrow Head is drawn, as a solid cone. Base on Z=0, Height on Z=0.3, Radius of 0.3 {5 slices and 5 stacks}.
    // This cone stays in the previously  translated position. In this case "5+axes_x"
    glTranslatef(0,0,-5-xx); // Translates to the initial position - origin
    glRotatef(-90.f,0,1,0); // Rotates to the initial position - origin

    // Arrow Head of Y Axis (GREEN)
    glRotatef(-90.f,1,0,0); // Rotation of -90º Degrees, relative to the X Axis... Now our Z axis, assumes the initial position of the Y axis.
    glTranslatef(0,0,5+yy); // Translation of "5+axes_y", relative to the Z Axis
    glColor3f(0.0f,1.0f,0.0f); // Color of our Y Arrow Head
    glutSolidCone(0.1,0.3,5,5); // Arrow Head is drawn, as a solid cone. Base on Z=0, Height on Z=0.3, Radius of 0.3 {5 slices and 5 stacks}.
    // This cone stays in the previously  translated position. In this case "5+axes_y"
    glTranslatef(0,0,-5-yy); // Translates to the initial position - origin
    glRotatef(90.f,1,0,0); // Rotates to the initial position - origin

    // Arrow Head of Z Axis (BLUE)
    glTranslatef(0,0,5+zz); // Translation of "5+axes_z", relative to the Z Axis
    glColor3f(0.0f,0.0f,1.0f); // Color of our Z Arrow Head
    glutSolidCone(0.1,0.3,5,5); // Arrow Head is drawn, as a solid cone. Base on Z=0, Height on Z=0.3, Radius of 0.3 {5 slices and 5 stacks}.
    // This cone stays in the previously  translated position. In this case "5+axes_z"
    glTranslatef(0,0,-5-zz); // Translates to the initial position - origin

    glBegin(GL_LINES);

    // Line of X Axis (RED) - From (0,0,0) to (5+axes_x,0,0)
    glColor3f(1.0,0,0);
    glVertex3f(0,0,0);
    glVertex3f(5 + xx,0,0);

    // Line of Y Axis (GREEN) - From (0,0,0) to (0,5+axes_y,0)
    glColor3f(0,1.0,0);
    glVertex3f(0,0,0);
    glVertex3f(0,5 + yy,0);

    // Line of Z Axis (BLUE) - From (0,0,0) to (0,0,5+axes_z)
    glColor3f(0,0,1.0);
    glVertex3f(0,0,0);
    glVertex3f(0,0,5 + zz);

    glEnd();

    // Letter X coloring (RED) and positioning (5+axes_x+0.5,0,0)
    glColor3f(1.0,0,0);
    glRasterPos3f((5 + xx + 0.5),0,0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'X');

    // Letter Y coloring (GREEN) and positioning (0,5+axes_y+0.5,0)
    glColor3f(0,1.0,0);
    glRasterPos3f(0,(5 + yy + 0.5),0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'Y');

    // Letter Z coloring (BLUE) and positioning (0,0,5+axes_z+0.5)
    glColor3f(0,0,1.0);
    glRasterPos3f(0,0,(5 + zz + 0.5));
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'Z');
}
// função que desenha as órbitas
void renderCatmullRomCurve( vector<Ponto> pontos) {
    int x = pontos.size();
    float npts[3];
    int i;

    glBegin(GL_LINE_LOOP);

    for(i=0; i < x ; i ++) {
        npts[0] = pontos[i].getX();
        npts[1] = pontos[i].getY();
        npts[2] = pontos[i].getZ();

        glVertex3fv(npts);
    }

    glEnd();
}


void renderScene(void){
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    glPolygonMode(GL_FRONT_AND_BACK,draw);

    gluLookAt(lx,ly,lz, //todo: alterar aqui
              lxx,lyy,lzz,
              0.0f,1.0f,0.0f);


    glTranslatef(0, -1, zz);

    //draw instructions
    glRotatef(angleY, 0.0, 1.0, 0.0);
    glRotatef(angleX, 1.0, 0.0, 0.0);
    glRotatef(angleZ, 0.0, 0.0, 1.0);
    glTranslatef(-xx,-yy,-zz);

    //drawAxis();

    int deriv[3];

    for(size_t i = 0; i < transformacoes.size(); i++) {
        glPushMatrix();
        Transforms trf = transformacoes[i];
        Transformacao transform = transformacoes[i].getTrans();

        //planetas

        if (!transform.semTranformacao()) {
            Rotacao rot = transform.getRotacao();

            if (!rot.semRotacao() && rot.getTime() != 0) {
                float t = glutGet(GLUT_ELAPSED_TIME) % (int) (rot.getTime() * 1000);
                float tempo = (t * 360) / (rot.getTime() * 1000);
                glRotatef(tempo, rot.getX(), rot.getY(), rot.getZ());
            }

            Translacao trl = transform.getTranslacao();
            if (!trl.semTranslacao()) {
                if (trl.getSize() > 0) {
                    float t = glutGet(GLUT_ELAPSED_TIME) % (int) (rot.getTime() * 1000);
                    float tempo = (t * 360) / (rot.getTime() * 1000);
                    trl.encurvar();
                    renderCatmullRomCurve(trl.getCurvas());
                    trl.getGlobalCatmullRomPoint(tempo, deriv, trl.getTransl());
                    glTranslatef(deriv[0], deriv[1], deriv[2]);
                }
            }
            Escala esc = transform.getEscala();
            if (!esc.semEscala())
                glScalef(esc.getX(), esc.getY(), esc.getZ());

            Cor cor = transform.getCor();
            if (!cor.semCor())
                glColor3f(cor.getR(), cor.getG(), cor.getG());

            //satélites
            if(transformacoes[i].getSubgrupo().size() != 0) {
                vector<Transforms> subg = transformacoes[i].getSubgrupo();
                for (size_t j = 0; j < subg.size(); j++) {
                    Transformacao subtransf = subg[j].getTrans();

                    if (!subtransf.semTranformacao()) {
                        glPushMatrix();
                        Translacao t = subtransf.getTranslacao();

                        if (!t.semTranslacao()) {
                            if (t.getSize() > 0) {
                                float te = glutGet(GLUT_ELAPSED_TIME) % (int) (t.getTime() * 1000);
                                float tempo = te / (t.getTime() * 1000);
                                vector<Ponto> trl = t.getTransl();
                                t.encurvar();
                                renderCatmullRomCurve(t.getCurvas());
                                t.getGlobalCatmullRomPoint(tempo, deriv, trl);
                                glTranslatef(deriv[0], deriv[1], deriv[2]); //todo: verificar !!!!!!
                                glRotatef(90.0, 1.0, 0.0, 0.0);
                            }
                        }

                        Rotacao subrot = subtransf.getRotacao();

                        if (!subrot.semRotacao()) {
                            float r = glutGet(GLUT_ELAPSED_TIME) % (int) (subrot.getTime() * 1000);
                            float tempo = (r * 360) / (subrot.getTime() * 1000);
                            glRotatef(tempo, subrot.getX(), subrot.getY(), subrot.getZ());
                        }

                        Escala subesc = subtransf.getEscala();

                        if (!subesc.semEscala())
                            glScalef(subesc.getX(), subesc.getY(), subesc.getZ());

                        Cor subcor = subtransf.getCor();
                        if (!subcor.semCor())
                            glColor3f(subcor.getR(), subcor.getG(), subcor.getB());
                    }
                    subg[j].draw();
                }
            }
            trf.draw();
            //TODO:

            //VBO
            //transform[j].encurvar() ???
            //transform.setVBO() ???

            glPopMatrix();
        }
    }
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

void keyboard(unsigned char key, int a, int b) {
    switch (key) {
        case 'a':
        case 'A':
            angleY -= 5;
            if (angleY < -360) angleY += 360;
            break;
        case 'd':
        case 'D':
            angleY += 5;
            if (angleY > 360) angleY -= 360;
            break;
        case 'q':
        case 'Q':
            angleX -= 5;
            if (angleX < -360) angleX += 360;
            break;

        case 'e':
        case 'E':
            angleX += 5;
            if (angleX > 360) angleX -= 360;
            break;
        case 'w':
        case 'W':
            angleZ += 5;
            if(angleZ > 360) angleZ += 360;
            break;
        case 's':
        case 'S':
            angleZ -= 5;
            if(angleZ < -360) angleZ -=360;
            break;
        case '+':
            glTranslatef(lx -= 1, ly -= 1, lz -= 1);
            break;

        case '-':
            glTranslatef(lx += 1, ly += 1, lz += 1);
            break;
        case 'f':
        case 'F':
            draw = GL_FILL;
            break;
        case 'p':
        case 'P':
            draw = GL_POINT;
            break;
        case 'l':
        case 'L':
            draw = GL_LINE;
            break;
        case 27:
            glutDestroyWindow(window);
            exit(0);
    }
}

void keyboardspecial(int key, int a, int b){
    switch (key){
        case GLUT_KEY_UP:
            zz -=cos(angleY /180 * M_PI);
            xx +=sin(angleY /180 * M_PI);
            break;
        case GLUT_KEY_DOWN:
            zz +=1 * cos(angleY /180 * M_PI);
            xx -=1 * sin(angleY /180 * M_PI);
            break;
        case GLUT_KEY_LEFT:
            xx -=cos(angleY /180 * M_PI);
            zz -=sin(angleY /180 * M_PI);
            break;
        case GLUT_KEY_RIGHT:
            xx +=cos(angleY /180 * M_PI);
            zz +=sin(angleY /180 * M_PI);
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

    trans.setX(trans.getX() + transf.getTranslacao().getX());
    trans.setY(trans.getY() + transf.getTranslacao().getY());
    trans.setZ(trans.getZ() +  transf.getTranslacao().getZ());
    es.setX(es.getX() * transf.getEscala().getX());
    es.setY(es.getY() * transf.getEscala().getY());
    es.setZ(es.getZ() * transf.getEscala().getZ());
    rot.setTime(rot.getTime());
    rot.setX(rot.getX() + transf.getRotacao().getX());
    rot.setY(rot.getY() + transf.getRotacao().getY());
    rot.setZ(rot.getZ() + transf.getRotacao().getZ());
    cor.setR(cor.getR());
    cor.setG(cor.getG());
    cor.setB(cor.getB());

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

    float xx = 0.0,yy = 0.0,zz = 0.0, transX = 0.0, transY = 0.0, transZ = 0.0, ang = 0.0, esX = 0.0, esY=0.0,esZ=0.0, rotX=0.0, rotY=0.0, rotZ=0.0, time = 0 ;
    float cr=1, cg=1, cb=1;



    if(strcmp(group->FirstChildElement()->Value(),"group")==0){
        group = group->FirstChildElement();

    }

    XMLElement* transfor = group->FirstChildElement();
    XMLAttribute* at;
    XMLAttribute* as;
    XMLAttribute* ar;
    XMLAttribute* ac;
    XMLAttribute* pt;

    for(transfor; (strcmp(transfor->Value(),"models")!=0); transfor = transfor->NextSiblingElement()){

        if(strcmp(transfor->Value(), "translate")==0) {

            at = const_cast<XMLAttribute *>(transfor->FirstAttribute());
            if(strcmp(at->Name(),"X")==0) transX = stof(transfor->Attribute("X"));
            else transX = 0;
            if(strcmp(at->Name(),"Y")==0) transY = stof(transfor->Attribute("Y"));
            else transY=0;
            if(strcmp(at->Name(),"Z")==0) transZ = stof(transfor->Attribute("Z"));
            else transZ=0;


            if(transfor->Attribute("time")) time = stof(transfor->Attribute("time"));
            else time = 0;

            vector<Ponto> trp;

            for(XMLElement* point = transfor->FirstChildElement("point"); point; point = point->NextSiblingElement("point")){

                pt = const_cast<XMLAttribute *>(transfor->FirstAttribute());
                if(strcmp(pt->Name(),"X")==0) xx = stof(transfor->Attribute("X"));
                else xx = 0;
                if(strcmp(pt->Name(),"Y")==0) yy = stof(transfor->Attribute("Y"));
                else yy=0;
                if(strcmp(pt->Name(),"Z")==0) zz = stof(transfor->Attribute("Z"));
                else zz=0;

                Ponto ptt = Ponto(xx,yy,zz);

                trp.push_back(ptt);
            }


                trl = Translacao(transX,transY,transZ,time,trp.size(),trp);

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

            time = stof(transfor->Attribute("time"));

            ang = stof(transfor->Attribute("angle"));

            rotX = stof(transfor->Attribute("X"));

            rotY = stof(transfor->Attribute("Y"));

            rotZ = stof(transfor->Attribute("Z"));

            rot =Rotacao(time,ang,rotX,rotY,rotZ);
        }
        if(strcmp(transfor->Value(), "colour")==0){



            cr= stof(transfor->Attribute("R"));

            cg = stof(transfor->Attribute("G"));

            cb = stof(transfor->Attribute("B"));

            cor = Cor(cr,cg,cb);


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

        cout << "Translacao ->" << trf.getTranslacao().getX() << "-" << trf.getTranslacao().getY() << "-" << trf.getTranslacao().getZ() << endl;
        cout << "Escala ->" << trf.getEscala().getX() << "-" << trf.getEscala().getY() << "-" << trf.getEscala().getZ() << endl;
        cout << "Rotacao -> " << trf.getRotacao().getAngle() << "-" << trf.getRotacao().getX() << "-" << trf.getRotacao().getY() << "-" << trf.getRotacao().getZ() << endl;
        cout << "Cor ->" << trf.getCor().getB() <<  "--" << trf.getCor().getG() << "-" << trf.getCor().getR()<<endl;
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
    glutInitWindowSize(1000,1000);
    window = glutCreateWindow("CG_Project");

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