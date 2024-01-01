#ifndef POINT_2D_HPP
#define POINT_2D_HPP

#include "types.hpp"

namespace wayround_i2p
{
namespace cctk
{
    struct Point2d
    {
        unsigned int x;
        unsigned int y;
    };

    struct Point2dStyle
    {
        ColorRGB color;
    };

} // namespace cctk
} // namespace wayround_i2p

#endif
