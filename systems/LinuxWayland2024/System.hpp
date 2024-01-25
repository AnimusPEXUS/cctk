#ifndef WAYROUND_I2P_20240125_022823_731674
#define WAYROUND_I2P_20240125_022823_731674

#include <memory>

#include <linux/input.h>

#include <wayland-client-protocol-extra.hpp>
#include <wayland-client-protocol.hpp>
#include <wayland-client.hpp>
#include <wayland-cursor.hpp>

#include <interfaces/SystemI.hpp>
#include <interfaces/WindowI.hpp>

#include <systems/LinuxWayland2024/Window.hpp>

namespace wayround_i2p::cctk::system::linux_wayland_2024
{

class Window;

class System : public SystemI
{
  public:
    static std::shared_ptr<System> create();

    ~System();

    int init() override;
    int run() override;

    std::shared_ptr<WindowI> createWindow() override;

  protected:
    System();

  private:
    friend Window;

    std::shared_ptr<System> own_ptr;

    // global objects
    wayland::display_t     display;
    wayland::registry_t    registry;
    wayland::compositor_t  compositor;
    wayland::shell_t       shell;
    wayland::xdg_wm_base_t xdg_wm_base;
    wayland::seat_t        seat;
    wayland::shm_t         shm;

    bool running;
    // bool has_pointer;
    // bool has_keyboard;

    int wayland_init();
};

} // namespace wayround_i2p::cctk::system::linux_wayland_2024

#endif
