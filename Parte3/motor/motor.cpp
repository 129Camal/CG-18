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


// função que desenha as órbitas
void renderCatmullRomCurve( vector<Ponto> pontos, float r, float g, float b) {
    int x = (int) pontos.size();
    float npts[3];
    int i;

    glBegin(GL_LINE_LOOP);

    for(i=0; i < x ; i ++) {
        npts[0] = pontos[i].getX();
        npts[1] = pontos[i].getY();
        npts[2] = pontos[i].getZ();
        glColor3f(r,g,b);
        glVertex3fv(npts);
    }

    glEnd();
}

//TODO: verificar  parâmetros dos translates
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

    float deriv[3];
    float res[3];

    for(size_t i = 0; i < transformacoes.size(); i++) {
        glPushMatrix();
        Transforms trf = transformacoes[i];
        Transformacao transform = transformacoes[i].getTransformacao();

        //planetas

        if (!transform.semTranformacao()) {
            Cor cor = transform.getCor();
            if (!cor.semCor())
                glColor3f(cor.getR(), cor.getG(), cor.getB());

            Translacao trl = transform.getTranslacao();
            if (!trl.semTranslacao()) {
                if (trl.getSize() > 0) {
                    float t = glutGet(GLUT_ELAPSED_TIME) % (int) (trl.getTime() * 1000);
                    float tempo = t / (trl.getTime() * 1000);
                    vector<Ponto> curva = trl.encurvar();
                    renderCatmullRomCurve(curva, transform.getCor().getR(), transform.getCor().getG(), transform.getCor().getB());
                    trl.getGlobalCatmullRomPoint(tempo, deriv, res, trl.getTransl());
                    glTranslatef(res[0], res[1], res[2]);
                    //trl.rodaCurva(deriv,trl.getCima());
                }
            }

            Rotacao rot = transform.getRotacao();

            if (!rot.semRotacao() && rot.getTime() != 0) {
                float t = glutGet(GLUT_ELAPSED_TIME) % (int) (rot.getTime() * 1000);
                float tempo = (t * 360) / (rot.getTime() * 1000);
                glRotatef(tempo, rot.getX(), rot.getY(), rot.getZ());
            }else{
                //glRotatef()
            }

            Escala esc = transform.getEscala();
            if (!esc.semEscala())
                glScalef(esc.getX(), esc.getY(), esc.getZ());


        }
            //satélites
            if(transformacoes[i].getSubgrupo().size() != 0) {
                vector<Transforms> subg = transformacoes[i].getSubgrupo();
                for (size_t j = 0; j < subg.size(); j++) {
                    glPushMatrix();
                    Transformacao subtransf = subg[j].getTransformacao();
                    Translacao t = subtransf.getTranslacao();

                    if(t.getTime() != 0){
                        float te = glutGet(GLUT_ELAPSED_TIME) % (int) (t.getTime() * 1000);
                        float tempo = te / (t.getTime() * 1000);
                        vector<Ponto> trl = t.getTransl();
                        vector<Ponto> subcurva= t.encurvar();
                        renderCatmullRomCurve(subcurva, subtransf.getCor().getR(), subtransf.getCor().getG(), subtransf.getCor().getB());
                        t.getGlobalCatmullRomPoint(tempo, deriv, res, trl);
                        glTranslatef(res[0], res[1], res[2]); //todo: verificar !!!!!!
                        //glRotatef(90.0, 1.0, 0.0, 0.0);
                    }

                    Rotacao subrot = subtransf.getRotacao();
                        if (subrot.getTime() != 0) {
                            float r = glutGet(GLUT_ELAPSED_TIME) % (int) (subrot.getTime() * 1000);
                            float tempo = (r * 360) / (subrot.getTime() * 1000);
                            glRotatef(tempo, subrot.getX(), subrot.getY(), subrot.getZ());
                        }

                    Escala subesc = subtransf.getEscala();
                    glScalef(subesc.getX(), subesc.getY(), subesc.getZ());

                    subg[j].draw();
                    glPopMatrix();
                }
            }
            trf.draw();
            glPopMatrix();
        }
    glutSwapBuffers();
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

void setVBO(){
    glPolygonMode(GL_FRONT, GL_FILL);
    for(size_t i = 0; i < transformacoes.size(); i++){
        transformacoes[i].setVBO();

        if(transformacoes[i].getSubgrupo().size() > 0){
            vector<Transforms> subg = transformacoes[i].getSubgrupo();

            for(size_t j = 0; j < subg.size(); j++) {
                subg[j].setVBO();
            }
            transformacoes[i].setSubgrupo(subg);
        }
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

    float xx = 0.0,yy = 0.0,zz = 0.0, transX = 0.0, transY = 0.0, transZ = 0.0, ang = 0.0, esX = 0.0, esY=0.0,esZ=0.0, rotX=0.0, rotY=0.0, rotZ=0.0, time = 1;
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
            else time = 1;

            vector<Ponto> trp;

            for(XMLElement* pt = transfor->FirstChildElement("point"); pt; pt = pt->NextSiblingElement("point")){


                if(pt->Attribute("X")) xx = stof(pt->Attribute("X"));
                else xx = 0;
                if(pt->Attribute("Y")) yy = stof(pt->Attribute("Y"));
                else yy=0;
                if(pt->Attribute("Z")) zz = stof(pt->Attribute("Z"));
                else zz=0;

                Ponto ptt = Ponto(xx,yy,zz);

                trp.push_back(ptt);
                printf("processei point\n");

            }



                trl = Translacao(transX, transY, transZ, time, trp.size(), trp);

        }
        if(strcmp(transfor->Value(), "scale")==0){

            as = const_cast<XMLAttribute *>(transfor->FirstAttribute());
            esX = stof(transfor->Attribute("X"));
            esY = stof(transfor->Attribute("Y"));
            esZ = stof(transfor->Attribute("Z"));

            esc.setX(esX);
            esc.setY(esY);
            esc.setZ(esZ);

            printf("processei scale\n");
        }



        if(strcmp(transfor->Value(), "rotate")==0){

            if(transfor->Attribute("time")) time = stof(transfor->Attribute("time"));
            else time = 1;

            if(transfor->Attribute("angle")) ang = stof(transfor->Attribute("angle"));
            else ang = 0;

            rotX = stof(transfor->Attribute("X"));

            rotY = stof(transfor->Attribute("Y"));

            rotZ = stof(transfor->Attribute("Z"));

            rot = Rotacao(time,ang,rotX,rotY,rotZ);

            printf("processei rotate\n");
        }


        if(strcmp(transfor->Value(), "colour")==0){

            cr= stof(transfor->Attribute("R"));

            cg = stof(transfor->Attribute("G"));

            cb = stof(transfor->Attribute("B"));

            cor = Cor(cr,cg,cb);

            printf("processei color\n");

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
    setVBO();

// enter GLUT's main loop
    glutMainLoop();

    return 1;

}
#pragma clang diagnostic pop