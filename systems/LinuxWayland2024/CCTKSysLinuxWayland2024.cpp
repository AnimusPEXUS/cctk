
#include "CCTKSysLinuxWayland2024.hpp"

namespace wayround_i2p
{
namespace cctk
{

    std::shared_ptr<CCTKSysLinuxWayland2024> CCTKSysLinuxWayland2024::create()
    {
        auto ret = std::shared_ptr<CCTKSysLinuxWayland2024>(
            new CCTKSysLinuxWayland2024()
        );

        return ret;
    }

    CCTKSysLinuxWayland2024::CCTKSysLinuxWayland2024()
    {
    }

    CCTKSysLinuxWayland2024::~CCTKSysLinuxWayland2024()
    {
    }

    int CCTKSysLinuxWayland2024::init()
    {
        return 0;
    }

} // namespace cctk
} // namespace wayround_i2p
