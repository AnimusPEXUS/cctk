
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

    int CCTK::applyCmdLineArgs(int argc, char **args)
    {
        return 0;
    }

    int CCTK::init()
    {
        return 0;
    }

    int CCTK::run()
    {
        return 0;
    }

    int CCTK::setSystem(std::shared_ptr<SystemI> sys)
    {
        return 0;
    }

    std::shared_ptr<WindowI> CCTK::createWindow()
    {
        return nullptr;
    }

    std::shared_ptr<KeyboardI> CCTK::getKeyboard()
    {
        return nullptr;
    }

    std::shared_ptr<PointerI> CCTK::getPointer()
    {
        return nullptr;
    }

    std::weak_ptr<sigc::signal<void()>> CCTK::get_sigAfterStart()
    {
        return sigAfterStart;
    }

} // namespace cctk
} // namespace wayround_i2p
