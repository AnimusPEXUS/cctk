#ifndef SYSTEM_I_HPP
#define SYSTEM_I_HPP

namespace wayround_i2p
{
namespace cctk
{
    class SystemI
    {
      public:
        virtual int init() = 0;
        virtual int run()  = 0;
    };

} // namespace cctk
} // namespace wayround_i2p

#endif
