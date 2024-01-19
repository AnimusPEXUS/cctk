#include "systems/LinuxWayland2024/Window.hpp"

namespace wayround_i2p::cctk::system::linux_wayland_2024
{

std::shared_ptr<Window> Window::create()
{
    auto ret = std::shared_ptr<Window>(new Window());
    return ret;
}

Window::Window() :
    title_(Property<icu::UnicodeString>::create(title)),
    position_(Property<Point2d>::create(position))
{
}

Window::~Window()
{
}

int Window::show()
{
    return 0;
}

} // namespace wayround_i2p::cctk::system::linux_wayland_2024
