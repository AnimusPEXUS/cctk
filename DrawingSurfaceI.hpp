#ifndef DRAWING_SURFACE_I_HPP
#define DRAWING_SURFACE_I_HPP

#include <cstdint>
#include <stdfloat>

namespace wayround_i2p
{
namespace CCTK
{

    enum ColorFieldDataType : unsigned char
    {
        u8
    };

    union ColorFieldData
    {
        std::uint8_t u8;
        // std::uint16_t   u16;
        // std::uint32_t   u32;
        // std::uint64_t   u64;
        // std::int8_t     s8;
        // std::int16_t    s16;
        // std::int32_t    s32;
        // std::int64_t    s64;
        // std::float16_t  f16;
        // std::float32_t  f32;
        // std::float64_t  f64;
        // std::float128_t f128;
    };

    struct ColorField
    {
        ColorFieldDataType type;
        ColorFieldData     data;

        void set_u8(std::uint8_t u8)
        {
            this->type    = ColorFieldDataType::u8;
            this->data.u8 = u8;
        }

        std::uint8_t get_u8()
        {
            return this->data.u8;
        }
    };

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

    class DrawingSurfaceI
    {
      public:
        virtual void point2d(
            Point2d      point,
            Point2dStyle point_style
        ) = 0;

        virtual void line2d(
            Line2d      line,
            Line2dStyle line_style
        ) = 0;

        virtual void rectangle2d(
            Rectangle2d rectangle,
            Rectangle2d rectangle_style
        ) = 0;

      protected:

      private:
    };

} // namespace CCTK
} // namespace wayround_i2p

#endif
