#ifndef WAYROUND_I2P_20240117_175210_702645
#define WAYROUND_I2P_20240117_175210_702645

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

#include "utils/Property.hpp"

#include <systems/LinuxWayland2024/System.hpp>

namespace wayround_i2p::cctk::system::linux_wayland_2024
{

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

    icu::UnicodeString          title;
    wayround_i2p::cctk::Point2d position;

    wayround_i2p::cctk::Property<icu::UnicodeString>          title_;
    wayround_i2p::cctk::Property<wayround_i2p::cctk::Point2d> position_;
};

} // namespace wayround_i2p::cctk::system::linux_wayland_2024

#endif
