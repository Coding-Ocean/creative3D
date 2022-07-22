#include"libOne.h"
#include"SHADER/LAMBERT.h"
#include"CONTAINER/CONTAINER.h"
#include"CONTAINER/BATCH.h"
COLOR hsv2rgb(float h, float s, float v, float a);
void createSphere();

//ƒJƒƒ‰
float angX = 0;
float angY = 0;
float radius = 0.5f;
VECTOR camPos, lookat(0, 0, 0), up(0, 1, 0);
MATRIX view;
void updateView() {
    if (isPress(KEY_I))angX += 0.3f;
    if (isPress(KEY_K))angX -= 0.3f;
    if (isPress(KEY_J))angY -= 0.3f;
    if (isPress(KEY_L))angY += 0.3f;
    if (isPress(KEY_U))radius -= 0.003f;
    if (isPress(KEY_O))radius += 0.003f;
    camPos.x = Sin(angY) * Cos(angX) * radius;
    camPos.y = Sin(angX) * radius;
    camPos.z = Cos(angY) * Cos(angX) * radius;
    up.y = Cos(angX);
    up.z = -Sin(angX);
    view.camera(camPos, lookat, up);
}
void gmain()
{
    window(1920, 1080, full);
    hideCursor();
    angleMode(DEGREES);
    createSphere();
    CONTAINER* container = new CONTAINER("assets\\assets.txt");
    BATCH* batch = container->batch("sphere");

    MATRIX world, proj;
    VECTOR lightPos;
    float ambient;
    COLOR diffuse;

    proj.pers(45, width / height, 0.01f, 5.0f);
    lightPos.set(1, 1, 1);
    ambient = 0.8f;
    diffuse = hsv2rgb(0.0f, 0, 255, 255);
    unsigned long long cnt = 0;
    float ofstZ = -0.0005f;
    int sign[4][2] = { 1,1,1,-1,-1,-1,-1,1 };
    float speed = 0.05f;
    float scl = 0.01f;
    MATRIX scale;
    scale.scaling(scl,scl,scl);
    SHADER* shader = new LAMBERT;
    {
        shader->setLightPosition(lightPos);
        shader->setLightAmbient(ambient);
        shader->setDiffuse(diffuse);
        setRasterizerCullBack();
        setRasterizerWire();
    }
    while (notQuit)
    {
        clear(0);
        updateView();
        shader->setProjView(proj * view);

        if (isPress(KEY_W))ofstZ -= 0.000001f;
        if (isPress(KEY_S))ofstZ += 0.000001f;
        float s = Sin(cnt * speed) * 0.15f;
        for (int j = 0; j < 4; j++) {
            world.identity();
            for (int i = 0; i < 120; i++) {
                world.mulRotateZ(cnt * speed * 2);
                world.mulTranslate(s * sign[j][0], s * sign[j][1], i * ofstZ);
                batch->draw(shader, world*scale);
            }
        }
        cnt += 1;
    }

    delete container;
    delete shader;
}