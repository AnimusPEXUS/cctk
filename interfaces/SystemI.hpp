#ifndef WAYROUND_I2P_20240125_022823_738266
#define WAYROUND_I2P_20240125_022823_738266

#include "WindowI.hpp"

namespace wayround_i2p::cctk
{

class SystemI
{
  public:
    virtual int init() = 0;
    virtual int run()  = 0;

    virtual std::shared_ptr<WindowI> createWindow() = 0;
};

} // namespace wayround_i2p::cctk

#endif
