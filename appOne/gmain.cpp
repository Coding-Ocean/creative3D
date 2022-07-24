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
    float ambient = 1.0f;
    COLOR diffuse = hsv2rgb(60, 255, 255, 255);
    
    SHADER* shader = new LAMBERT;
    shader->setLightPosition(lightPos);
    shader->setLightAmbient(ambient);
    shader->setDiffuse(diffuse);
    setRasterizerWire();
    
    MATRIX world;
    MATRIX scale;
    float scl = 0.05f;
    scale.scaling(scl,scl,scl);

    while (notQuit)
    {
        clear(0);
        updateView(shader);
        world.identity();
        sphere->draw(shader, world);
    }

    delete container;
    delete shader;
}