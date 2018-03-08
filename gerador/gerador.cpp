#include "gerador.h"

void plano(float ladox, float ladoz, string f){
    float x, y = 0, z;
    ofstream file(f);


    x = ladox/2;
    z = ladoz/2;

    // Triangulo 1
    file << x << "," << y << "," << z << endl;
    file << x << "," << y << "," << -z << endl;
    file << -x << "," << y << "," << -z << endl;


    // Triangulo 2
    file << -x << "," << y << "," << z << endl;
    file << x << "," << y << "," << z << endl;
    file << -x << "," << y << "," << -z << endl;


    file.close();
}
void box(float c, float l, float a, int camadas, string f){
    ofstream file(f);
    float x,y,z, xx, yy, zz;
    int i, j;

    //definição dos espaços entre as camadas
    float espC = c / camadas;
    float espL = l / camadas;
    float espA = a / camadas;

    //fazer as faces da frente e face de trás.
    y = a / 2;
    yy = -y;
    x = c / 2;
    xx = -x;
    z = l / 2;
    zz = -z;


    //faz as camadas percorrendo a linha X e quando acabar sobe um posiçao de Y.
    for (i = 0; i < camadas; i++) {
        float s = yy + (espA * i);

        for (j = 0; j < camadas; j++ ) {
            float r = xx + (espC * j);

            float pontoX = r + espC; //shift em x
            float pontoY = s + espA; //shift em y

            //face da frente
            file << r << "," << s << "," << z << endl;
            file << pontoX << "," << s << "," << z << endl;
            file << pontoX << "," << pontoY << "," << z << endl;

            file << pontoX << "," << pontoY << "," << z << endl;
            file << r << "," << pontoY << "," << z << endl;
            file << r << "," << s << "," << z << endl;

            //face de trás
            file << r << "," << s << "," << zz << endl;
            file << r << "," << pontoY << "," << zz << endl;
            file << pontoX << "," << pontoY << "," << zz << endl;

            file << pontoX << "," << pontoY << "," << zz << endl;
            file << pontoX << "," << s << "," << zz << endl;
            file << r << "," << s << "," << zz << endl;
        }
    }

    //face de cima e de baixo

    y = a / 2;
    yy = -y;
    x = c / 2;
    xx = -x;
    z = l / 2;
    zz = -z;

    for (i = 0; i < camadas; i++) {
        float s = zz + (espL * i);


        for (j = 0; j < camadas; j ++) {

            float r = xx + (espC * j);

            float pontoX = r + espC;
            float pontoZ = s + espL;

            //face da cima
            file << r << "," << y << "," << s << endl;
            file << r << "," << y << "," << pontoZ << endl;
            file << pontoX << "," << y << "," << s << endl;

            file << r << "," << y << "," << pontoZ << endl;
            file << pontoX << "," << y << "," << pontoZ << endl;
            file << pontoX << "," << y << "," << s<< endl;



            //face de baixo
            file << r << "," << yy << "," << s << endl;
            file << pontoX << "," << yy << "," << s << endl;
            file << pontoX << "," << yy << "," << pontoZ << endl;

            file << pontoX << "," << yy << "," << pontoZ << endl;
            file << r << "," << yy << "," << pontoZ << endl;
            file << r << "," << yy << "," << s << endl;
        }
    }

    //face da esquerda e da direita
    y = a / 2;
    yy = -y;
    x = c / 2;
    xx = -x;
    z = l / 2;
    zz = -z;

    for (i = 0; i < camadas; i++) {
        float s = yy + (espA * i);

        for (j = 0; j < camadas; j++){
            float r = zz + (espL * j);

            float pontoZ = r + espL;
            float pontoY = s + espA;

            //face da esquerda
            file << xx << "," << s << "," << r << endl;
            file << xx << "," << s << "," << pontoZ << endl;
            file << xx << "," << pontoY << "," << pontoZ << endl;

            file << xx << "," << pontoY << "," << pontoZ << endl;
            file << xx << "," << pontoY << "," << r << endl;
            file << xx << "," << s << "," << r << endl;



            //face da direita
            file << x << "," << s << "," << r << endl;
            file << x << "," << pontoY << "," << r << endl;
            file << x << "," << s << "," << pontoZ << endl;

            file << x << "," << pontoY << "," << r << endl;
            file << x << "," << pontoY << "," << pontoZ << endl;
            file << x << "," << s << "," << pontoZ << endl;
        }
    }
    file.close();


}

void cone(float r, float a, int slices, int cH, string f){
    ofstream file(f);
    float x1, x2, x3, y1, y2, y3, z1, z2, z3;
    float x4, x5, x6, y4, y5, y6, z4, z5, z6;
    float x7, x8, x9, y7, y8, y9, z7, z8, z9;

    float espS = (2 * M_PI) / slices;
    float espH = a / cH;
    float alt = -a/2;

    //fazer a circunferência
    for (int i = 0; i < slices; i++){

        float ang = espS * i;

        x1 = 0;
        y1 = alt;
        z1 = 0;

        x2 = r * sin(ang + espS);
        y2 = alt;
        z2 = r * cos(ang + espS);

        x3 = r * sin(ang);
        y3 = alt;
        z3 = r * cos(ang);

        file << x1 << "," << y1 << "," << z1 << endl;
        file << x2 << "," << y2 << "," << z2 << endl;
        file << x3 << "," << y3 << "," << z3 << endl;

    }

    //fazer a parte de cima do cone
    for(int i = 0; i < cH; i++){


        for(int j = 0; j < slices; j++){
            float a = espS * j;

            float camadaBaixo = alt + (i * espH);
            float camadaAcima = alt + ((i+1) * espH);

            float raioBaixo = r - ((r/cH)*i);
            float raioAcima = r - ((r / cH) * (i+1));

            x4 = raioBaixo * sin(a);
            y4 = camadaBaixo;
            z4 = raioBaixo * cos(a);

            x5 = raioAcima * sin(a + espS);
            y5 = camadaAcima;
            z5 = raioAcima * cos(a + espS);

            x6 = raioAcima * sin(a);
            y6 = camadaAcima;
            z6 = raioAcima * cos(a);

            file << x4 << "," << y4 << "," << z4 << endl;
            file << x5 << "," << y5 << "," << z5 << endl;
            file << x6 << "," << y6 << "," << z6 << endl;

            x7 = raioBaixo * sin(a);
            y7 = camadaBaixo;
            z7 = raioBaixo * cos(a);

            x8 = raioBaixo * sin(a + espS);
            y8 = camadaBaixo;
            z8 = raioBaixo * cos(a + espS);

            x9 = raioAcima * sin(a + espS);
            y9 = camadaAcima;
            z9 = raioAcima * cos(a + espS);

            file << x7 << "," << y7 << "," << z7 << endl;
            file << x8 << "," << y8 << "," << z8 << endl;
            file << x9 << "," << y9 << "," << z9 << endl;
        }

    }
    file.close();
}

void sphere(float r, int cv, int ch, string f){
    ofstream file(f);
    float espV = 2 * M_PI / cv;
    float espH = M_PI / ch;
    int i, j;


    for(i = 0; i < ch; i++){

        float angH = espH * i;

        for (j=0; j < cv; j++){

            float angV = espV * j;


            float x1 = r * sin(angV) * sin(angH);
            float y1 = r * cos(angH);
            float z1 = r * sin(angH) * cos(angV);

            float x2 = r * sin(angH) * sin(angV + espV);
            float y2 = r * cos(angH);
            float z2 = r * sin(angH) * cos(angV + espV);

            float x3 = r * sin(angH + espH) * sin(angV + espV);
            float y3 = r * cos(angH + espH);
            float z3 = r * sin(angH + espH) * cos(angV + espV);

            float x4 = r * sin(angH + espH) * sin(angV);
            float y4 = r * cos(angH + espH);
            float z4 = r * sin(angH + espH) * cos(angV);

            file << x1 << "," << y1 << "," << z1 << endl;
            file << x2 << "," << y2 << "," << z2 << endl;
            file << x3 << "," << y3 << "," << z3 << endl;


            file << x1 << "," << y1 << "," << z1 << endl;
            file << x3 << "," << y3 << "," << z3 << endl;
            file << x4 << "," << y4 << "," << z4 << endl;


        }
    }
    file.close();
}

void cylinder(float raio, float altura, int slices, int slicesHorizontais, string f){
    ofstream file(f);

    float espS = 2 * M_PI / slices;
    float espSH = altura / slicesHorizontais;
    float x1, x2, x3, x4, y1, y2, y3, y4, z1, z2, z3, z4;
    float alt = -(altura/2);

    for (int i = 0; i < slices; i++){
        float ang = espS * i;

        x1 = 0;
        y1 = alt;
        z1 = 0;

        x2 = raio * sin(ang);
        y2 = alt;
        z2 = raio * cos(ang);

        x3 = raio * sin(ang + espS);
        y3 = alt;
        z3 = raio * cos(ang + espS);

        float yC = - alt;

        file << x2 << "," << y2 << "," << z2 << endl;
        file << x1 << "," << y1 << "," << z1 << endl;
        file << x3 << "," << y3 << "," << z3 << endl;

        file << x1 << "," << yC << "," << z1 << endl;
        file << x2 << "," << yC << "," << z2 << endl;
        file << x3 << "," << yC << "," << z3 << endl;

    }

    for(int i = 0; i <slicesHorizontais; i++){

        float altCamada = alt + (espSH * i);

        for(int j = 0; j < slices; j++){

            float ang = espS * j;

            x1 = raio * sin(ang);
            y1 = altCamada + espSH;
            z1 = raio * cos(ang);

            x2 = raio * sin(ang);
            y2 = altCamada;
            z2 = raio * cos(ang);

            x3 = raio * sin(ang + espS);
            y3 = altCamada;
            z3 = raio * cos(ang + espS);

            x4 = raio * sin(ang + espS);
            y4 = altCamada + espSH;
            z4 = raio * cos(ang + espS);


            file << x1 << "," << y1 << "," << z1 << endl;
            file << x2 << "," << y2 << "," << z2 << endl;
            file << x3 << "," << y3 << "," << z3 << endl;

            file << x3 << "," << y3 << "," << z3 << endl;
            file << x4 << "," << y4 << "," << z4 << endl;
            file << x1 << "," << y1 << "," << z1 << endl;

        }

    }
    file.close();

}

void help() {

    cout <<" ---------------------> MENU DE AJUDA <---------------------"<< endl;
    cout <<"|                                                           |"<< endl;
    cout <<"|       GERADOR:                                            |"<< endl;
    cout <<"|       $ g++ gerador.cpp -o gen                            |"<< endl;
    cout <<"|       $ ./gen <Modelo> [Parâmetros] figura.3d             |"<< endl;
    cout <<"|       $ mv figura.3d diretoria/Motor                      |"<< endl;
    cout <<"|                                                           |"<< endl;
    cout <<"|       MOTOR:                                              |"<< endl;
    cout <<"|       [build]$ make                                       |"<< endl;
    cout <<"|       $ ./TP ../CG-18/Motor/figura.xml                    |"<< endl;
    cout <<"|                                                           |"<< endl;
    cout <<"|------------------------> Modelo <-------------------------|"<< endl;
    cout <<"|                                                           |"<< endl;
    cout <<"|       * Plano lado lado                                   |"<< endl;
    cout <<"|       * Cubo comp larg alt nr_camadas                     |"<< endl;
    cout <<"|       * Cone raio altura nr_camadasV nr_camadasH          |"<< endl;
    cout <<"|       * Esfera raio nr_camadasV nr_camadasH               |"<< endl;
    cout <<"|                                                           |"<< endl;
    cout <<"|---------------------> Controlos 3D <----------------------|"<< endl;
    cout <<"|                                                           |"<< endl;
    cout <<"|       * Translação: Seta cima, baixo, esquerda, direita   |"<< endl;
    cout <<"|       * Rotação: w, a, s, d  | W, A, S, D                 |"<< endl;
    cout <<"|       * Zoom: + | -                                       |"<< endl;
    cout <<"|       * Representação do sólido:                          |"<< endl;
    cout <<"|           - por linhas: l | L                             |"<< endl;
    cout <<"|           - por pontos: p | P                             |"<< endl;
    cout <<"|           - preenchido: f | F                             |"<< endl;
    cout <<"|       * RESET: r | R                                      |"<< endl;
    cout <<"|                                                           |"<< endl;
    cout <<" ------------------------------><---------------------------"<< endl;

}

int main(int argc, char **argv) {
    /*if(argc < 1) {
        printf("Faltam argumentos\n");
        return 1;
    }
    if(strcmp(argv[1], "help") == 0)
        help();
    if(strcmp(argv[1], "plane") == 0)
        plano(atof(argv[2]), atof(argv[3]), argv[4]);
    if(strcmp(argv[1], "box") == 0){
        box(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), argv[6]);
    }
    if(strcmp(argv[1], "cone") == 0)
        cone(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), argv[6]);
    return 0;
     */
    sphere(2,20,10, "box.3d");
}