#include "libOne.h"
#include"SHADER/LAMBERT.h"

extern MATRIX gView{ 0 };
extern MATRIX gProj{ 0 };

static float angX = 0;
static float angY = 0;
static float radius = 5.0f;
static VECTOR camPos, lookat(0, 0, 0), up(0, 1, 0);

void createProj()
{
    gProj.pers(45, width / height, 0.01f, 50.0f);
}
void updateView(SHADER* shader)
{
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
    gView.camera(camPos, lookat, up);

    shader->setProjView(gProj * gView);
}