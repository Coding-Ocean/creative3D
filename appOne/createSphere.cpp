#include<stdio.h>
#include"VECTOR.h"
#include"mathUtil.h"
void createSphere(int numAng)
{
    const int numVtx = numAng * (numAng / 2 - 1) + 2;//全頂点数
    int numTri = (numAng * 2) * (numAng / 2 - 2) + (numAng*2);
    VECTOR* p = new VECTOR[numVtx];
    VECTOR* n = new VECTOR[numVtx];
    float radius = 1.0f;
    FILE* fp=0;
    fopen_s(&fp, "assets\\assets.txt", "w");
    fprintf(fp, "x white assets\\white.png\n");
    fprintf(fp, "b sphere sphere sphere 1\n");
    fprintf(fp, "0 %d white\n", numTri);
    fprintf(fp, "v sphere pnt %d\n", numVtx);
    float angle = 360.0f / numAng;
    int k = 0;
    for (int j = 0; j < numAng / 2 - 1; j++) {
        float y = Cos(angle * (j + 1));
        float r = Sin(angle * (j + 1));
        //円の座標
        for (int i = 0; i < numAng; i++) {
            k = numAng * j + i;
            p[k].set(Cos(angle * i) * r*radius, y*radius, Sin(angle * i) * r*radius);
            n[k].set(Cos(angle * i) * r, y, Sin(angle * i) * r);
            fprintf(fp, "%f %f %f %f %f %f %d %d\n",
                p[k].x, p[k].y, p[k].z,
                n[k].x, n[k].y, n[k].z,
                0, 0
            );
        }
    }
    //北極になる頂点
    k++;
    p[k].set(0, radius, 0);
    n[k].set(0, 1, 0);
    fprintf(fp, "%f %f %f %f %f %f %d %d\n",
        p[k].x, p[k].y, p[k].z,
        n[k].x, n[k].y, n[k].z,
        0, 0
    );
    //南極になる頂点
    k++;
    p[k].set(0, -radius, 0);
    n[k].set(0, -1, 0);
    fprintf(fp, "%f %f %f %f %f %f %d %d\n",
        p[k].x, p[k].y, p[k].z,
        n[k].x, n[k].y, n[k].z,
        0, 0
    );

    fprintf(fp, "i sphere %d\n", numTri * 3);
    for (int j = 0; j < numAng/2-2; j++) {
        for (int i = 0; i < numAng; i++) {
            int a = (numAng * j) + i;
            int b = (numAng * j) + i + 1;
            int c = (numAng * j) + i + numAng;
            int d = c;
            int e = b;
            int f = (numAng * j) + i + numAng+1;
            if (b % numAng == 0) {
                b -= numAng;
                e = b;
                f -= numAng;
            }
            fprintf(fp, "%d %d %d\n", a, b, c);
            fprintf(fp, "%d %d %d\n", d, e, f);
        }
    }
    for (int i = 0; i < numAng; i++) {
        int a = k-1;
        int b = i + 1;
        int c = i;
        if (b % numAng == 0) {
            b -= numAng;
        }
        fprintf(fp, "%d %d %d\n", a, b, c);
    }
    int l = numAng * (numAng / 2 - 2);
    for (int i = 0; i < numAng; i++) {
        int a = k;
        int b = l + i;
        int c = l + i + 1;
        if (c % numAng == 0) {
            c -= numAng;
        }
        fprintf(fp, "%d %d %d\n", a, b, c);
    }

    fclose(fp);
    delete[] p;
    delete[] n;
}
