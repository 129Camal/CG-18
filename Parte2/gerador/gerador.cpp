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
    float pontoX, pontoY, pontoZ, r, s;

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


    //faz as camadas percorrendo a linha X e quando acabar sobe uma posiçao de Y.
    for (i = 0; i < camadas; i++) {
        s = yy + (espA * i);

        for (j = 0; j < camadas; j++ ) {
            r = xx + (espC * j);

            pontoX = r + espC; //shift em x
            pontoY = s + espA; //shift em y

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
    //começa numa posição Z e depois faz a linha toda de X e no fim sobe uma posição de Y


    y = a / 2;
    yy = -y;
    x = c / 2;
    xx = -x;
    z = l / 2;
    zz = -z;

    for (i = 0; i < camadas; i++) {
        s = zz + (espL * i);


        for (j = 0; j < camadas; j ++) {

            r = xx + (espC * j);

            pontoX = r + espC;
            pontoZ = s + espL;

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
    //começa numa posição de Z faz toda a linha e depois sobe uma unidade de Y.
    y = a / 2;
    yy = -y;
    x = c / 2;
    xx = -x;
    z = l / 2;
    zz = -z;

    for (i = 0; i < camadas; i++) {
        s = yy + (espA * i);

        for (j = 0; j < camadas; j++){
            r = zz + (espL * j);

            pontoZ = r + espL;
            pontoY = s + espA;

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
    float alt = -a/2;//para centrar o cone no referencial
    int i, j;
    float ang, camadaB, camadaA, raioB, raioA;

    //fazer a circunferência da base
    for (i = 0; i < slices; i++){

        ang = espS * i;

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

    //fazer a parte de cima do cone camada a camada
    for(i = 0; i < cH; i++){
        camadaB = alt + (i * espH);
        camadaA = alt + ((i+1) * espH);

        raioB = r - ((r/cH)*i);
        raioA = r - ((r / cH) * (i+1));

        for(j = 0; j < slices; j++){
            a = espS * j;

            x4 = raioB * sin(a);
            y4 = camadaB;
            z4 = raioB * cos(a);

            x5 = raioA * sin(a + espS);
            y5 = camadaA;
            z5 = raioA * cos(a + espS);

            x6 = raioA * sin(a);
            y6 = camadaA;
            z6 = raioA * cos(a);

            file << x4 << "," << y4 << "," << z4 << endl;
            file << x5 << "," << y5 << "," << z5 << endl;
            file << x6 << "," << y6 << "," << z6 << endl;

            x7 = raioB * sin(a);
            y7 = camadaB;
            z7 = raioB * cos(a);

            x8 = raioB * sin(a + espS);
            y8 = camadaB;
            z8 = raioB * cos(a + espS);

            x9 = raioA * sin(a + espS);
            y9 = camadaA;
            z9 = raioA * cos(a + espS);

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
    float angH, angV;
    float x1, x2, x3, x4, y1, y2, y3, y4, z1, z2, z3, z4;


    for(i = 0; i < ch; i++){

        angH = espH * i;

        for (j=0; j < cv; j++){

            angV = espV * j;


            x1 = r * sin(angV) * sin(angH);
            y1 = r * cos(angH);
            z1 = r * sin(angH) * cos(angV);

            x2 = r * sin(angH) * sin(angV + espV);
            y2 = r * cos(angH);
            z2 = r * sin(angH) * cos(angV + espV);

            x3 = r * sin(angH + espH) * sin(angV + espV);
            y3 = r * cos(angH + espH);
            z3 = r * sin(angH + espH) * cos(angV + espV);

            x4 = r * sin(angH + espH) * sin(angV);
            y4 = r * cos(angH + espH);
            z4 = r * sin(angH + espH) * cos(angV);

            //fazer os dois triangulos que fazer a forma da face da esfera em cada iteração do circulo
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

void cylinder(float raio, float altura, int slices, int slicesH, string f){
    ofstream file(f);

    float espS = 2 * M_PI / slices;
    float espSH = altura / slicesH;
    float x1, x2, x3, x4, y1, y2, y3, y4, z1, z2, z3, z4;
    float alt = -(altura/2);
    float yC, ang, altCamada;
    int i, j;

    //fazer as duas bases(circunferências) do cilindro
    for (i = 0; i < slices; i++){
        ang = espS * i;

        x1 = 0;
        y1 = alt;
        z1 = 0;

        x2 = raio * sin(ang);
        y2 = alt;
        z2 = raio * cos(ang);

        x3 = raio * sin(ang + espS);
        y3 = alt;
        z3 = raio * cos(ang + espS);

        yC = - alt;

        //circunferência de cima
        file << x1 << "," << yC << "," << z1 << endl;
        file << x2 << "," << yC << "," << z2 << endl;
        file << x3 << "," << yC << "," << z3 << endl;
        //circunferência de baixo
        file << x2 << "," << y2 << "," << z2 << endl;
        file << x1 << "," << y1 << "," << z1 << endl;
        file << x3 << "," << y3 << "," << z3 << endl;



    }

    //unir as faces fazendo em N slicesHorizontais
    for(i = 0; i <slicesH; i++){

        altCamada = alt + (espSH * i);

        for(j = 0; j < slices; j++){

            ang = espS * j;

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

            //triângulos para fazer a face correspondente em cada ciclo
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
    if(argc < 1) {
        printf("Faltam argumentos\n");
        return 1;
    }
    if(strcmp(argv[1], "help") == 0)
        help();
    if(strcmp(argv[1], "plane") == 0)
        plano(atof(argv[2]), atof(argv[3]), argv[4]);
    if(strcmp(argv[1], "box") == 0)
        box(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), argv[6]);
    if(strcmp(argv[1], "cone") == 0)
        cone(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), argv[6]);
    if(strcmp(argv[1], "sphere") == 0)
        sphere(atof(argv[2]), atof(argv[3]), atof(argv[4]), argv[5]);
    if(strcmp(argv[1], "cylinder") == 0)
        cylinder(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), argv[6]);

    return 0;
}