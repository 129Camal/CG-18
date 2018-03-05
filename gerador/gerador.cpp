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

void box(double c, double l, double a, int camadas, string f){
    
}

/*
void box(double c, double l, double a, int camadas, string f) {
    double x, xx, y, yy, z, zz;
    double espC, espL, espA;
    ofstream file(f);
    int i;

    //definição dos espaços entre camadas;

    espC = c / (camadas-1);
    espL = l / (camadas-1);
    espA = a / (camadas-1);

    //fazer as camadas cima e baixo;

    y = a / 2;
    yy = -y;
    x = c / 2;
    xx = -x;
    z = l / 2;
    zz = -z;

    // fazer o lado que tem que ficar do virado para o lado oposto do ciclo  ---- ???????????????????
    printf("%f %f %f\n", x, yy, z);
    file << x << "," << yy << "," << z << endl;
    printf("%f %f %f\n", xx, yy, z);
    file << xx << "," << yy << "," << z << endl;
    printf("%f %f %f\n", xx, yy, zz);
    file << xx << "," << yy << "," << zz << endl;

    printf("%f %f %f\n", xx, yy, zz);
    file << xx << "," << yy << "," << zz << endl;
    printf("%f %f %f\n", x, yy, zz);
    file << x << "," << yy << "," << zz << endl;
    printf("%f %f %f\n", x, yy, z);
    file << x << "," << yy << "," << z << endl;

    yy = yy + espA;


    for (i = 0; i < camadas-1; i++) {

        printf("%f %f %f\n", x, yy, zz);
        file << x << "," << yy << "," << zz << endl;
        printf("%f %f %f\n", xx, yy, zz);
        file << xx << "," << yy << "," << zz << endl;
        printf("%f %f %f\n", xx, yy, z);
        file << xx << "," << yy << "," << z << endl;

        printf("%f %f %f\n", xx, yy, z);
        file << xx << "," << yy << "," << z << endl;
        printf("%f %f %f\n", x, yy, z);
        file << x << "," << yy << "," << z << endl;
        printf("%f %f %f\n", x, yy, zz);
        file << x << "," << yy << "," << zz << endl;

        yy += espA;

    }

    //fazer camadas da esquerda para direita

    x = c / 2;
    xx = -x;
    y = a / 2;
    yy = -y;
    z = l / 2;
    zz = -z;

    // fazer o lado que tem que ficar do virado para o lado oposto do ciclo
    printf("%f %f %f\n", xx, y, z);
    file << xx << "," << y << "," << z << endl;
    printf("%f %f %f\n", xx, y, zz);
    file << xx << "," << y << "," << zz << endl;
    printf("%f %f %f\n", xx, yy, zz);
    file << xx << "," << yy << "," << zz << endl;

    printf("%f %f %f\n", xx, y, zz);
    file << xx << "," << y << "," << zz << endl;
    printf("%f %f %f\n", xx, yy, zz);
    file << xx << "," << yy << "," << zz << endl;
    printf("%f %f %f\n", xx, yy, z);
    file << xx << "," << yy << "," << z << endl;

    xx += espC;

    for (i = 0; i < camadas-1 && xx <= x; i++) {

        printf("%f %f %f\n", xx, y, zz);
        file << xx << "," << y << "," << zz << endl;
        printf("%f %f %f\n", xx, y, z);
        file << xx << "," << y << "," << z << endl;
        printf("%f %f %f\n", xx, yy, z);
        file << xx << "," << yy << "," << z << endl;

        printf("%f %f %f\n", xx, yy, z);
        file << xx << "," << yy << "," << z << endl;
        printf("%f %f %f\n", xx, yy, zz);
        file << xx << "," << yy << "," << zz << endl;
        printf("%f %f %f\n", xx, y, zz);
        file << xx << "," << y << "," << zz << endl;

        xx += espC;

    }

    //fazer camadas de frente para trás

    z = l / 2;
    zz = -z;
    y = a / 2;
    yy = -y;
    x = c / 2;
    xx = -x;

    printf("%f %f %f\n", xx, yy, zz);
    file << xx << "," << yy << "," << zz << endl;
    printf("%f %f %f\n", xx, y, zz);
    file << xx << "," << y << "," << zz << endl;
    printf("%f %f %f\n", x, y, zz);
    file << x << "," << y << "," << zz << endl;

    printf("%f %f %f\n", x, y, zz);
    file << x << "," << y << "," << zz << endl;
    printf("%f %f %f\n", x, yy, zz);
    file << x << "," << yy << "," << zz << endl;
    printf("%f %f %f\n", xx, yy, zz);
    file << xx << "," << yy << "," << zz << endl;

    zz += espL;

    for (i = 0; i < camadas-1 && zz <= z; i++) {

        printf("%f %f %f\n", x, y, zz);
        file << x << "," << y << "," << zz << endl;
        printf("%f %f %f\n", xx, y, zz);
        file << xx << "," << y << "," << zz << endl;
        printf("%f %f %f\n", xx, yy, zz);
        file << xx << "," << yy << "," << zz << endl;

        printf("%f %f %f\n", xx, yy, zz);
        file << xx << "," << yy << "," << zz << endl;
        printf("%f %f %f\n", x, yy, zz);
        file << x << "," << yy << "," << zz << endl;
        printf("%f %f %f\n", x, y, zz);
        file << x << "," << y << "," << zz << endl;

        zz += espL;

    }
    file.close();
}
*/

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

            printf("%f %f %f\n", x7, y7, z7);
            file << x7 << "," << y7 << "," << z7 << endl;
            printf("%f %f %f\n", x8, y8, z8);
            file << x8 << "," << y8 << "," << z8 << endl;
            printf("%f %f %f\n", x9, y9, z9);
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
    /*printf("dhuhfis");
    if(argc < 1) {
        printf("Faltam argumentos\n");
        return 1;
    }

    if(strcmp(argv[1], "plano") == 0)
        plano(atof(argv[2]), atof(argv[3]), argv[4]);
}*/

}