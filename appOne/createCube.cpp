#include<stdio.h>
#include"VECTOR.h"
#include"mathUtil.h"
void createCube()
{
    int numSquare = 6;
    int numVtx = 4 * numSquare;
    int numTri = 2 * numSquare;
    float l = 0.5f;

    FILE* fp = 0;
    fopen_s(&fp, "assets\\cube.txt", "w");

    fprintf(fp, "x orangeGreen assets\\orangeGreen.png\n");
    fprintf(fp, "x blackYellow assets\\blackYellow.png\n");
    fprintf(fp, "x cyanYellow assets\\cyanYellow.png\n");
    fprintf(fp, "x blueTwoTone assets\\blueTwoTone.png\n");
    
    //Batch
    fprintf(fp, "b cube cube cube 1\n");
    fprintf(fp, "0 %d blueTwoTone\n", numTri);
    fprintf(fp, "b cube1 cube cube 1\n");
    fprintf(fp, "0 %d cyanYellow\n", numTri);
    fprintf(fp, "b cube2 cube cube 1\n");
    fprintf(fp, "0 %d orangeGreen\n", numTri);
    fprintf(fp, "b cube3 cube cube 1\n");
    fprintf(fp, "0 %d blackYellow\n", numTri);

    //Vertices
    fprintf(fp, "v cube pnt %d\n", numVtx);
    //front
    fprintf(fp, "%3.1f %3.1f %3.1f  0 0 1  0 0 \n", -l,  l, l);
    fprintf(fp, "%3.1f %3.1f %3.1f  0 0 1  0 0 \n", -l, -l, l);
    fprintf(fp, "%3.1f %3.1f %3.1f  0 0 1  0 0 \n",  l,  l, l);
    fprintf(fp, "%3.1f %3.1f %3.1f  0 0 1  0 0 \n",  l, -l, l);
    //right
    fprintf(fp, "%3.1f %3.1f %3.1f  1 0 0   0 1\n", l, l, l);
    fprintf(fp, "%3.1f %3.1f %3.1f  1 0 0   0 1\n", l, -l, l);
    fprintf(fp, "%3.1f %3.1f %3.1f  1 0 0   0 1\n", l, l, -l);
    fprintf(fp, "%3.1f %3.1f %3.1f  1 0 0   0 1\n", l, -l, -l);
    //back
    fprintf(fp, "%3.1f %3.1f %3.1f  0 0 -1  0 0\n", l, l, -l);
    fprintf(fp, "%3.1f %3.1f %3.1f  0 0 -1  0 0\n", l, -l, -l);
    fprintf(fp, "%3.1f %3.1f %3.1f  0 0 -1  0 0\n", -l, l, -l);
    fprintf(fp, "%3.1f %3.1f %3.1f  0 0 -1  0 0\n", -l, -l, -l);
    //left
    fprintf(fp, "%3.1f %3.1f %3.1f  -1 0 0   0 0\n", -l, l, -l);
    fprintf(fp, "%3.1f %3.1f %3.1f  -1 0 0   0 0\n", -l, -l, -l);
    fprintf(fp, "%3.1f %3.1f %3.1f  -1 0 0   0 0\n", -l, l, l);
    fprintf(fp, "%3.1f %3.1f %3.1f  -1 0 0   0 0\n", -l, -l, l);
    //top
    fprintf(fp, "%3.1f %3.1f %3.1f  0 1 0  1 0 \n", -l, l, -l);
    fprintf(fp, "%3.1f %3.1f %3.1f  0 1 0  1 0 \n", -l, l, l);
    fprintf(fp, "%3.1f %3.1f %3.1f  0 1 0  1 0 \n", l, l, -l);
    fprintf(fp, "%3.1f %3.1f %3.1f  0 1 0  1 0 \n", l, l, l);
    //botom
    fprintf(fp, "%3.1f %3.1f %3.1f  0 -1 0  1 0 \n", -l, -l, -l);
    fprintf(fp, "%3.1f %3.1f %3.1f  0 -1 0  1 0 \n", l, -l, -l);
    fprintf(fp, "%3.1f %3.1f %3.1f  0 -1 0  1 0 \n", -l, -l, l);
    fprintf(fp, "%3.1f %3.1f %3.1f  0 -1 0  1 0 \n", l, -l, l);

    //Indices
    fprintf(fp, "i cube %d\n", numTri * 3);
    for (int i = 0; i < 6; i++) {
        int j = 4 * i;
        fprintf(fp, "%d %d %d\n", j + 0, j + 1, j + 2);
        fprintf(fp, "%d %d %d\n", j + 2, j + 1, j + 3);
    }

    fclose(fp);
}

