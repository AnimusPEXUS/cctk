#ifndef RECTANGLE_2D_HPP
#define RECTANGLE_2D_HPP

#include "types.hpp"

namespace wayround_i2p
{
namespace cctk
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

} // namespace cctk
} // namespace wayround_i2p

#endif
