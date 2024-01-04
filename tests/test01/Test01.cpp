#include <utility>

#include "CCTK.hpp"

#include "systems/LinuxWayland2024/CCTKSysLinuxWayland2024.hpp"

int main(int argc, char **args)
{

    auto cctk = wayround_i2p::cctk::CCTK::create();

    cctk->applyCmdLineArgs(argc, args);

    auto sys = wayround_i2p::cctk::CCTKSysLinuxWayland2024::create();

    cctk->setSystem(sys);

    cctk->init();

    {
        auto x = cctk->get_sigAfterStart().lock();
        x->connect(
            [cctk]()
            {
                auto win = cctk->createWindow();
                win->show();
            }
        );
    }

    return cctk->run();
}
