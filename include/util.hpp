#include "rect.hpp"

namespace Util::Geometry
{
    // Takes two rectangles and returns whether or not they're overlapping
    bool overlaps(Rectangle &rA, Rectangle &rB);
} // namespace Util::Geometry

namespace Util::Math
{
    // Takes a min and max value and returns an integer within that range
    int randRange(int min, int max);
} // namespace Util::Math