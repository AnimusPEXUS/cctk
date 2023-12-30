#ifndef TYPES_HPP
#define TYPES_HPP

namespace wayround_i2p
{
namespace cctk
{

    struct ColorRGB
    {
        ColorField r;
        ColorField g;
        ColorField b;
    };

    struct Point2d
    {
        unsigned int x;
        unsigned int y;
    };

    struct Point2dStyle
    {
        ColorRGB color;
    };

    struct Line2d
    {
        Point2d point0;
        Point2d point1;
    };

    struct Line2dStyle
    {
        ColorRGB color;
    };

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
