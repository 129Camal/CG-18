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



void box(double c, double l, double a, int camadas, string f) {
    double x, xx, xxx, y, yy, yyy, z, zz, zzz;
    double espC, espL, espA;
    ofstream file(f);
    int i, j;

    //definição dos espaços entre camadas;

    espC = c / camadas;
    espL = l / camadas;
    espA = a / camadas;

    //fazer as camadas cima e baixo;

    y = a / 2;
    yy = -y;
    x = c / 2;
    xx = -x;
    z = l / 2;
    zz = -z;

    // fazer o lado que tem que ficar do virado para o lado oposto do ciclo
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

    yy += espA;


    for (i = 0; i < camadas-1 && yy <= y; i++) {

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
}


int main(int argc, char **argv) {
    /*printf("dhuhfis");
    if(argc < 1) {
        printf("Faltam argumentos\n");
        return 1;
    }

    if(strcmp(argv[1], "plano") == 0)
        plano(atof(argv[2]), atof(argv[3]), argv[4]);
}*/
    box(4, 4, 4, 4, "caixinha.txt");
}