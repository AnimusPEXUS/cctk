#ifndef WAYROUND_I2P_20240127_063832_822645
#define WAYROUND_I2P_20240127_063832_822645

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
