#ifndef WAYROUND_I2P_20240127_063832_813585
#define WAYROUND_I2P_20240127_063832_813585

namespace wayround_i2p
{
namespace cctk
{

    class Form
    {
      public:
        static std::shared_ptr<Form> create();

        ~Form();

      protected:
        Form();

      private:
        std::shared_ptr<WidgetI> child;
    };

} // namespace cctk
} // namespace wayround_i2p

#endif
