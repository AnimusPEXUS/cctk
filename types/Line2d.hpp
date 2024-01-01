#ifndef LINE_2D_HPP
#define LINE_2D_HPP

#include "types.hpp"

namespace wayround_i2p
{
namespace cctk
{

    struct Line2d
    {
        Point2d point0;
        Point2d point1;
    };

    struct Line2dStyle
    {
        ColorRGB color;
    };

} // namespace cctk
} // namespace wayround_i2p

#endif
