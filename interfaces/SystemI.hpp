#ifndef SYSTEM_I_HPP
#define SYSTEM_I_HPP

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
