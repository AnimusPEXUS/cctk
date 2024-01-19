#ifndef WAYROUND_I2P_20240117_175210_710388
#define WAYROUND_I2P_20240117_175210_710388

#include "types/ColorRGB.hpp"
#include "types/Point2d.hpp"

namespace wayround_i2p::cctk
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

} // namespace wayround_i2p::cctk

#endif
