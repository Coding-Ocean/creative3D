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
    fprintf(fp, "x white assets\\green_orange.png\n");
    fprintf(fp, "b cube cube cube 1\n");
    fprintf(fp, "0 %d white\n", numTri);

    fprintf(fp, "v cube pnt %d\n", numVtx);
    //ê≥ñ 
    fprintf(fp, "%3.1f %3.1f %3.1f  0 0 1  0 0 \n", -l,  l, l);
    fprintf(fp, "%3.1f %3.1f %3.1f  0 0 1  0 0 \n", -l, -l, l);
    fprintf(fp, "%3.1f %3.1f %3.1f  0 0 1  0 0 \n",  l,  l, l);
    fprintf(fp, "%3.1f %3.1f %3.1f  0 0 1  0 0 \n",  l, -l, l);
    ////âEñ 
    fprintf(fp, "%3.2f %3.2f %3.2f  1 0 0   0 0\n", l, l, l);
    fprintf(fp, "%3.2f %3.2f %3.2f  1 0 0   0 0\n", l, -l, l);
    fprintf(fp, "%3.2f %3.2f %3.2f  1 0 0   0 0\n", l, l, -l);
    fprintf(fp, "%3.2f %3.2f %3.2f  1 0 0   0 0\n", l, -l, -l);
    //ó†ñ 
    fprintf(fp, "%3.2f %3.2f %3.2f  0 0 -1  0 0\n", l, l, -l);
    fprintf(fp, "%3.2f %3.2f %3.2f  0 0 -1  0 0\n", l, -l, -l);
    fprintf(fp, "%3.2f %3.2f %3.2f  0 0 -1  0 0\n", -l, -l, -l);
    fprintf(fp, "%3.2f %3.2f %3.2f  0 0 -1  0 0\n", -l, l, -l);
    //ç∂ñ 
    fprintf(fp, "%3.2f %3.2f %3.2f  -1 0 0   0 0\n", -l, l, -l);
    fprintf(fp, "%3.2f %3.2f %3.2f  -1 0 0   0 0\n", -l, -l, -l);
    fprintf(fp, "%3.2f %3.2f %3.2f  -1 0 0   0 0\n", -l, l, l);
    fprintf(fp, "%3.2f %3.2f %3.2f  -1 0 0   0 0\n", -l, -l, l);
    //è„ñ 
    fprintf(fp, "%3.2f %3.2f %3.2f  0 1 0  1 0 \n", -l, l, -l);
    fprintf(fp, "%3.2f %3.2f %3.2f  0 1 0  1 0 \n", -l, l, l);
    fprintf(fp, "%3.2f %3.2f %3.2f  0 1 0  1 0 \n", l, l, -l);
    fprintf(fp, "%3.2f %3.2f %3.2f  0 1 0  1 0 \n", l, l, l);
    //â∫ñ 
    fprintf(fp, "%3.2f %3.2f %3.2f  0 -1 0  1 0 \n", -l, -l, -l);
    fprintf(fp, "%3.2f %3.2f %3.2f  0 -1 0  1 0 \n", l, -l, -l);
    fprintf(fp, "%3.2f %3.2f %3.2f  0 -1 0  1 0 \n", -l, -l, l);
    fprintf(fp, "%3.2f %3.2f %3.2f  0 -1 0  1 0 \n", l, -l, l);



    fprintf(fp, "i cube %d\n", numTri * 3);

    fprintf(fp, "0 1 2\n");
    fprintf(fp, "2 1 3\n");

    fprintf(fp, "4 5 6\n");
    fprintf(fp, "6 5 7\n");

    fprintf(fp, "8  9 10\n");
    fprintf(fp, "8 10 11\n");

    fprintf(fp, "12 13 14\n");
    fprintf(fp, "14 13 15\n");

    fprintf(fp, "16 17 18\n");
    fprintf(fp, "18 17 19\n");

    fprintf(fp, "20 21 22\n");
    fprintf(fp, "22 21 23\n");

    fclose(fp);
}

