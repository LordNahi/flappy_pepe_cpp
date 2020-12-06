#pragma once

#include "olcPixelGameEngine.h"
#include "rect.hpp"

using namespace Util;

class Pipe
{
public:
    Pipe(
        Geometry::Rectangle frame,
        int spawnMinY,
        int spawnMaxY,
        int spawnX,
        int pipeSpeed);

    bool GetIsActive()
    {
        return isActive;
    }
    void Kill();
    void Spawn();
    void Update();
    void GetFrame();
    olc::vi2d position;

private:
    bool isActive = false;
    int killZone = -50;
    int speed;
    int sMinY;
    int sMaxY;
    int sX;
    Geometry::Rectangle frame;
};