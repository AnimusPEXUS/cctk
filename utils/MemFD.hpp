#ifndef WAYROUND_I2P_20240127_063832_817125
#define WAYROUND_I2P_20240127_063832_817125

#include <stdexcept>

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

namespace wayround_i2p::cctk
{

template <class T>
class MemFD
{
  public:
    MemFD(T size);

    ~MemFD();

    int    set_size(T new_size);
    size_t get_size();

    int get_fd();

    const void *get_mem();

  private:
    T     size = 0;
    int   fd   = 0;
    void *mem;
};

// todo: all this, probably, requires better error handling

template <class T>
MemFD<T>::MemFD(T size)
{
    if (size < 0)
    {
        throw std::runtime_error("size < 0");
    }

    fd = memfd_create("(fixed non-random name)", 0);
    if (fd < 0)
    {
        throw std::runtime_error("memfd_create failed");
    }

    mem = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mem == MAP_FAILED)
    {
        throw std::runtime_error("mmap error");
    }

    if (set_size(size) != 0)
    {
        throw std::runtime_error("couldn't setup initial memory");
    }
}

template <class T>
MemFD<T>::~MemFD()
{
    if (fd != 0)
    {
        if (munmap(mem, size) < 0)
        {
            // todo: compiler doesn't like this. do something
            throw std::runtime_error("munmap error");
        }

        if (close(fd) < 0)
        {
            // todo: compiler doesn't like this. do something
            throw std::runtime_error("close error");
        }

        // todo: is this needed with fd opened by memfd_create?
        // shm_unlink(name)
    }
}

template <class T>
int MemFD<T>::set_size(T new_size)
{
    bool grow = new_size > size;
    int  err  = 0;

    if (!grow)
    {
        goto mr;
    }
ft:

    // set size
    if (ftruncate(fd, new_size) < 0)
    {
        err = 1;
        goto err_end;
    }

    if (!grow)
    {
        goto end;
    }

mr:
    mem = mremap(mem, size, new_size, 0);
    if (mem == MAP_FAILED)
    {
        err = 2;
        goto err_end;
    }

    if (!grow)
    {
        goto ft;
    }

end:

    size = new_size;
    return 0;
err_end:
    return err;
}

template <class T>
size_t MemFD<T>::get_size()
{
    return size;
}

template <class T>
int MemFD<T>::get_fd()
{
    return fd;
}

template <class T>
const void *MemFD<T>::get_mem()
{
    return mem;
}

} // namespace wayround_i2p::cctk

#endif
