#ifndef CCTK_HPP
#define CCTK_HPP

#include "SystemI.hpp"

#include "KeyboardI.hpp"
#include "PointerI.hpp"

namespace wayround_i2p
{
namespace cctk
{

    class CCTK
    {
      public:
        static std::shared_ptr<CCTK> create();

        ~CCTK();

        int setSystem(std::shared_ptr<SystemI> sys);

        std::shared_ptr<WindowI> createWindow();

        std::shared_ptr<KeyboardI> getKeyboard();
        std::shared_ptr<PointerI>  getPointer();

      protected:
        CCTK();

      private:
        std::shared_ptr<SystemI> system;
    };

} // namespace cctk
} // namespace wayround_i2p

#endif
