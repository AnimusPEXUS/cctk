#ifndef WAYROUND_I2P_20240117_175210_699604
#define WAYROUND_I2P_20240117_175210_699604

#include <memory>

#include <linux/input.h>

#include <wayland-client-protocol-extra.hpp>
#include <wayland-client-protocol.hpp>
#include <wayland-client.hpp>
#include <wayland-cursor.hpp>

#include <interfaces/SystemI.hpp>

namespace wayround_i2p::cctk::system::linux_wayland_2024
{

class System : public SystemI
{
  public:
    static std::shared_ptr<System> create();

    ~System();

    int init() override;
    int run() override;

    std::shared_ptr<WindowI> createWindow() override;

    #include "_props_System.hpp"

  protected:
    System();

  private:
    // global objects
    wayland::display_t     display;
    wayland::registry_t    registry;
    wayland::compositor_t  compositor;
    wayland::shell_t       shell;
    wayland::xdg_wm_base_t xdg_wm_base;
    wayland::seat_t        seat;
    wayland::shm_t         shm;

    // local objects
    wayland::surface_t       surface;
    wayland::shell_surface_t shell_surface;
    wayland::xdg_surface_t   xdg_surface;
    wayland::xdg_toplevel_t  xdg_toplevel;
    wayland::pointer_t       pointer;
    wayland::keyboard_t      keyboard;
    wayland::callback_t      frame_cb;
    wayland::cursor_image_t  cursor_image;
    wayland::buffer_t        cursor_buffer;
    wayland::surface_t       cursor_surface;

    bool running;
    bool has_pointer;
    bool has_keyboard;

    int wayland_init();
};

} // namespace wayround_i2p::cctk::system::linux_wayland_2024

#endif
