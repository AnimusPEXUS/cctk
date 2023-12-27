#ifndef WIDGET_I_HPP
#define WIDGET_I_HPP

namespace wayround_i2p
{
namespace CCTK
{

    class WidgetI
    {
      public:
        void redraw(std::shared_ptr<DrawingSurfaceI> dc) abstract;

      protected:

      private:
    };

} // namespace CCTK
} // namespace wayround_i2p

#endif
