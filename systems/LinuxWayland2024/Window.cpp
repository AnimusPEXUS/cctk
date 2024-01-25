#include "systems/LinuxWayland2024/Window.hpp"

namespace wayround_i2p::cctk::system::linux_wayland_2024
{

std::shared_ptr<Window> Window::create(std::shared_ptr<System> sys)
{
    auto ret     = std::shared_ptr<Window>(new Window(sys));
    ret->own_ptr = ret;
    return ret;
}

Window::Window(std::shared_ptr<System> sys) :
    title_(Property<icu::UnicodeString>::create(title)),
    position_(Property<wayround_i2p::cctk::Point2d>::create(position))
{
    this->sys = sys;

    surface = this->sys->compositor.create_surface();

    if (!this->sys->xdg_wm_base)
    {
        throw std::runtime_error("no xdg_wm_base");
    }

    xdg_surface = this->sys->xdg_wm_base.get_xdg_surface(surface);

    xdg_surface.on_configure() =
        [&](uint32_t serial)
    {
        xdg_surface.ack_configure(serial);
    };

    xdg_toplevel = xdg_surface.get_toplevel();
    xdg_toplevel.set_title("Window");

    surface.commit();

    // this->sys->display.roundtrip();
}

Window::~Window()
{
}

int Window::show()
{
    return 0;
}

} // namespace wayround_i2p::cctk::system::linux_wayland_2024
