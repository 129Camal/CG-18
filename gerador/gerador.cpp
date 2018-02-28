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




int main(int argc, char **argv) {
    printf("dhuhfis");
    if(argc < 1) {
        printf("Faltam argumentos\n");
        return 1;
    }

    if(strcmp(argv[1], "plano") == 0)
        plano(atof(argv[2]), atof(argv[3]), argv[4]);
}