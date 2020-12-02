#include "utilities.hpp"
#include "pipe.hpp"

Pipe::Pipe(
    int x,
    int y,
    int spawnMinY,
    int spawnMaxY,
    int spawnX,
    int pipeSpeed)
{
    position.x = x;
    position.y = y;
    sMinY = spawnMinY;
    sMaxY = spawnMaxY;
    sX = spawnX;
    speed = pipeSpeed;

    killZone = -50;
    isActive = false;
}

void Pipe::Spawn()
{
    isActive = true;
    position.x = sX;
    position.y = randRange(sMinY, sMaxY);

    std::cout << "Pipe Spawned" << std::endl;
};

void Pipe::Kill()
{
    isActive = false;

    std::cout << "Pipe Killed" << std::endl;
}

void Pipe::Update()
{
    position.x -= speed;
    if (position.x < killZone)
        Kill();

    std::cout << "Pipe new posX: " << position.x << std::endl;
}
