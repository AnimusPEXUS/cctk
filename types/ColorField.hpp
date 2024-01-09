#ifndef WAYROUND_I2P_20240109_203545_246578
#define WAYROUND_I2P_20240109_203545_246578

#include <cstdint>
#include <stdfloat>

namespace wayround_i2p::cctk
{
enum ColorFieldDataType : unsigned char
{
    u8
};

union ColorFieldData
{
    std::uint8_t u8;
    // std::uint16_t   u16;
    // std::uint32_t   u32;
    // std::uint64_t   u64;
    // std::int8_t     s8;
    // std::int16_t    s16;
    // std::int32_t    s32;
    // std::int64_t    s64;
    // std::float16_t  f16;
    // std::float32_t  f32;
    // std::float64_t  f64;
    // std::float128_t f128;
};

struct ColorField
{
    ColorFieldDataType type;
    ColorFieldData     data;

    void set_u8(std::uint8_t u8)
    {
        this->type    = ColorFieldDataType::u8;
        this->data.u8 = u8;
    }

    std::uint8_t get_u8()
    {
        return this->data.u8;
    }
};

} // namespace wayround_i2p::cctk

#endif
