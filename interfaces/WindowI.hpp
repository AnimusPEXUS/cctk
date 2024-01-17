#ifndef WAYROUND_I2P_20240117_175210_707951
#define WAYROUND_I2P_20240117_175210_707951

#include "types/ColorField.hpp"

#include "SystemI.hpp"

#include "KeyboardI.hpp"
#include "PointerI.hpp"

#include "types.hpp"

namespace wayround_i2p::cctk
{

class WindowI
{
  public:
    virtual void               setTitle(icu::UnicodeString val) = 0;
    virtual icu::UnicodeString getTitle()                       = 0;

    virtual void setPosition(Point2d val) = 0;

    virtual int show() = 0;
};

} // namespace wayround_i2p::cctk

#endif
