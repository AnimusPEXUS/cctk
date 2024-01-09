#ifndef WAYROUND_I2P_20240109_203545_244014
#define WAYROUND_I2P_20240109_203545_244014

namespace wayround_i2p::cctk
{

enum PropertyWhatToReturnIfValueIsUnset : unsigned char
{
    defaultValue,
    initValue,
    typeInitValue
};

template <class T>
struct PropertySettings
{
    T init_value;    // value after object creation
    T default_value; // value, to which variable is set on reset() call

    bool initially_value_is_default = true;
    bool initially_value_is_unset   = true;
    bool default_is_unset           = false; // if reset() called, property becomes unset
    /* alias resetting_value_makes_it_unset = default_is_unset; */

    // TODO: complete this
    bool setting_to_default_value_makes_property_reset = false;
    bool setting_to_default_value_makes_property_unset = false;

    bool on_unset_also_reset = false;

    // bool variable_define = true;
    // bool variable_private = true;

    bool gettable   = true;  /// define function to get value
    bool settable   = true;  /// define function to set value
    bool resettable = true;  /// define function to reset value to default
    bool unsettable = false; /// value can have 'unset' state. also defines unset() function.

    bool recursiveChangeProtection = true;
    bool recursiveChangeDebugWarn  = false;
    bool recursiveChangeException  = true;

    PropertyWhatToReturnIfValueIsUnset whatToReturnIfUnset = PropertyWhatToReturnIfValueIsUnset
                                                                 .typeInitValue;
};

template <class T>
class Property
{
  public:
    Property(T init_value);
    ~Property();

    void set(T value);
    T    get();
};

} // namespace wayround_i2p::cctk

#endif
