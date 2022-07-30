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
    BATCH* cube[4];
    cube[0] = container->batch("cube");
    cube[1] = container->batch("cube2");
    cube[2] = container->batch("cube1");
    cube[3] = container->batch("cube3");

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
    float t = 1.0f;
    int n = 8;
    float s = 0;//nに応じてサイズを決定
    float w = 1.0f;//棒の太さ
    int paternSw = 0;//計算パターン変更
    int rasterSw = 1;
    int batchSw = 0;

    while (notQuit)
    {
        clear(0, 0, 0);
        updateView(shader);

        if (isPress(KEY_SHIFT)) {
            if (isTrigger(KEY_Q))n += 10;
            if (isTrigger(KEY_A))n -= 10;
        }
        else {
            if (isTrigger(KEY_Q))n += 1;
            if (isTrigger(KEY_A))n -= 1;
        }
        if (n < 1)n = 1;
        s = 3.0f/(n*2+1);

        if (isPress(KEY_W))w += 0.01f;
        if (isPress(KEY_S))w -= 0.01f;

        if (isPress(KEY_E))t += 0.01f;
        if (isPress(KEY_D))t -= 0.01f;

        if (isTrigger(KEY_Z)) ++paternSw %= 5;
        
        if (isTrigger(KEY_C))++batchSw %= 4;

        setRasterizerCullBack();
        printSize(30);
        print((let)"patern:" + paternSw);
        print((let)"num:"+n);
        print((let)"fat:" + w);
        print((let)"thick:"+t);

        if (isTrigger(KEY_X))rasterSw = 1 - rasterSw;
        if (rasterSw)setRasterizerCullBack();
        else setRasterizerWire();
        shader->setLightAmbient(ambient);
        shader->setDiffuse(diffuse);

        for (int z = -n; z <= n; z++) {
            for (int x = -n; x <= n; x++) {
                switch (paternSw) {
                case 0:ofst = 360.0f * (x * x + z * z) / (n * n * 2); break;
                case 1:ofst = (float)x * x + z * z; break;
                case 2:ofst = 16.0f * (x + z); break;
                case 3:ofst = 180.0f * x * z; break;
                case 4:ofst = 9.0f * x * z; break;
                }
                h = Sin(angle + ofst)*t + t+0.01f;
                world.identity();
                world.mulTranslate(x * s, 0, z * s);
                world.mulScaling(s * w, s * h, s * w);
                cube[batchSw]->draw(shader, world);
            }
        }
        angle += 2;
    }

    delete container;
    delete shader;
}