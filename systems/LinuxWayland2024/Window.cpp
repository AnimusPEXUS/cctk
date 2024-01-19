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
}

Window::~Window()
{
}

int Window::show()
{
    return 0;
}

} // namespace wayround_i2p::cctk::system::linux_wayland_2024
