#ifndef WIDGET_I_HPP
#define WIDGET_I_HPP

#include "interfaces.hpp"

namespace wayround_i2p::cctk
{

class WidgetI
{
  public:
    virtual void redraw(std::shared_ptr<DrawingSurfaceI> dc) = 0;

  protected:

  private:
};

} // namespace wayround_i2p::cctk

#endif
