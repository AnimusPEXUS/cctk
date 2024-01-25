#include <utils/MemFD.hpp>

namespace wayround_i2p::cctk
{

MemFD::MemFD(size_t size)
{
    if (size < 0)
    {
        throw std::runtime_error("size < 0");
    }

    set_size(size)
}

MemFD::~MemFD()
{
}

void MemFD::set_size(size_t new_size)
{
    fd = memfd_create("(fixed nonrandom name)", 0);
    if (fd < 0)
    {
        throw std::runtime_error("memfd_create failed.");
    }

    // set size
    if (ftruncate(fd, new_size) < 0)
    {
        throw std::runtime_error("ftruncate failed.");
    }

    size = new_size;
}

} // namespace wayround_i2p::cctk
