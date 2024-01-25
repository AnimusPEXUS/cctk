#ifndef WAYROUND_I2P_20240125_022823_734718
#define WAYROUND_I2P_20240125_022823_734718

namespace wayround_i2p::cctk
{

class MemFD
{
  public:
    MemFD(size_t page_size, size_t page_count);

    ~MemFD();

    void   set_size(size_t new_size);
    size_t get_page_size();

  private:
    size_t size = 0;

    int fd = -1;
};

} // namespace wayround_i2p::cctk

#endif
