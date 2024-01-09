#ifndef WAYROUND_I2P_20240109_203545_247136
#define WAYROUND_I2P_20240109_203545_247136

#include "types.hpp"

namespace wayround_i2p::cctk
{

struct Rectangle2d
{
    Point2d top_left;
    Point2d bottom_right;

    bool is_valid();

    unsigned int calc_width();
    unsigned int calc_height();
};

struct Rectangle2dStyle
{
};

} // namespace wayround_i2p::cctk

#endif
