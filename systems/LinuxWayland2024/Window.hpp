#ifndef WAYROUND_I2P_20240127_063832_812664
#define WAYROUND_I2P_20240127_063832_812664

#include <memory>

#include <linux/input.h>
#include <unicode/unistr.h>

#include <wayland-client-protocol-extra.hpp>
#include <wayland-client-protocol.hpp>
#include <wayland-client.hpp>
#include <wayland-cursor.hpp>

#include "interfaces/SystemI.hpp"
#include "interfaces/WindowI.hpp"

#include "types/Point2d.hpp"

// #include "utils/MemFD.hpp"
#include "utils/Property.hpp"

#include "systems/LinuxWayland2024/System.hpp"
#include "systems/LinuxWayland2024/WaylandShmCtl.hpp"

namespace wayround_i2p::cctk::system::linux_wayland_2024
{

struct WindowVideoConfig
{
    int32_t width;
    int32_t height;
};

class System;

class Window : public WindowI
{
  public:
    static std::shared_ptr<Window> create(std::shared_ptr<System>);

    ~Window();

    int show();

#include "_props_Window.hpp"

  protected:
    Window(std::shared_ptr<System>);

  private:
    std::shared_ptr<Window> own_ptr;
    std::shared_ptr<System> sys;

    icu::UnicodeString title;
    Point2d            position;

    Property<icu::UnicodeString> title_;
    Property<Point2d>            position_;

    // local objects
    wayland::surface_t       surface;
    wayland::shell_surface_t shell_surface;
    wayland::xdg_surface_t   xdg_surface;
    wayland::xdg_toplevel_t  xdg_toplevel;
    // wayland::pointer_t       pointer;
    // wayland::keyboard_t      keyboard;
    wayland::callback_t      frame_cb;
    // wayland::cursor_image_t  cursor_image;
    // wayland::buffer_t        cursor_buffer;
    // wayland::surface_t       cursor_surface;

    WindowVideoConfig video_cfg;

    WaylandShmCtl wsc;

    int video_reconfig(WindowVideoConfig cfg);
};

} // namespace wayround_i2p::cctk::system::linux_wayland_2024

#endif
