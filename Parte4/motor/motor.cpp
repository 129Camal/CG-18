//
// Created by 87 Dolly on 27/03/2018.
//

#include "headers/motor.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

using namespace std;
using namespace tinyxml2;

int draw = GL_LINE;
int window;
vector<Transforms> transformacoes;
vector<Ponto> pontos;
vector<Ponto> normal;
vector<Ponto> texturaz;
Camara cam = Camara();

//luzinhas
string tipoluz;
float isPoint = 0;
float luzX, luzY, luzZ;

// função que desenha as órbitas


//TODO: verificar  parâmetros dos translates
void renderScene(void){
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    glPolygonMode(GL_FRONT_AND_BACK,draw);

    gluLookAt(cam.getLX(), cam.getLY(), cam.getLZ(),
              cam.getLX()+cam.getLLX(), cam.getLY()+cam.getLLY(), cam.getLZ()+cam.getLLZ(),
              0.0f,1.0f,0.0f);


    float deriv[3];
    float res[3];

    for(size_t i = 0; i < transformacoes.size(); i++) {
        glPushMatrix();
        Transforms trf = transformacoes[i];
        Transformacao transform = transformacoes[i].getTransformacao();

        //sol
        if(i==0){
            GLfloat pos[4] = { luzX, luzY, luzZ, isPoint};
            GLfloat amb[3] = { 0.0, 0.0, 0.0 };
            GLfloat diff[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
            GLfloat matt[3] = { 5, 5, 5 };

            glMaterialf(GL_FRONT, GL_SHININESS, 50);
            glLightfv(GL_LIGHT0, GL_POSITION, pos); // posição da luz
            glLightfv(GL_LIGHT0, GL_AMBIENT, amb); // luz ambiente
            glLightfv(GL_LIGHT0, GL_DIFFUSE, diff); // luz difusa

            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matt);
        }
        else {
            GLfloat matt[3] = { 0, 0, 0 };
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matt);
        }

        //planetas

        if (!transform.semTranformacao()) {

            Translacao trl = transform.getTranslacao();
            if (!trl.semTranslacao()) {
                if (trl.getSize() > 0 && trl.getTime() > 0) {
                    float t = glutGet(GLUT_ELAPSED_TIME) % (int) (trl.getTime() * 1000);
                    float tempo = t / (trl.getTime() * 1000.0);
                    vector<Ponto> curva = trl.encurvar();
                    trl.renderCatmullRomCurve(curva, transform.getCor().getR()/255, transform.getCor().getG()/255, transform.getCor().getB()/255);
                    trl.getGlobalCatmullRomPoint(tempo, deriv, res, trl.getTransl());
                    glTranslatef(res[0], res[1], res[2]);
                }
            }

            Rotacao rot = transform.getRotacao();

            if (!rot.semRotacao() && rot.getTime() != 0) {
                float t = glutGet(GLUT_ELAPSED_TIME) % (int) (rot.getTime() * 1000);
                float tempo = (t * 360.0) / (rot.getTime() * 1000.0);
                glRotatef(tempo, rot.getX(), rot.getY(), rot.getZ());
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
                        float tempo = te / (t.getTime() * 1000.0);
                        vector<Ponto> subcurva= t.encurvar();
                        t.renderCatmullRomCurve(subcurva, subtransf.getCor().getR()/255, subtransf.getCor().getG()/255, subtransf.getCor().getB()/255);
                        t.getGlobalCatmullRomPoint(tempo, deriv, res, t.getTransl());
                        glTranslatef(res[0], res[1], res[2]);

                    }else{
                        glTranslatef(t.getX(),t.getY(),t.getZ());
                    }

                    Rotacao subrot = subtransf.getRotacao();
                        if (subrot.getTime() != 0) {
                            float r = glutGet(GLUT_ELAPSED_TIME) % (int) (subrot.getTime() * 1000);
                            float tempo = (r * 360) / (subrot.getTime() * 1000);
                            glRotatef(tempo, subrot.getX(), subrot.getY(), subrot.getZ());
                        }

                    Escala subesc = subtransf.getEscala();
                    glScalef(subesc.getX(), subesc.getY(), subesc.getZ());

                    Cor cor = subtransf.getCor();
                    if (!cor.semCor())
                        glColor3f(cor.getR()/255, cor.getG()/255, cor.getB()/255);

                    if(subg[j].getText().compare("") != 0) {
                        glBindTexture(GL_TEXTURE_2D, subg[j].getTexID());
                        glEnable(GL_LIGHTING);
                    }
                    subg[j].draw();
                    glDisable(GL_LIGHTING);
                    glBindTexture(GL_TEXTURE_2D, 0);
                    glPopMatrix();
                }
            }
            Cor cor = transform.getCor();
            if (!cor.semCor())
                glColor3f(cor.getR()/255, cor.getG()/255, cor.getB()/255);

            if(trf.getText().compare("") != 0) {
                glBindTexture(GL_TEXTURE_2D, trf.getTexID());
                glEnable(GL_LIGHTING);
            }
            trf.draw();
            glDisable(GL_LIGHTING);
            glBindTexture(GL_TEXTURE_2D, 0);
            glPopMatrix();
        }
    cam.displayFPS();
    cam.camaraMove();
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

void keyboard(unsigned char key, int x, int y){
   cam.pressKeys(key, x, y);

    switch(key){
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

void releaseK(unsigned char key, int x, int y){
    cam.releaseKeys(key, x, y);
}

void mouseMotion(int x, int y){
    cam.mouseMove(x, y);
}

void setVBO(){

    glPolygonMode(GL_FRONT, GL_FILL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);
    glShadeModel (GL_SMOOTH);

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

    if(file.is_open()) {

        while (getline(file, linha) && (linha.compare("--normais--")) != 0) {

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
        if ((linha.compare("--normais--")) == 0) {
            while (getline(file, linha) && (linha.compare("--texturas--")) != 0) {
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

                normal.push_back(p);
            }
        }

        if ((linha.compare("--texturas--")) == 0) {
            while (getline(file, linha)) {
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

                texturaz.push_back(p);
            }
        }
        file.close();  //todo: verificar se esta merda é aqui, colei o pisto com as chavetas
    }
    else {
        cout << "ERRO AO LER FICHEIRO" << endl;
    }
}

//Parse do XML tendo em conta os níveis hierarquicos

void Parser(XMLElement *group , Transformacao transf, string p){

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

    for( ; (strcmp(transfor->Value(),"models")!=0); transfor = transfor->NextSiblingElement()){

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
            else time = 0;

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


    esc.setX(esc.getX() * transf.getEscala().getX());
    esc.setY(esc.getY() * transf.getEscala().getY());
    esc.setZ(esc.getZ() * transf.getEscala().getZ());

    trf = Transformacao(trl,rot,esc,cor);


    for(XMLElement* models = group->FirstChildElement("models")->FirstChildElement("model"); models; models = models -> NextSiblingElement("model")){

        Transforms tran;

        tran.setTipo(models->Attribute("fich"));
        if (models->Attribute("text")) tran.setText(models->Attribute("text"));
        cout << tran.getTipo() << endl;
        readFile(tran.getTipo());
        tran.setPontos(pontos);
        tran.setNormal(normal);
        tran.setTextura(texturaz);
        pontos.clear();
        normal.clear();
        texturaz.clear();
        tran.setTrans(trf);

        cout << "Translacao ->" << trf.getTranslacao().getTime() << endl;
        cout << "Escala ->" << trf.getEscala().getX() << "-" << trf.getEscala().getY() << "-" << trf.getEscala().getZ() << endl;
        cout << "Rotacao -> " << trf.getRotacao().getAngle() << "-"  << trf.getRotacao().getTime() << "-" << trf.getRotacao().getX() << "-" << trf.getRotacao().getY() << "-" << trf.getRotacao().getZ() << endl;
        cout << "Cor ->" << trf.getCor().getB() <<  "--" << trf.getCor().getG() << "-" << trf.getCor().getR()<<endl;
        if(p == "I"){
            transformacoes.push_back(tran);
        }
        if(p == "F"){
            int pos = transformacoes.size() - 1;
            transformacoes[pos].push_child(tran);
        }
        if(p == "P"){
            int pos = transformacoes.size() - 1;
            transformacoes[pos].push_child(tran);
        }

    }
        // faz parse dos filhos
    if(group->FirstChildElement("group")){
            Parser(group->FirstChildElement("group"),trf,"F");
    }


    if(group->NextSiblingElement("group") && (p == "F" || p == "P")){
        Parser(group->NextSiblingElement("group"),transf,"P");
    }
        //faz parse nos irmãos
    if(group->NextSiblingElement("group") && p != "F" && p != "P"){
        Parser(group->NextSiblingElement("group"),transf,"I");
    }

}


//método para ler ficheiro xml

void lerXML(string fich) {
    XMLDocument doc;

    if (!(doc.LoadFile(fich.c_str()))) {

            XMLElement * scene = doc.FirstChildElement("scene");
            XMLElement * group = scene-> FirstChildElement("group");
            XMLElement * luzes = scene-> FirstChildElement("lights");
            XMLElement * luz = luzes-> FirstChildElement("light");
            tipoluz = luz -> Attribute("luz");
            if(luz->Attribute("luz") && !tipoluz.compare(luz->Attribute("luz")))
                isPoint = 1;

            luzX = atof(luz->Attribute("posX"));
            luzY = atof(luz->Attribute("posY"));
            luzZ = atof(luz->Attribute("posZ"));

            Transformacao t = Transformacao();
            Escala esc = Escala(1,1,1);
            t.setEscala(esc);

            Parser(group,t,"I");

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

    //rato e teclado
    glutKeyboardUpFunc(releaseK);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(mouseMotion);
    glutSetCursor(GLUT_CURSOR_NONE);

    ilInit();
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

// OpenGL settings
    setVBO();

// enter GLUT's main loop
    glutMainLoop();

    return 1;

}
#pragma clang diagnostic pop