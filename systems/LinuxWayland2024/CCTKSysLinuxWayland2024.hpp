#ifndef CCTK_SYS_LINUX_WAYLAND_2024_HPP
#define CCTK_SYS_LINUX_WAYLAND_2024_HPP

#include <memory>

#include <interfaces/SystemI.hpp>

namespace wayround_i2p
{
namespace cctk
{

    class CCTKSysLinuxWayland2024 : public SystemI
    {
      public:
        static std::shared_ptr<CCTKSysLinuxWayland2024> create();

        ~CCTKSysLinuxWayland2024();

      protected:
        CCTKSysLinuxWayland2024();

      private:
    };

} // namespace cctk
} // namespace wayround_i2p

#endif
