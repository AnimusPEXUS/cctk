#ifndef WAYROUND_I2P_20240117_175210_702645
#define WAYROUND_I2P_20240117_175210_702645

#include <memory>

#include <linux/input.h>

#include <wayland-client-protocol-extra.hpp>
#include <wayland-client-protocol.hpp>
#include <wayland-client.hpp>
#include <wayland-cursor.hpp>

#include "interfaces/SystemI.hpp"
#include "interfaces/WindowI.hpp"

#include "types/Point2d.hpp"

#include "utils/Property.hpp"

namespace wayround_i2p::cctk::system::linux_wayland_2024
{

class Window : public WindowI
{
  public:
    static std::shared_ptr<Window> create();

    ~Window();

    int show();

#include "_props_Window.hpp"

  protected:
    Window();

  private:
    icu::UnicodeString title;
    Point2d            position;

    Property<icu::UnicodeString> title_;
    Property<Point2d>            position_;
};

} // namespace wayround_i2p::cctk::system::linux_wayland_2024

#endif
