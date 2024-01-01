
#include "CCTK.hpp"

namespace wayround_i2p
{
namespace cctk
{

    std::shared_ptr<CCTK> CCTK::create()
    {
        auto ret = std::shared_ptr<CCTK>(new CCTK());
        return ret;
    }

    CCTK::CCTK()
    {
    }

    CCTK::~CCTK()
    {
    }

    int CCTK::setSystem(std::shared_ptr<SystemI> sys)
    {
    }

    std::shared_ptr<WindowI> CCTK::createWindow()
    {
    }

    std::shared_ptr<KeyboardI> CCTK::getKeyboard()
    {
    }
    std::shared_ptr<PointerI> CCTK::getPointer()
    {
    }

} // namespace cctk
} // namespace wayround_i2p
