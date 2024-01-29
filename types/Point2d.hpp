#ifndef WAYROUND_I2P_20240127_063832_823484
#define WAYROUND_I2P_20240127_063832_823484

#include "types/ColorRGB.hpp"

namespace wayround_i2p::cctk
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

} // namespace wayround_i2p::cctk

#endif
