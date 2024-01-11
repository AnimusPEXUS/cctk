#include "systems/LinuxWayland2024/Window.hpp"

namespace wayround_i2p::cctk::system::linux_wayland_2024
{

std::shared_ptr<Window> Window::create()
{
    auto ret = std::shared_ptr<Window>(new Window());
    return ret;
}

Window::Window()
{
}

Window::~Window()
{
}

} // namespace wayround_i2p::cctk::system::linux_wayland_2024
