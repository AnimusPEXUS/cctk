#ifndef WAYROUND_I2P_20240127_063832_811906
#define WAYROUND_I2P_20240127_063832_811906

#include <cstdint>

#include <wayland-client-protocol-extra.hpp>
#include <wayland-client-protocol.hpp>
#include <wayland-client.hpp>
#include <wayland-cursor.hpp>

#include "utils/MemFD.hpp"

namespace wayround_i2p::cctk::system::linux_wayland_2024
{

struct WaylandShmCtlCfg
{
    int32_t width;
    int32_t height;
    int32_t pixel_size_bytes;
    // int32_t buffer_count;
};

inline int32_t calcStride(
    int32_t width,
    int32_t pixel_size_bytes
)
{
    return width * pixel_size_bytes;
}

inline int32_t calcBufferOffset(
    int32_t buffer_index,
    int32_t buffer_size
)
{
    return buffer_index * buffer_size;
}

inline int32_t calcBufferSize(
    int32_t width,
    int32_t height,
    int32_t pixel_size_bytes
)
{
    return calcStride(width, pixel_size_bytes) * height;
}

inline int32_t calcBufferSize(
    int32_t height,
    int32_t stride
)
{
    return height * stride;
}

inline int32_t calcMemSize(
    int32_t width,
    int32_t height,
    int32_t pixel_size_bytes,
    int32_t buffer_count
)
{
    return calcBufferSize(width, height, pixel_size_bytes) * buffer_count;
}

inline int32_t calcMemSize(
    WaylandShmCtlCfg cfg,
    int32_t          buffer_count
)
{
    return calcMemSize(
        cfg.width,
        cfg.height,
        cfg.pixel_size_bytes,
        buffer_count
    );
}

/*
class WaylandShmBuffCtl
{
  public:
    WaylandShmBuffCtl(
        int                            index,
        std::function<void(int index)> cb_on_release
    );

  private:
    int                            index;
    std::function<void(int index)> cb_on_release;
}
*/

class WaylandShmCtl
{
  public:
    WaylandShmCtl(wayland::shm_t shm);

    int applyCfg(WaylandShmCtlCfg cfg);

    int                 getMemFD_fd();
    wayland::shm_pool_t getPool();
    wayland::buffer_t   getBuffer(int index);

    // gets corresponding values from config
    void getWidthHeight(int32_t &width, int32_t &height);

  private:
    wayland::shm_t shm;

    WaylandShmCtlCfg cfg;

    MemFD<int32_t>      memfd;
    int32_t             active_pool_size;
    wayland::shm_pool_t pool;
    wayland::buffer_t   buffers[2];

    int applyInitCfg();

    int createBuffer(
        int32_t buffer_index,
        int32_t width,
        int32_t height,
        int32_t pixel_size_bytes
    );
};

} // namespace wayround_i2p::cctk::system::linux_wayland_2024

#endif
