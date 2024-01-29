#include "WaylandShmCtl.hpp"

namespace wayround_i2p::cctk::system::linux_wayland_2024
{

WaylandShmCtl::WaylandShmCtl(wayland::shm_t shm) :
    memfd(0)
{
    int err   = 0;
    this->shm = shm;

    err = applyInitCfg();
    if (err != 0)
    {
        throw std::runtime_error("couldn't apply config");
    }
}

int WaylandShmCtl::applyInitCfg()
{
    this->cfg = {
        .width            = 0,
        .height           = 0,
        .pixel_size_bytes = 4
    };

    /*
    // memfd size should be 0 at this point anyway
    err = memfd.set_size(0);
    if (err != 0)
    {
        return err;
    }
    */

    pool = shm.create_pool(
        memfd.get_fd(),
        0
    );

    active_pool_size = 0;

    return applyCfg(this->cfg);
}

int WaylandShmCtl::applyCfg(WaylandShmCtlCfg cfg)
{
    int err = 0;

    auto target_pool_size = calcMemSize(cfg, 2);
    bool grow             = target_pool_size > active_pool_size;

    if (!grow)
    {
        goto cb;
    }

mss:
    err = memfd.set_size(target_pool_size);
    if (err != 0)
    {
        return err;
    }

    if (!grow)
    {
        goto end;
    }

prs:

    // todo: use `try {} except {}` here ?
    pool.resize(target_pool_size);

    if (!grow)
    {
        goto mss;
    }

cb:
    for (int32_t i = 0; i != 2; i++)
    {
        // todo: error checking
        createBuffer(i, cfg.width, cfg.height, cfg.pixel_size_bytes);
    }

    if (!grow)
    {
        goto prs;
    }

end:

    active_pool_size = target_pool_size;
    this->cfg        = cfg;

    return 0;
}

int WaylandShmCtl::createBuffer(
    int32_t buffer_index,
    int32_t width,
    int32_t height,
    int32_t pixel_size_bytes
)
{
    int32_t stride      = calcStride(width, pixel_size_bytes);
    int32_t buffer_size = calcBufferSize(height, stride);
    int32_t offset      = calcBufferOffset(buffer_index, buffer_size);

    auto b = pool.create_buffer(
        offset, width, height, stride, wayland::shm_format::argb8888
    );
    buffers[buffer_index] = b;
    return 0;
}

int WaylandShmCtl::getMemFD_fd()
{
    return memfd.get_fd();
}

const void *WaylandShmCtl::getMemFD_mem()
{
    return memfd.get_mem();
}

wayland::shm_pool_t WaylandShmCtl::getPool()
{
    return pool;
}

wayland::buffer_t WaylandShmCtl::getBuffer(int index)
{
    return buffers[index];
}

void WaylandShmCtl::getWidthHeight(int32_t &width, int32_t &height)
{
    width  = cfg.width;
    height = cfg.height;
    return;
}

} // namespace wayround_i2p::cctk::system::linux_wayland_2024
