#include <utility>

#include "CCTK.hpp"

#include "systems/LinuxWayland2024/System.hpp"

int main(int argc, char **args)
{

    auto cctk = wayround_i2p::cctk::CCTK::create();

    cctk->applyCmdLineArgs(argc, args);

    auto sys = wayround_i2p::cctk::system::linux_wayland_2024::System::create();

    cctk->setSystem(sys);

    cctk->init();

    std::shared_ptr<wayround_i2p::cctk::WindowI> win;

    {
        auto x = cctk->get_sigAfterStart().lock();
        if (x)
        {
            x->connect(
                [cctk, &win]()
                {
                    win = cctk->createWindow();
                    win->show();
                }
            );
        }
    }

    return cctk->run();
}
