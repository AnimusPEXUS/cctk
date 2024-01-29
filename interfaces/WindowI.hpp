#ifndef WAYROUND_I2P_20240127_063832_821162
#define WAYROUND_I2P_20240127_063832_821162

#include "types/ColorField.hpp"

#include "SystemI.hpp"

#include "KeyboardI.hpp"
#include "PointerI.hpp"

namespace wayround_i2p::cctk
{

class WindowI
{
  public:
    virtual bool               p_Title_set(const icu::UnicodeString &val) = 0;
    virtual icu::UnicodeString p_Title_get()                              = 0;
    virtual bool               p_Position_set(const Point2d &val)         = 0;
    virtual Point2d            p_Position_get()                           = 0;

    virtual int show() = 0;
};

} // namespace wayround_i2p::cctk

#endif
