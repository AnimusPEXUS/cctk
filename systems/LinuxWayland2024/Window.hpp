#ifndef WAYROUND_I2P_20240109_203545_242574
#define WAYROUND_I2P_20240109_203545_242574

#include <memory>

#include <linux/input.h>

#include <wayland-client-protocol-extra.hpp>
#include <wayland-client-protocol.hpp>
#include <wayland-client.hpp>
#include <wayland-cursor.hpp>

#include <interfaces/SystemI.hpp>

namespace wayround_i2p::cctk::system::linux_wayland_2024
{

class Window : public WindowI
{
  public:
    static std::shared_ptr<Window> create();

    ~Window();

    int init() override;
    int run() override;

    std::shared_ptr<WindowI> createWindow() override;

  protected:
    Window();
};

} // namespace wayround_i2p::cctk::system::linux_wayland_2024

#endif
