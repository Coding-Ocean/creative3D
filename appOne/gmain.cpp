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
    createSphere(60);
    CONTAINER* cont = new CONTAINER("assets\\assets.txt");
    BATCH* batch = cont->batch("sphere");

    VECTOR lightPos(1,1,1);
    float ambient=0.3f;
    COLOR diffuse = hsv2rgb(180, 0, 255, 255);

    float ofstZ = -0.0005f;
    unsigned long long cnt = 0;
    int sign[4][2] = { 1,1,1,-1,-1,-1,-1,1 };
    float angSpeed = 0.05f;
    float radius = 0.15f;

    MATRIX world2;
    MATRIX world;
    float scl = 0.01f;
    world.scaling(scl,scl,scl);
    createProj();

    SHADER* shader = new LAMBERT;
    shader->setLightPosition(lightPos);
    shader->setLightAmbient(ambient);
    shader->setDiffuse(diffuse);
    //setRasterizerWire();
    
    while (notQuit)
    {
        clear(0);
        updateView();
        shader->setProjView(gProj * gView);

        if (isPress(KEY_W))ofstZ -= 0.000001f;
        if (isPress(KEY_S))ofstZ += 0.000001f;
        float s = Sin(cnt * angSpeed) * radius;
        for (int j = 0; j < 4; j++) {
            world2.identity();
            for (int i = 0; i < 120; i++) {
                world2.mulRotateZ(cnt * angSpeed * 2);
                world2.mulTranslate(
                    s * sign[j][0], 
                    s * sign[j][1], 
                    i * ofstZ
                );
                batch->draw(shader, world2 * world);
            }
        }
        cnt += 1;
    }

    delete container;
    delete shader;
}