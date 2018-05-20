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

    file << "--normais--" << endl;
    //triangulo1
    file << 0 << "," << 1 << "," << 0 << endl;
    file << 0 << "," << 1 << "," << 0 << endl;
    file << 0 << "," << 1 << "," << 0 << endl;

    //triangulo2
    file << 0 << "," << 1 << "," << 0 << endl;
    file << 0 << "," << 1 << "," << 0 << endl;
    file << 0 << "," << 1 << "," << 0 << endl;

    file << "--texturas--" << endl; //VERIFICAR SE OS PONTOS ESTAO CERTOS
    //triangulo1
    file << 0 << "," << 1 << endl;
    file << 1 << "," << 1 << endl;
    file << 0 << "," << 1 << endl;

    //triangulo2
    file << 0 << "," << 0 << endl;
    file << 1 << "," << 0 << endl;
    file << 0 << "," << 1 << endl;


    file.close();
}
void box(float c, float l, float a, int camadas, string f){
    ofstream file(f);
    float x,y,z, xx, yy, zz;
    int i, j;
    float pontoX, pontoY, pontoZ, r, s, textX, textY;
    vector<Ponto> normal;
    vector<Ponto> text;

    //definição dos espaços entre as camadas
    float espC = c / camadas;
    float espL = l / camadas;
    float espA = a / camadas;

    //formulas textura
    textX = 0.25 / camadas;
    textY = 0.33 / camadas;

    //fazer as faces da frente e face de trás.
    y = a / 2;
    yy = -y;
    x = c / 2;
    xx = -x;
    z = l / 2;
    zz = -z;

    float frenteX = 0.75;
    float frenteY = 0.33;
    float trasX = 0.25;
    float trasY = 0.33;

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

            //normal
            normal.push_back(Ponto(0,0,1));
            normal.push_back(Ponto(0,0,1));
            normal.push_back(Ponto(0,0,1));
            normal.push_back(Ponto(0,0,1));
            normal.push_back(Ponto(0,0,1));
            normal.push_back(Ponto(0,0,1));

            //texturas

            text.push_back(Ponto(frenteX, frenteY, 0));
            text.push_back(Ponto(frenteX + textX, frenteY, 0));
            text.push_back(Ponto(frenteX + textX, frenteY + textY, 0));

            text.push_back(Ponto(frenteX + textX, frenteY + textY, 0));
            text.push_back(Ponto(frenteX, frenteY + textY, 0));
            text.push_back(Ponto(frenteX, frenteY, 0));

            //face de trás
            file << r << "," << s << "," << zz << endl;
            file << r << "," << pontoY << "," << zz << endl;
            file << pontoX << "," << pontoY << "," << zz << endl;

            file << pontoX << "," << pontoY << "," << zz << endl;
            file << pontoX << "," << s << "," << zz << endl;
            file << r << "," << s << "," << zz << endl;

            //normal
            normal.push_back(Ponto(0,0,-1));
            normal.push_back(Ponto(0,0,-1));
            normal.push_back(Ponto(0,0,-1));
            normal.push_back(Ponto(0,0,-1));
            normal.push_back(Ponto(0,0,-1));
            normal.push_back(Ponto(0,0,-1));

            //texturas
            text.push_back(Ponto(trasX, trasY, 0));
            text.push_back(Ponto(trasX + textX, trasY, 0));
            text.push_back(Ponto(trasX + textX, trasY + textY, 0));

            text.push_back(Ponto(trasX + textX, trasY + textY, 0));
            text.push_back(Ponto(trasX, trasY + textY, 0));
            text.push_back(Ponto(trasX, trasY, 0));

            frenteX += textX;
            trasX += textX;
        }

        frenteY += textY;
        trasY += textY;

    }

    //face de cima e de baixo
    //começa numa posição Z e depois faz a linha toda de X e no fim sobe uma posição de Y

    float cimaX = 0.25;
    float cimaY = 0.66;
    float baixoX = 0;
    float baixoY = 0;

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

            //normal
            normal.push_back(Ponto(0,1,0));
            normal.push_back(Ponto(0,1,0));
            normal.push_back(Ponto(0,1,0));
            normal.push_back(Ponto(0,1,0));
            normal.push_back(Ponto(0,1,0));
            normal.push_back(Ponto(0,1,0));

            //texturas
            text.push_back(Ponto(cimaX, cimaY, 0));
            text.push_back(Ponto(cimaX + textX, cimaY, 0));
            text.push_back(Ponto(cimaX + textX, cimaY + textY, 0));

            text.push_back(Ponto(cimaX + textX, cimaY + textY, 0));
            text.push_back(Ponto(cimaX, cimaY + textY, 0));
            text.push_back(Ponto(cimaX, cimaY, 0));

            //face de baixo
            file << r << "," << yy << "," << s << endl;
            file << pontoX << "," << yy << "," << s << endl;
            file << pontoX << "," << yy << "," << pontoZ << endl;

            file << pontoX << "," << yy << "," << pontoZ << endl;
            file << r << "," << yy << "," << pontoZ << endl;
            file << r << "," << yy << "," << s << endl;

            //normal
            normal.push_back(Ponto(0,-1,0));
            normal.push_back(Ponto(0,-1,0));
            normal.push_back(Ponto(0,-1,0));
            normal.push_back(Ponto(0,-1,0));
            normal.push_back(Ponto(0,-1,0));
            normal.push_back(Ponto(0,-1,0));

            //texturas
            text.push_back(Ponto(baixoX, baixoY, 0));
            text.push_back(Ponto(baixoX + textX, baixoY, 0));
            text.push_back(Ponto(baixoX + textX, baixoY + textY, 0));

            text.push_back(Ponto(baixoX + textX, baixoY + textY, 0));
            text.push_back(Ponto(baixoX, baixoY + textY, 0));
            text.push_back(Ponto(baixoX, baixoY, 0));

            cimaX += textX;
            baixoX += textX;
        }

        cimaY += textY;
        baixoY += textY;

    }

    //face da esquerda e da direita
    //começa numa posição de Z faz toda a linha e depois sobe uma unidade de Y.
    y = a / 2;
    yy = -y;
    x = c / 2;
    xx = -x;
    z = l / 2;
    zz = -z;

    float esquerdaX = 0;
    float esquerdaY = 0.33;
    float direitaX = 0.25;
    float direitaY = 0.33;

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

            //normal
            normal.push_back(Ponto(-1,0,0));
            normal.push_back(Ponto(-1,0,0));
            normal.push_back(Ponto(-1,0,0));
            normal.push_back(Ponto(-1,0,0));
            normal.push_back(Ponto(-1,0,0));
            normal.push_back(Ponto(-1,0,0));

            //texturas
            text.push_back(Ponto(esquerdaX, esquerdaY, 0));
            text.push_back(Ponto(esquerdaX + textX, esquerdaY, 0));
            text.push_back(Ponto(esquerdaX + textX, esquerdaY + textY, 0));

            text.push_back(Ponto(esquerdaX + textX, esquerdaY + textY, 0));
            text.push_back(Ponto(esquerdaX, esquerdaY + textY, 0));
            text.push_back(Ponto(esquerdaX, esquerdaY, 0));

            //face da direita
            file << x << "," << s << "," << r << endl;
            file << x << "," << pontoY << "," << r << endl;
            file << x << "," << s << "," << pontoZ << endl;

            file << x << "," << pontoY << "," << r << endl;
            file << x << "," << pontoY << "," << pontoZ << endl;
            file << x << "," << s << "," << pontoZ << endl;

            //normal
            normal.push_back(Ponto(1,0,0));
            normal.push_back(Ponto(1,0,0));
            normal.push_back(Ponto(1,0,0));
            normal.push_back(Ponto(1,0,0));
            normal.push_back(Ponto(1,0,0));
            normal.push_back(Ponto(1,0,0));

            //texturas
            text.push_back(Ponto(direitaX, direitaY, 0));
            text.push_back(Ponto(direitaX + textX, direitaY, 0));
            text.push_back(Ponto(direitaX + textX, direitaY + textY, 0));

            text.push_back(Ponto(direitaX + textX, direitaY + textY, 0));
            text.push_back(Ponto(direitaX, direitaY + textY, 0));
            text.push_back(Ponto(direitaX, direitaY, 0));

            esquerdaX+= textX;
            direitaX += textX;
        }

        esquerdaY += textY;
        direitaY += textY;
    }
    for(i = 0; i < normal.size(); i++){
        file << normal[i].getX() << "," << normal[i].getY() << "," << normal[i].getZ() << endl;
    }

    for(i = 0; i < text.size(); i++){
        file << text[i].getX() << "," << text[i].getY() << "," << text[i].getZ() << endl;
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

    vector<Ponto> normal;
    vector<Ponto> text;

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

        //normal
        normal.push_back(Ponto(0,-1,0));
        normal.push_back(Ponto(0,-1,0));
        normal.push_back(Ponto(0,-1,0));


    }

    //fazer a parte de cima do cone camada a camada
    for(i = 0; i < cH; i++){
        camadaB = alt + (i * espH);
        camadaA = alt + ((i+1) * espH);

        raioB = r - ((r/cH)*i);
        raioA = r - ((r / cH) * (i+1));

        for(j = 0; j < slices; j++){
            float alpha = espS * j;

            x4 = raioB * sin(alpha);
            y4 = camadaB;
            z4 = raioB * cos(alpha);

            //normal
            normal.push_back(Ponto(sin(alpha), a/cH, cos(alpha)));

            x5 = raioA * sin(alpha + espS);
            y5 = camadaA;
            z5 = raioA * cos(alpha + espS);

            //normal
            normal.push_back(Ponto(sin(alpha + espS), a/cH, cos(alpha + espS)));

            x6 = raioA * sin(alpha);
            y6 = camadaA;
            z6 = raioA * cos(alpha);

            //normal
            normal.push_back(Ponto(sin(alpha), a/cH, cos(alpha)));


            file << x4 << "," << y4 << "," << z4 << endl;
            file << x5 << "," << y5 << "," << z5 << endl;
            file << x6 << "," << y6 << "," << z6 << endl;

            x7 = raioB * sin(alpha);
            y7 = camadaB;
            z7 = raioB * cos(alpha);

            //normal
            normal.push_back(Ponto(sin(alpha), a/cH, cos(alpha)));

            x8 = raioB * sin(alpha + espS);
            y8 = camadaB;
            z8 = raioB * cos(alpha + espS);

            //normal
            normal.push_back(Ponto(sin(alpha + espS), a/cH, cos(alpha + espS)));

            x9 = raioA * sin(alpha + espS);
            y9 = camadaA;
            z9 = raioA * cos(alpha + espS);

            //normal
            normal.push_back(Ponto(sin(alpha + espS), a/cH, cos(alpha + espS)));

            file << x7 << "," << y7 << "," << z7 << endl;
            file << x8 << "," << y8 << "," << z8 << endl;
            file << x9 << "," << y9 << "," << z9 << endl;
        }

    }

    for(i = 0; i < normal.size(); i++){
        file << normal[i].getX() << "," << normal[i].getY() << "," << normal[i].getZ() << endl;
    }

    file.close();
}

void sphere(float r, int cv, int ch, string f){
    ofstream file(f);
    float espV = 2 * M_PI / cv;
    float espH = M_PI / ch;
    int i, j, x, y;
    float angH, angV;
    float x1, x2, x3, x4, y1, y2, y3, y4, z1, z2, z3, z4;
    vector<Ponto> normal;
    vector<Ponto> text;

    float texV = 1 / (float)cv;
    float texH = 1 / (float)ch;


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

            //normal
            normal.push_back(Ponto(x1 / r, y1 / r, z1 / r));
            normal.push_back(Ponto(x2 / r, y2 / r, z2 / r));
            normal.push_back(Ponto(x3 / r, y3 / r, z3 / r));

            file << x1 << "," << y1 << "," << z1 << endl;
            file << x3 << "," << y3 << "," << z3 << endl;
            file << x4 << "," << y4 << "," << z4 << endl;

            //normal

            normal.push_back(Ponto(x1 / r, y1 / r, z1 / r));
            normal.push_back(Ponto(x3 / r, y3 / r, z3 / r));
            normal.push_back(Ponto(x4 / r, y4 / r, z4 / r));

            //texturas
            text.push_back(Ponto(j*texV, i*texH, 0));
            text.push_back(Ponto(j*texV + texV, i*texH + texH, 0));
            text.push_back(Ponto(j*texV + texV, i*texH, 0));

            text.push_back(Ponto(j*texV + texV, i*texH + texH, 0));
            text.push_back(Ponto(j*texV, i*texH, 0));
            text.push_back(Ponto(j*texV, i*texH + texH, 0));


        }
    }
    file << "--normais--" << endl;
    for(i = 0; i < normal.size(); i++){
        file << normal[i].getX() << "," << normal[i].getY() << "," << normal[i].getZ() << endl;
    }
    file << "--texturas--" << endl;
    for(i = text.size() - 1; i >= 0; i-=3){
        file << text[i].getX() << "," << text[i].getY() << "," << text[i].getZ() << endl;
        file << text[i-1].getX() << "," << text[i-1].getY() << "," << text[i-1].getZ() << endl;
        file << text[i-2].getX() << "," << text[i-2].getY() << "," << text[i-2].getZ() << endl;
    }
    file.close();
}

void cylinder(float raio, float altura, int slices, int slicesH, string f){
    ofstream file(f);

    vector<Ponto> normal;
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

        //normal
        normal.push_back(Ponto(0, 1, 0));
        normal.push_back(Ponto(0, 1, 0));
        normal.push_back(Ponto(0, 1, 0));

        //circunferência de baixo
        file << x2 << "," << y2 << "," << z2 << endl;
        file << x1 << "," << y1 << "," << z1 << endl;
        file << x3 << "," << y3 << "," << z3 << endl;

        //normal
        normal.push_back(Ponto(0, -1, 0));
        normal.push_back(Ponto(0, -1, 0));
        normal.push_back(Ponto(0, -1, 0));



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

            //normal
            normal.push_back(Ponto(sin(ang), 0, cos(ang)));
            normal.push_back(Ponto(sin(ang), 0, cos(ang)));
            normal.push_back(Ponto(sin(ang + espS), 0, cos(ang + espS)));


            file << x3 << "," << y3 << "," << z3 << endl;
            file << x4 << "," << y4 << "," << z4 << endl;
            file << x1 << "," << y1 << "," << z1 << endl;

            //normal
            normal.push_back(Ponto(sin(ang + espS), 0, cos(ang + espS)));
            normal.push_back(Ponto(sin(ang + espS), 0, cos(ang + espS)));
            normal.push_back(Ponto(sin(ang), 0, cos(ang)));

        }

    }
    for(i = 0; i < normal.size(); i++){
        file << normal[i].getX() << "," << normal[i].getY() << "," << normal[i].getZ() << endl;
    }

    file.close();
}

void torus(float raioI, float raioE, float slices, float stacks, string fich){
    ofstream file(fich);
    int i,j;
    float x1, x2, x3, x4, y1, y2, y3, y4, z1, z2, z3, z4;

    vector<Ponto> normal;
    vector<Ponto> text;

    float textureS = float(1)/ stacks;
    float textureR = float(1)/ slices;

    float theta=0, phi=0, shiftT, shiftP;
    shiftT = 2 * M_PI / slices;
    shiftP = 2 * M_PI / stacks;

    for(i=0; i<slices; i++){
        for(j=0; j<stacks; j++){

            x1 = cos(theta)*(raioI+raioE*cos(phi));
            y1 = sin(theta) * (raioI + raioE * cos(phi));
            z1 = raioE * sin(phi);

            x2 = cos(theta + shiftT)*(raioI+raioE*cos(phi));
            y2 = sin(theta + shiftT) * (raioI + raioE * cos(phi));
            z2 = raioE * sin(phi);

            x3 = cos(theta + shiftT)*(raioI+raioE*cos(phi + shiftP));
            y3 = sin(theta + shiftT) * (raioI + raioE * cos(phi + shiftP));
            z3 = raioE * sin(phi + shiftP);

            x4 = cos(theta)*(raioI+raioE*cos(phi + shiftP));
            y4 = sin(theta) * (raioI + raioE * cos(phi + shiftP));
            z4 = raioE * sin(phi + shiftP);

            file << x1 << "," << y1 << "," << z1 << endl;
            file<< x2 << "," << y2 << "," << z2 << endl;
            file<< x3 << "," << y3 << "," << z3 << endl;

            //normal
            normal.push_back(Ponto(cos(theta)*cos(phi), sin(theta) * cos(phi), sin(phi)));
            normal.push_back(Ponto(cos(theta + shiftT)*cos(phi), sin(theta + shiftT) * cos(phi), sin(phi)));
            normal.push_back(Ponto(cos(theta + shiftT)*cos(phi + shiftP), sin(theta + shiftT) * cos(phi + shiftP), sin(phi + shiftP)));

            //texturas
            text.push_back(Ponto(i*textureR, j*textureS, 0));
            text.push_back(Ponto((i+1)*textureR, j*textureS, 0));
            text.push_back(Ponto((i+1)*textureR, (j+1)*textureS, 0));

            file<< x3 << "," << y3 << "," << z3 << endl;
            file<< x4 << "," << y4 << "," << z4 << endl;
            file<< x1 << "," << y1 << "," << z1 << endl;

            //normal
            normal.push_back(Ponto(cos(theta + shiftT)*cos(phi + shiftP), sin(theta + shiftT) * cos(phi + shiftP), sin(phi + shiftP)));
            normal.push_back(Ponto(cos(theta)*cos(phi + shiftP), sin(theta) * cos(phi + shiftP), sin(phi + shiftP)));
            normal.push_back(Ponto(cos(theta)*cos(phi), sin(theta) * cos(phi), sin(phi)));

            //texturas
            text.push_back(Ponto((i+1)*textureR, (j+1)*textureS, 0));
            text.push_back(Ponto(i*textureR, (j+1)*textureS, 0));
            text.push_back(Ponto(i*textureR, j*textureS, 0));

            phi = shiftP * (j+1);
        }
        theta = shiftT * (i+1) ;
    }
    file << "--normais--" << endl;
    for(i = 0; i < normal.size(); i++){
        file << normal[i].getX() << "," << normal[i].getY() << "," << normal[i].getZ() << endl;
    }
    file << "--texturas--" << endl;
    for(i = 0; i < text.size(); i++){
        file << text[i].getX() << "," << text[i].getY() << "," << text[i].getZ() << endl;
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
    cout <<"|       * Sair: ESC                                         |"<< endl;
    cout <<"|       * Representação do sólido:                          |"<< endl;
    cout <<"|           - por linhas: l | L                             |"<< endl;
    cout <<"|           - por pontos: p | P                             |"<< endl;
    cout <<"|           - preenchido: f | F                             |"<< endl;
    cout <<"|                                                           |"<< endl;
    cout <<" ------------------------------><---------------------------"<< endl;

}

float* bezierFormula(float t, float* p0, float* p1, float* p2, float *p3){
    float* result = new float[3];

    float aux = (1-t);

    float x0 = aux * aux * aux;
    float x1 = 3 * (aux * aux) * t;
    float x2 = 3 * aux * (t * t);
    float x3 = t * t * t;


    result[0] = x0 * p0[0] + x1 * p1[0] + x2 * p2[0] + x3 * p3[0];
    result[1] = x0 * p0[1] + x1 * p1[1] + x2 * p2[1] + x3 * p3[1];
    result[2] = x0 * p0[2] + x1 * p1[2] + x2 * p2[2] + x3 * p3[2];

    return result;


}

float* bezier(float n, float m, float** points, int* index){
    int i;
    float* point = new float[3];
    float* result = new float[3];
    int j = 0;
    int N = 0;
    float pointsAcumulator[4][3];
    float bezierAcumulator[4][3];

    for(i=0; i < 16; i++){

        pointsAcumulator[j][0] = points[index[i]][0];

        pointsAcumulator[j][1] = points[index[i]][1];

        pointsAcumulator[j][2] = points[index[i]][2];

        printf("P%d: %f , %f, %f\n", i, points[index[i]][0], points[index[i]][1], points[index[i]][2]);

        j++;

        if(j % 4 == 0){

            point = bezierFormula(n, pointsAcumulator[0], pointsAcumulator[1], pointsAcumulator[2], pointsAcumulator[3]);
            printf("RESULT: %f , %f, %f\n", point[0], point[1], point[2]);


            bezierAcumulator[N][0] = point[0];
            bezierAcumulator[N][1] = point[1];
            bezierAcumulator[N][2] = point[2];
            j = 0;
            N++;
        }
    }
    result = bezierFormula(m, bezierAcumulator[0], bezierAcumulator[1], bezierAcumulator[2], bezierAcumulator[3]);

    printf("RESULT: %f , %f, %f\n", result[0], result[1], result[2]);

    return result;
}

void makeBezier(string ReadFile, int tecelagem){

    ifstream read(ReadFile);
    ofstream write("bezier.3d");
    string line, value;
    int i1, i2, i3, p1, p2;
    int position;
    string delimiter = ",";
    float increment = 1.0 / tecelagem;


    if(read.is_open()){

        getline(read, line);
        int nPatches = atoi(line.c_str());
        int** index = new int*[nPatches];
        float*** resultPoints = new float**[nPatches];

        for(i1 = 0; i1 < nPatches; i1++){
            getline(read, line);
            index[i1] = new int[16];

            for(p1 = 0; p1 < 16; p1++){
                position = line.find(delimiter);
                value = line.substr(0, position);
                index[i1][p1] = atoi(value.c_str());
                line.erase(0, position + 1);
                //write << index[i1][p1] << endl;
            }


        }

        getline(read, line);
        int cPoints = atoi(line.c_str());
        float** points = new float*[cPoints];



        for(i2 = 0; i2 < cPoints; i2++){
            getline(read, line);
            points[i2] = new float[3];

            for(p2 = 0; p2 < 3; p2++){
                position = line.find(delimiter);
                value = line.substr(0, position);
                points[i2][p2] = atof(value.c_str());

                line.erase(0, position + 1);
            }
            //write << points[i2][0] << "," << points[i2][1] << "," << points[i2][2] << endl;
        }

        for(i3 = 0; i3 < nPatches; i3++){
            resultPoints[i3] = new float*[4];

            for(int xx = 0; xx < tecelagem; xx++ ) {

                for(int yy = 0; yy < tecelagem; yy++) {

                    float x1 = increment * xx;
                    float y1 = increment * yy;
                    float x2 = increment * ( xx+1 );
                    float y2 = increment * ( yy+1 );

                    resultPoints[i3][0] = bezier(x1, y1, points, index[i3]);
                    resultPoints[i3][1] = bezier(x1, y2, points, index[i3]);
                    resultPoints[i3][2] = bezier(x2, y1, points, index[i3]);
                    resultPoints[i3][3] = bezier(x2, y2, points, index[i3]);



                    write << resultPoints[i3][0][0] << "," << resultPoints[i3][0][1] << "," << resultPoints[i3][0][2] << endl;
                    write << resultPoints[i3][2][0] << "," << resultPoints[i3][2][1] << "," << resultPoints[i3][2][2] << endl;
                    write << resultPoints[i3][3][0] << "," << resultPoints[i3][3][1] << "," << resultPoints[i3][3][2] << endl;

                    write << resultPoints[i3][0][0] << "," << resultPoints[i3][0][1] << "," << resultPoints[i3][0][2] << endl;
                    write << resultPoints[i3][3][0] << "," << resultPoints[i3][3][1] << "," << resultPoints[i3][3][2] << endl;
                    write << resultPoints[i3][1][0] << "," << resultPoints[i3][1][1] << "," << resultPoints[i3][1][2] << endl;

                }
            }
        }
        write.close();
        read.close();



    } else {
        printf("Ficheiro de Input Inválido!");


    }

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
    if(strcmp(argv[1], "torus") == 0)
        torus(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), argv[6]);
    if(strcmp(argv[1], "patch") == 0)
        makeBezier(argv[2], atoi(argv[3]));
    return 0;
}