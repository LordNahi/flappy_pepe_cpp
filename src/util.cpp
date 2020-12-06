#include <random>
#include "rect.hpp"

namespace Util::Geometry
{
    bool overlaps(Rectangle &rA, Rectangle &rB)
    {
        return rA.x < rB.w && rA.w > rB.x && rA.y < rB.h && rA.h < rB.y;
    }
} // namespace Util::Geometry

namespace Util::Math
{
    int randRange(int min, int max)
    {
        // Will this cause a memory leak if I call this func a million times ...
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(min, max);

        return distrib(gen);
    };
} // namespace Util::Math