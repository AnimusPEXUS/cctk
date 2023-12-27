#ifndef FORM_HPP
#define FORM_HPP

namespace wayround_i2p
{
namespace CCTK
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

} // namespace CCTK
} // namespace wayround_i2p

#endif
