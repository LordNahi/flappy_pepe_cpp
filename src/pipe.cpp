#include "util.hpp"
#include "pipe.hpp"
#include "rect.hpp"

Pipe::Pipe(
    Geometry::Rectangle frame,
    int spawnMinY,
    int spawnMaxY,
    int spawnX,
    int pipeSpeed)
{
    position.x = frame.x;
    position.y = frame.y;
    sMinY = spawnMinY;
    sMaxY = spawnMaxY;
    sX = spawnX;
    speed = pipeSpeed;
    frame = frame;
}

void Pipe::Spawn()
{
    isActive = true;
    position.x = sX;
    position.y = Util::Math::randRange(sMinY, sMaxY);

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

    frame.x = position.x;
    frame.y = position.y;
}
