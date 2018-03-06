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

    for (i = yy; i < y; i+=espA) {

        for (j = xx; j < x; j += espC) {
            float pontoX = j + espC;
            float pontoY = i + espA;

            //face da frente
            //printf("%f %f %f\n", j, i, z);
            file << j << "," << i << "," << z << endl;
            //printf("%f %f %f\n", pontoX, i, z);
            file << pontoX << "," << i << "," << z << endl;
            //printf("%f %f %f\n", pontoX, pontoY, z);
            file << pontoX << "," << pontoY << "," << z << endl;

            //printf("%f %f %f\n", pontoX, pontoY, z);
            file << pontoX << "," << pontoY << "," << z << endl;
            //printf("%f %f %f\n", j, pontoY, z);
            file << j << "," << pontoY << "," << z << endl;
            //printf("%f %f %f\n", j, i, z);
            file << j << "," << i << "," << z << endl;

            //face de trás
            //printf("%f %f %f\n", j, i, zz);
            file << j << "," << i << "," << zz << endl;
            //printf("%f %f %f\n", j, pontoY, zz);
            file << j << "," << pontoY << "," << zz << endl;
            //printf("%f %f %f\n", pontoX, pontoY, zz);
            file << pontoX << "," << pontoY << "," << zz << endl;

            //printf("%f %f %f\n", pontoX, pontoY, zz);
            file << pontoX << "," << pontoY << "," << zz << endl;
            //printf("%f %f %f\n", pontoX, i, zz);
            file << pontoX << "," << i << "," << zz << endl;
            //printf("%f %f %f\n", j, i, zz);
            file << j << "," << i << "," << zz << endl;
        }
    }

    //face de cima e de baixo

    y = a / 2;
    yy = -y;
    x = c / 2;
    xx = -x;
    z = l / 2;
    zz = -z;

    for (i = zz; i < z; i+=espL) {

        for (j = xx; j < x; j += espC) {
            float pontoX = j + espC;
            float pontoZ = i + espL;

            //face da cima
            //printf("%f %f %f\n", j, y, i);
            file << j << "," << y << "," << i << endl;
            //printf("%f %f %f\n", j, y, pontoZ);
            file << j << "," << y << "," << pontoZ << endl;
            //printf("%f %f %f\n", pontoX, y, i);
            file << pontoX << "," << y << "," << i << endl;

            //printf("%f %f %f\n", j, y, pontoZ);
            file << j << "," << y << "," << pontoZ << endl;
            //printf("%f %f %f\n", pontoX, y, pontoZ);
            file << pontoX << "," << y << "," << pontoZ << endl;
            //printf("%f %f %f\n", pontoX, y, i);
            file << pontoX << "," << y << "," << i<< endl;



            //face de baixo
            //printf("%f %f %f\n", j, yy, i);
            file << j << "," << yy << "," << i << endl;
            //printf("%f %f %f\n", pontoX, yy, i);
            file << pontoX << "," << yy << "," << i << endl;
            //printf("%f %f %f\n", pontoX, yy, pontoZ);
            file << pontoX << "," << yy << "," << pontoZ << endl;

            //printf("%f %f %f\n", pontoX, yy, pontoZ);
            file << pontoX << "," << yy << "," << pontoZ << endl;
            //printf("%f %f %f\n", j, yy, pontoZ);
            file << j << "," << yy << "," << pontoZ << endl;
            //printf("%f %f %f\n", j, yy, i);
            file << j << "," << yy << "," << i << endl;
        }
    }

    //face da esquerda e de cima
    y = a / 2;
    yy = -y;
    x = c / 2;
    xx = -x;
    z = l / 2;
    zz = -z;

    for (i = zz; i < z; i+=espL) {

        for (j = yy; j < y; j += espA) {
            float pontoZ = i + espL;
            float pontoY = j + espA;

            //face da esquerda
            //printf("%f %f %f\n", xx, j, i);
            file << xx << "," << j << "," << i << endl;
            //printf("%f %f %f\n", xx, j, pontoZ);
            file << xx << "," << j << "," << pontoZ << endl;
            //printf("%f %f %f\n", xx, pontoY, i);
            file << xx << "," << pontoY << "," << i << endl;

            //printf("%f %f %f\n", xx, j, pontoZ);
            file << xx << "," << j << "," << pontoZ << endl;
            //printf("%f %f %f\n", xx, pontoY, pontoZ);
            file << xx << "," << pontoY << "," << pontoZ << endl;
            //printf("%f %f %f\n", xx, pontoY, i);
            file << xx << "," << pontoY << "," << i << endl;



            //face da direita
            //printf("%f %f %f\n", x, j, i);
            file << x << "," << j << "," << i << endl;
            //printf("%f %f %f\n", x, pontoY, i);
            file << x << "," << pontoY << "," << i << endl;
            //printf("%f %f %f\n", x, j, pontoZ);
            file << x << "," << j << "," << pontoZ << endl;

            //printf("%f %f %f\n", x, pontoY, i);
            file << x << "," << pontoY << "," << i << endl;
            //printf("%f %f %f\n", x, pontoY, pontoZ);
            file << x << "," << pontoY << "," << pontoZ << endl;
            //printf("%f %f %f\n", x, j, pontoZ);
            file << x << "," << j << "," << pontoZ << endl;
        }
    }


}

void cone(float r, float a, int cV, int cH, string f){
    ofstream file(f);
    float x1, x2, x3, y1, y2, y3, z1, z2, z3;
    float x4, x5, x6, y4, y5, y6, z4, z5, z6;
    float x7, x8, x9, y7, y8, y9, z7, z8, z9;

    float espV = (2 * M_PI) / cV;
    float espH = a / cH;
    float altura = -(a/2); //centrar

    //fazer a circunferência
    for (float ang = 0; ang < 2 * M_PI; ang+= espV){
        x1 = 0;
        y1 = altura;
        z1 = 0;

        x2 = r * sin(ang + espV);
        y2 = altura;
        z2 = r * cos(ang + espV);

        x3 = r * sin(ang);
        y3 = altura;
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

        for(int a = 0; a < cV; a += espV){

            float patamarB = r + i*espH;
            float patamarA = r + (i+1) * espH;

            float raioB = r - (r * i);
            float raioA = r - (r * (i+1));

            x4 = raioA * sin(a);
            y4 = patamarA;
            z4 = raioA * cos(a);

            x5 = raioB * sin(a);
            y5 = patamarB;
            z5 = raioB * cos(a);

            x6 = raioA * sin(a + espV);
            y6 = patamarA;
            z6 = raioB * sin(a + espV);

            printf("%f %f %f\n", x4, y4, z4);
            file << x1 << "," << y1 << "," << z1 << endl;
            printf("%f %f %f\n", x5, y5, z5);
            file << x2 << "," << y2 << "," << z2 << endl;
            printf("%f %f %f\n", x6, y6, z6);
            file << x3 << "," << y3 << "," << z3 << endl;

            x7 = raioB * sin(a);
            y7 = patamarB;
            z7 = raioB * cos(a);

            x8 = raioB * sin(a + espV);
            y8 = patamarB;
            z8 = raioB * cos(a + espV);

            x9 = raioA * sin(a + espV);
            y9 = patamarA;
            z9 = raioB * cos(a + espV);

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

//void sphere(float r, int cv, int ch, string f){
//    ofstream file(f);
//    float espV = 2* M_PI / ch;
//    float espH = M_PI / cv;


int main(int argc, char **argv) {
    if(argc < 1) {
        printf("Faltam argumentos\n");
        return 1;
    }

    if(strcmp(argv[1], "plano") == 0)
        plano(atof(argv[2]), atof(argv[3]), argv[4]);
    if(strcmp(argv[1], "box") == 0){
        box(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), argv[6]);
    }
    return 0;
}