
#include <iostream>

#include "systems/LinuxWayland2024/System.hpp"

namespace wayround_i2p::cctk::system::linux_wayland_2024
{

std::shared_ptr<System> System::create()
{
    auto ret = std::shared_ptr<System>(
        new System()
    );

    ret->own_ptr = ret;

    return ret;
}

System::System()
{
}

System::~System()
{
}

int System::init()
{
    wayland_init();
    return 0;
}

int System::run()
{
    running = true;
    while (running)
    {
        display.dispatch();
    }
    std::cout << "run loop exit" << std::endl;
    return 0;
}

int System::wayland_init()
{

    registry = display.get_registry();
    registry.on_global() =
        [&](
            uint32_t           name,
            const std::string &interface,
            uint32_t           version
        )
    {
        if (interface == wayland::compositor_t::interface_name)
        {
            registry.bind(name, compositor, version);
        }
        else if (interface == wayland::shell_t::interface_name)
        {
            registry.bind(name, shell, version);
        }
        else if (interface == wayland::xdg_wm_base_t::interface_name)
        {
            registry.bind(name, xdg_wm_base, version);
        }
        else if (interface == wayland::seat_t::interface_name)
        {
            registry.bind(name, seat, version);
        }
        else if (interface == wayland::shm_t::interface_name)
        {
            registry.bind(name, shm, version);
        }
    };
    display.roundtrip();

    if (!xdg_wm_base)
    {
        throw std::runtime_error("no xdg_wm_base");
    }

    xdg_wm_base.on_ping() =
        [&](uint32_t serial)
    {
        xdg_wm_base.pong(serial);
    };

    return 0;
}

std::shared_ptr<WindowI> System::createWindow()
{
    auto ret = Window::create(own_ptr);
    return ret;
}

} // namespace wayround_i2p::cctk::system::linux_wayland_2024
