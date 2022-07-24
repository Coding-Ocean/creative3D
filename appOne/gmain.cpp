#include"libOne.h"
#include"SHADER/LAMBERT.h"
#include"CONTAINER/CONTAINER.h"
#include"CONTAINER/BATCH.h"
#include"createSphere.h"
#include"view_proj.h"

void gmain()
{
    window(1920, 1080, full);
    hideCursor();
    angleMode(DEGREES);
    createProj();

    createSphere(30);
    CONTAINER* container = new CONTAINER("assets\\assets.txt");
    BATCH* sphere = container->batch("sphere");

    VECTOR lightPos(1,1,1);
    float ambient = 0.2f;
    COLOR diffuse(1,1,0);
    
    SHADER* shader = new LAMBERT;
    shader->setLightPosition(lightPos);
    shader->setLightAmbient(ambient);
    shader->setDiffuse(diffuse);
    //setRasterizerWire();
    
    MATRIX world;
    MATRIX scale;
    float scl = 0.05f;
    scale.scaling(scl, scl, scl);
    unsigned cnt = 0;
    float speed = 0.05f;
    float ofst = -0.01f;
    int sign[4][2] = { 1,1, -1,-1, -1,1, 1,-1 };
    while (notQuit)
    {
        clear(0);
        updateView(shader);
        float s = Sin(cnt * speed);
        for (int j = 0; j < 4; j++) {
            world.identity();
            for (int i = 0; i < 100; i++) {
                world.mulRotateZ(cnt * speed * 2);
                world.mulTranslate(
                    -s*sign[j][0], -s*sign[j][1], ofst * i);
                sphere->draw(shader, world * scale);
            }
        }
        cnt++;
    }

    delete container;
    delete shader;
}