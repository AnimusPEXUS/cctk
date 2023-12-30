#ifndef WIDGET_I_HPP
#define WIDGET_I_HPP

namespace wayround_i2p
{
namespace cctk
{

    class WidgetI
    {
      public:
        void redraw(std::shared_ptr<DrawingSurfaceI> dc) abstract;

      protected:

      private:
    };

} // namespace cctk
} // namespace wayround_i2p

#endif
