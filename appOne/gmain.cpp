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
    float h;
    float n = 8;
    float s2 = 1.0f;
    float ofst = 50;
    int sw = 0;
    float h2 = 1.01f;
    int rasterSw = 1;
    while (notQuit)
    {
        clear(0,0,0);
        updateView(shader);

        if (isTrigger(KEY_Q))n += 1;
        if (isTrigger(KEY_A))n -= 1;
        if (n < 1)n = 1;
        float scale = 3.0f/(n*2+1);

        if (isPress(KEY_W))s2 += 0.01f;
        if (isPress(KEY_S))s2 -= 0.01f;

        if (isPress(KEY_E))ofst += 1;
        if (isPress(KEY_D))ofst -= 1;
        if (isTrigger(KEY_Z))++sw %= 7;

        if (isPress(KEY_R))h2 += 0.01f;
        if (isPress(KEY_F))h2 -= 0.01f;

        setRasterizerCullBack();
        print((let)"sw:" + sw);
        print((let)"n:"+n);
        print((let)"ofst:"+ofst);
        if (isTrigger(KEY_X))rasterSw = 1 - rasterSw;
        if (rasterSw)setRasterizerCullBack();
        else setRasterizerWire();
        shader->setLightAmbient(ambient);
        shader->setDiffuse(diffuse);

        for (int z = -n; z <= n; z++) {
            for (int x = -n; x <= n; x++) {
                switch (sw) {
                case 0:h = Sin(angle + ofst * (x * x + z * z) / (n * n * 2))*2 + h2*2; break;
                case 1:h = Sin(angle + ofst * Sqrt(x * x + z * z) / Sqrt(n * n * 2)) + h2; break;
                case 2:h = Sin(angle + (x * x + z * z)) + h2; break;
                case 3:h = Sin(angle + (ofst * (x + z))) + h2; break;
                case 4:h = Sin(angle + (ofst * x * z)) + h2; break;
                case 5:h = Sin(angle * ofst * (x * z) / (n * n * 10)) + h2; break;
                case 6:h = Sin(angle + (ofst * Abs(x + z))) + h2; break;
                }
                world.identity();
                world.mulTranslate(x*scale, 0, z*scale);
                world.mulScaling(scale*s2, scale*h, scale*s2);
                cube->draw(shader, world);
            }
        }
        angle += 2;
    }

    delete container;
    delete shader;
}