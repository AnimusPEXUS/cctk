#ifndef CCTK_HPP
#define CCTK_HPP

namespace wayround_i2p
{
namespace CCTK
{

    class CCTK
    {
      public:
        static std::shared_ptr<CCTK> create();

        ~CCTK();

        std::shared_ptr<CCTK> createWindow();

      protected:
        CCTK();

      private:
        std::shared_ptr<SystemI> system;
    };

} // namespace CCTK
} // namespace wayround_i2p

#endif
