#ifndef DRAWING_SURFACE_I_HPP
#define DRAWING_SURFACE_I_HPP

#include "interfaces.hpp"

#include "types/types.hpp"

namespace wayround_i2p
{
namespace cctk
{

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

} // namespace cctk
} // namespace wayround_i2p

#endif