#include "gerador.h"

void plano(float ladox, float ladoz, string f){
    float x, y = 0, z;
    ofstream file(f);


    x = ladox/2;
    z = ladoz/2;

    // Triangulo 1
    printf("%f %f %f\n",x,y,z);
    file << x << "," << y << "," << z << endl;
    printf("%f %f %f\n",x,y,-z);
    file << x << "," << y << "," << -z << endl;
    printf("%f %f %f\n",-x,y,-z);
    file << -x << "," << y << "," << -z << endl;


    // Triangulo 2
    printf("%f %f %f\n",-x,y,z);
    file << -x << "," << y << "," << z << endl;
    printf("%f %f %f\n",x,y,z);
    file << x << "," << y << "," << z << endl;
    printf("%f %f %f\n",-x,y,-z);
    file << -x << "," << y << "," << -z << endl;


    file.close();
}
void box(float c, float l, float a, int camadas, string f){
    ofstream file(f);
    float x,y,z, xx, yy, zz;
    float i, j;

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

    for (i = 0; i < camadas; i++) {
        float s = yy + (espA * i);

        for (j = 0; j < camadas; j++ ) {
            float r = xx + (espC * i);

            float pontoX = r + espC;
            float pontoY = s + espA;

            //face da frente
            //printf("%f %f %f\n", j, i, z);
            file << r << "," << s << "," << z << endl;
            //printf("%f %f %f\n", pontoX, i, z);
            file << pontoX << "," << s << "," << z << endl;
            //printf("%f %f %f\n", pontoX, pontoY, z);
            file << pontoX << "," << pontoY << "," << z << endl;

            //printf("%f %f %f\n", pontoX, pontoY, z);
            file << pontoX << "," << pontoY << "," << z << endl;
            //printf("%f %f %f\n", j, pontoY, z);
            file << r << "," << pontoY << "," << z << endl;
            //printf("%f %f %f\n", j, i, z);
            file << r << "," << s << "," << z << endl;

            //face de trás
            //printf("%f %f %f\n", j, i, zz);
            file << r << "," << s << "," << zz << endl;
            //printf("%f %f %f\n", j, pontoY, zz);
            file << r << "," << pontoY << "," << zz << endl;
            //printf("%f %f %f\n", pontoX, pontoY, zz);
            file << pontoX << "," << pontoY << "," << zz << endl;

            //printf("%f %f %f\n", pontoX, pontoY, zz);
            file << pontoX << "," << pontoY << "," << zz << endl;
            //printf("%f %f %f\n", pontoX, i, zz);
            file << pontoX << "," << s << "," << zz << endl;
            //printf("%f %f %f\n", j, i, zz);
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
            //printf("%f %f %f\n", j, y, i);
            file << r << "," << y << "," << s << endl;
            //printf("%f %f %f\n", j, y, pontoZ);
            file << r << "," << y << "," << pontoZ << endl;
            //printf("%f %f %f\n", pontoX, y, i);
            file << pontoX << "," << y << "," << s << endl;

            //printf("%f %f %f\n", j, y, pontoZ);
            file << r << "," << y << "," << pontoZ << endl;
            //printf("%f %f %f\n", pontoX, y, pontoZ);
            file << pontoX << "," << y << "," << pontoZ << endl;
            //printf("%f %f %f\n", pontoX, y, i);
            file << pontoX << "," << y << "," << s<< endl;



            //face de baixo
            //printf("%f %f %f\n", j, yy, i);
            file << r << "," << yy << "," << s << endl;
            //printf("%f %f %f\n", pontoX, yy, i);
            file << pontoX << "," << yy << "," << s << endl;
            //printf("%f %f %f\n", pontoX, yy, pontoZ);
            file << pontoX << "," << yy << "," << pontoZ << endl;

            //printf("%f %f %f\n", pontoX, yy, pontoZ);
            file << pontoX << "," << yy << "," << pontoZ << endl;
            //printf("%f %f %f\n", j, yy, pontoZ);
            file << r << "," << yy << "," << pontoZ << endl;
            //printf("%f %f %f\n", j, yy, i);
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
            printf("%f %f %f\n", xx, s, r);
            file << xx << "," << s << "," << r << endl;
            printf("%f %f %f\n", xx, s, pontoZ);
            file << xx << "," << s << "," << pontoZ << endl;
            printf("%f %f %f\n", xx, pontoY, pontoZ);
            file << xx << "," << pontoY << "," << pontoZ << endl;

            printf("%f %f %f\n", xx, pontoY, pontoZ);
            file << xx << "," << pontoY << "," << pontoZ << endl;
            printf("%f %f %f\n", xx, pontoY, r);
            file << xx << "," << pontoY << "," << r << endl;
            printf("%f %f %f\n", xx, s, r);
            file << xx << "," << s << "," << r << endl;



            //face da direita
            printf("%f %f %f\n", x, s, r);
            file << x << "," << s << "," << r << endl;
            printf("%f %f %f\n", x, pontoY, r);
            file << x << "," << pontoY << "," << r << endl;
            printf("%f %f %f\n", x, s, pontoZ);
            file << x << "," << s << "," << pontoZ << endl;

            printf("%f %f %f\n", x, pontoY, r);
            file << x << "," << pontoY << "," << r << endl;
            printf("%f %f %f\n", x, pontoY, pontoZ);
            file << x << "," << pontoY << "," << pontoZ << endl;
            printf("%f %f %f\n", x, s, pontoZ);
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

        printf("%f %f %f\n", x1, y1, z1);
        file << x1 << "," << y1 << "," << z1 << endl;
        printf("%f %f %f\n", x2, y2, z2);
        file << x2 << "," << y2 << "," << z2 << endl;
        printf("%f %f %f\n", x3, y3, z3);
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

            //printf("%f %f %f\n", x4, y4, z4);
            file << x4 << "," << y4 << "," << z4 << endl;
            //printf("%f %f %f\n", x5, y5, z5);
            file << x5 << "," << y5 << "," << z5 << endl;
            //printf("%f %f %f\n", x6, y6, z6);
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

            //printf("%f %f %f\n", x7, y7, z7);
            file << x7 << "," << y7 << "," << z7 << endl;
            //printf("%f %f %f\n", x8, y8, z8);
            file << x8 << "," << y8 << "," << z8 << endl;
            //printf("%f %f %f\n", x9, y9, z9);
            file << x9 << "," << y9 << "," << z9 << endl;
        }

    }
    file.close();
}

void sphere(float r, int cv, int ch, string f){
    ofstream file(f);
    float espV = 2* M_PI / ch;
    float espH = M_PI / cv;
    int i, j;

    for(i = 0; i < 2 * ch; i++){

        float angH = espH * i;

        for (j=0; j < cv; j++){

            float angV = espV * j;

            float x1 = r * cos(angH) * sin(angV);
            float y1 = r * sin(angH);
            float z1 = r * cos(angH) * cos(angV) ;

            float x2 = r * cos(angH) * sin(angV + espV);
            float y2 = r * sin(angH);
            float z2 = r * cos(angH) * cos(angV + espV);

            float x3 = r * cos(angH + espH) * sin(angV + espV);
            float y3 = r * sin(angH + espH);
            float z3 = r * cos(angH + espH) * cos(angV + espV);

            float x4 = r * cos(angH + espH) * sin(angV);
            float y4 = r * sin(angH + espH);
            float z4 = r * cos(angH + espH) * cos(angV);

            file << x1 << "," << y1 << "," << z1 << endl;
            //printf("%f %f %f\n", x8, y8, z8);
            file << x2 << "," << y2 << "," << z2 << endl;
            //printf("%f %f %f\n", x9, y9, z9);
            file << x3 << "," << y3 << "," << z3 << endl;

            //printf("%f %f %f\n", x4, y4, z4);
            file << x3 << "," << y3 << "," << z3 << endl;
            //printf("%f %f %f\n", x5, y5, z5);
            file << x4 << "," << y4 << "," << z4 << endl;
            //printf("%f %f %f\n", x6, y6, z6);
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
    if(strcmp(argv[1], "box") == 0){
        box(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), argv[6]);
    }
    if(strcmp(argv[1], "cone") == 0)
        cone(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), argv[6]);
    return 0;
}