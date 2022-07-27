#include "libOne.h"
#include"SHADER/LAMBERT.h"

extern MATRIX gView{ 0 };
extern MATRIX gProj{ 0 };

static float angX = 15;
static float angY = -45;
static float radius = 5.0f;
static VECTOR camPos, lookat(0, 0, 0), up(0, 1, 0);
static int sw = 1;

void createProj()
{
    gProj.pers(45, width / height, 0.01f, 50.0f);
}
void updateView(SHADER* shader)
{
    if (isTrigger(KEY_C)) {
        ++sw %= 5; angY = 135;
    }
    if (sw == 1)angY = -45;
    if (sw == 2)angY = 45;
    if (sw == 3)angY = -135;
    if (isPress(KEY_I))angX += 0.3f;
    if (isPress(KEY_K))angX -= 0.3f;
    if (isPress(KEY_J))angY -= 0.3f;
    if (isPress(KEY_L))angY += 0.3f;
    if (isPress(KEY_U))radius -= 0.03f;
    if (isPress(KEY_O))radius += 0.03f;
    if (angX >=  89.5)angX =  89.5f;
    if (angX <= -89.5)angX = -89.5f;
    camPos.x = Sin(angY) * Cos(angX) * radius;
    camPos.y = Sin(angX)* radius;
    camPos.z = Cos(angY) * Cos(angX) * radius;
    //up.y = Cos(angX);
    //up.z = -Sin(angX);
    gView.camera(camPos, lookat, up);

    shader->setProjView(gProj * gView);
}