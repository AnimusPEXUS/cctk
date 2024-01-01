#ifndef WINDOW_I_HPP
#define WINDOW_I_HPP

#include "types/ColorField.hpp"

#include "SystemI.hpp"

#include "KeyboardI.hpp"
#include "PointerI.hpp"

#include "types.hpp"

namespace wayround_i2p
{
namespace cctk
{

    class WindowI
    {
      public:
        virtual void               setTitle(icu::UnicodeString val) = 0;
        virtual icu::UnicodeString getTitle()                       = 0;

        virtual void setPosition(Point2d val) = 0;

      protected:

      private:
    };

} // namespace cctk
} // namespace wayround_i2p

#endif
