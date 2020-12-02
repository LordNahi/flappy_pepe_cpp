#pragma once

#include "olcPixelGameEngine.h"

class Pipe
{
public:
    Pipe(
        int x,
        int y,
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
    olc::vi2d position;

private:
    bool isActive;
    int killZone;
    int speed;
    int sMinY;
    int sMaxY;
    int sX;
};