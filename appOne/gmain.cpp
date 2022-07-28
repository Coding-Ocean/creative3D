#include"libOne.h"
#include"SHADER/LAMBERT.h"
#include"CONTAINER/CONTAINER.h"
#include"CONTAINER/BATCH.h"
#include"createCube.h"
#include"view_proj.h"

void gmain()
{
    window(1920, 1080, full);
    hideCursor();
    angleMode(DEGREES);
    createProj();

    createCube();
    CONTAINER* container = new CONTAINER("assets\\cube.txt");
    BATCH* cube = container->batch("cube");

    VECTOR lightPos(0.4f,0.5f,0.6f);
    float ambient = 0.0f;
    COLOR diffuse(1,1,1);
    
    SHADER* shader = new LAMBERT;
    shader->setLightPosition(lightPos);
    setRasterizerCullBack();
    setRasterizerWire();
    
    MATRIX world;
    float angle = 0;
    float ofst = 180;
    float h;
    float t = 1.01f;
    int n = 8;
    float s = 0;//nに応じてサイズを決定
    float w = 1.0f;//棒の太さ
    int paternSw = 0;//計算パターン変更
    int rasterSw = 1;
    while (notQuit)
    {
        clear(0,0,0);
        updateView(shader);

        if (isTrigger(KEY_Q))n += 1;
        if (isTrigger(KEY_A))n -= 1;
        if (n < 1)n = 1;
        s = 3.0f/(n*2+1);

        if (isPress(KEY_W))w += 0.01f;
        if (isPress(KEY_S))w -= 0.01f;

        if (isPress(KEY_E))t += 0.01f;
        if (isPress(KEY_D))t -= 0.01f;

        //if (isPress(KEY_E))ofst += 1;
        //if (isPress(KEY_D))ofst -= 1;

        if (isTrigger(KEY_Z))++paternSw %= 5;


        setRasterizerCullBack();
        printSize(30);
        print((let)"paternSw:" + paternSw);
        print((let)"n:"+n);
        //print((let)"ofst:" + ofst);
        print((let)"t:"+t);

        if (isTrigger(KEY_X))rasterSw = 1 - rasterSw;
        if (rasterSw)setRasterizerCullBack();
        else setRasterizerWire();
        shader->setLightAmbient(ambient);
        shader->setDiffuse(diffuse);

        for (int z = -n; z <= n; z++) {
            for (int x = -n; x <= n; x++) {
                switch (paternSw) {
                case 0:h = Sin(angle + 360.0f * (x * x + z * z) / (n * n * 2)) + t; break;
                case 1:h = Sin(angle + (x * x + z * z)) + t; break;
                case 2:h = Sin(angle + 16 * (x + z)) + t; break;
                case 3:h = Sin(angle + 180 * x * z) + t; break;
                case 4:h = Sin(angle + 9 * x * z) + t; break;
                case 5:h = Sin(angle * ofst * (x * z / 3600.0f)) + t; break;
                }
                world.identity();
                world.mulTranslate(x * s, 0, z * s);
                world.mulScaling(s * w, s * h, s * w);
                cube->draw(shader, world);
            }
        }
        angle += 2;
    }

    delete container;
    delete shader;
}