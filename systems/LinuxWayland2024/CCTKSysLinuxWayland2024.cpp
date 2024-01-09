

#include "CCTKSysLinuxWayland2024.hpp"

namespace wayround_i2p
{
namespace cctk
{

    std::shared_ptr<CCTKSysLinuxWayland2024> CCTKSysLinuxWayland2024::create()
    {
        auto ret = std::shared_ptr<CCTKSysLinuxWayland2024>(
            new CCTKSysLinuxWayland2024()
        );

        return ret;
    }

    CCTKSysLinuxWayland2024::CCTKSysLinuxWayland2024()
    {
    }

    CCTKSysLinuxWayland2024::~CCTKSysLinuxWayland2024()
    {
    }

    int CCTKSysLinuxWayland2024::init()
    {
        wayland_init();
        return 0;
    }

    int CCTKSysLinuxWayland2024::run()
    {
        running = true;
        while (running)
        {
            display.dispatch();
        }
        return 0;
    }

    int CCTKSysLinuxWayland2024::wayland_init()
    {
        // retrieve global objects
        registry = display.get_registry();
        registry.on_global() =
            [&](
                uint32_t           name,
                const std::string &interface,
                uint32_t           version
            )
        {
            if (interface == wayland::compositor_t::interface_name)
                registry.bind(name, compositor, version);
            else if (interface == wayland::shell_t::interface_name)
                registry.bind(name, shell, version);
            else if (interface == wayland::xdg_wm_base_t::interface_name)
                registry.bind(name, xdg_wm_base, version);
            else if (interface == wayland::seat_t::interface_name)
                registry.bind(name, seat, version);
            else if (interface == wayland::shm_t::interface_name)
                registry.bind(name, shm, version);
        };
        display.roundtrip();

        seat.on_capabilities() = [&](const wayland::seat_capability &capability)
        {
            has_keyboard = capability & wayland::seat_capability::keyboard;
            has_pointer  = capability & wayland::seat_capability::pointer;
        };

        // create a surface
        surface = compositor.create_surface();

        // create a shell surface
        if (xdg_wm_base)
        {
            xdg_wm_base.on_ping() = [&](uint32_t serial)
            { xdg_wm_base.pong(serial); };
            xdg_surface                = xdg_wm_base.get_xdg_surface(surface);
            xdg_surface.on_configure() = [&](uint32_t serial)
            { xdg_surface.ack_configure(serial); };
            xdg_toplevel = xdg_surface.get_toplevel();
            xdg_toplevel.set_title("Window");
            xdg_toplevel.on_close() = [&]()
            { running = false; };
        }
        else
        {
            shell_surface           = shell.get_shell_surface(surface);
            shell_surface.on_ping() = [&](uint32_t serial)
            { shell_surface.pong(serial); };
            shell_surface.set_title("Window");
            shell_surface.set_toplevel();
        }
        surface.commit();

        display.roundtrip();

        // Get input devices
        if (!has_keyboard)
            throw std::runtime_error("No keyboard found.");
        if (!has_pointer)
            throw std::runtime_error("No pointer found.");

        pointer  = seat.get_pointer();
        keyboard = seat.get_keyboard();

        // load cursor theme
        wayland::cursor_theme_t cursor_theme = wayland::cursor_theme_t("default", 16, shm);
        wayland::cursor_t       cursor       = cursor_theme.get_cursor("cross");
        cursor_image                         = cursor.image(0);
        cursor_buffer                        = cursor_image.get_buffer();

        // create cursor surface
        cursor_surface = compositor.create_surface();

        // draw cursor
        pointer.on_enter() =
            [&](
                uint32_t serial,
                const wayland::surface_t & /*unused*/,
                int32_t /*unused*/,
                int32_t /*unused*/
            )
        {
            cursor_surface.attach(cursor_buffer, 0, 0);
            cursor_surface.damage(0, 0, cursor_image.width(), cursor_image.height());
            cursor_surface.commit();
            pointer.set_cursor(serial, cursor_surface, 0, 0);
        };

        // window movement
        pointer.on_button() =
            [&](
                uint32_t serial,
                uint32_t /*unused*/,
                uint32_t                      button,
                wayland::pointer_button_state state
            )
        {
            if (
                button == BTN_LEFT
                && state == wayland::pointer_button_state::pressed
            )
            {
                if (xdg_toplevel)
                    xdg_toplevel.move(seat, serial);
                else
                    shell_surface.move(seat, serial);
            }
        };

        // press 'q' to exit
        keyboard.on_key() =
            [&](
                uint32_t /*unused*/,
                uint32_t /*unused*/,
                uint32_t                    key,
                wayland::keyboard_key_state state
            )
        {
            if (
                key == KEY_Q
                && state == wayland::keyboard_key_state::pressed
            )
                running = false;
        };

        return 0;
    }

} // namespace cctk
} // namespace wayround_i2p
