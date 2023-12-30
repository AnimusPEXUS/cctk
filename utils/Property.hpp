#ifndef PROPERTY_HPP
#define PROPERTY_HPP

namespace wayround_i2p
{
namespace cctk
{

    template <class T>
    class Property
    {
      public:
        Property(T init_value);
        ~Property();

        void set(T value);
        T    get();
    };

} // namespace cctk
} // namespace wayround_i2p

#endif
