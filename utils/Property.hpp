#ifndef WAYROUND_I2P_20240109_203545_244014
#define WAYROUND_I2P_20240109_203545_244014

#include <functional>

#include <sigc++/signal.h>

namespace wayround_i2p::cctk
{

/**
    functionality to enable Properties in cctk.

    Property can be a simple get/set property, with two options:
    1. possibility to have default state;
    2. possibility to have undefined state.
    this is configured at construction time and should be not changed afterwards.

    If Property current state is undefined, - attempt to get it's value, leads
    to call getUndefined(), in which you can return value or throw exception;
    Property doesn't use getter() in undefined state.

    If Property is in default state - it uses function getDefault() to know which
    value is actually default and doesn't use getter() to get value.

    If Property not Defaultable - calling functions related to default state -
    leads to exception.

    If Property not Undefinable - calling functions related to undefined state -
    leads to exception.

    Setting any valid value to property - makes Propery undefault and defined.

 */

// note: at this point it is intentional to not make isUndefinable/isDefaultable
//       a Property parameter and to not disable corresponding functions via
//       traits. - that is to not overcomplicate this cunctional and not make
//       it hard to read and understand.

template <class T>
struct PropertyConfig
{
    bool isUndefinable = false;
    bool isDefaultable = false;

    // return true if valid
    // (optional)
    std::function<bool()> valueValidityCheck(T);

    // must be defined if Property is defaultable. used to get actual default
    // value. it isn't required to constantly be same result, so this way,
    // you can get value else where.
    std::function<T()> getDefault();

    // must be defined if Property is undefinable. allows you to take action in
    // case of attempt to get value from property in undefined state
    std::function<T()> getUndefined();

    // must be defined. you provide actual property value
    std::function<T()> getter();

    // must be defined. you store somewhere actual property value
    std::function<void(T)> setter();
};

template <class T>
class Property
{
  public:
    Property(const PropertyConfig<T> &cfg);
    ~Property();

    // returns true if value set ok
    bool set(T value);
    T    get();

    bool isDefaultable();
    bool isUndefinable();

    T    getDefault();
    bool isDefault();
    bool isDefault(T);
    void resetToDefault();

    T    getUndefined();
    bool isUndefined();
    void undefine();

  private:
    PropertyConfig<T> cfg;

    bool state_default;
    bool state_undefined;

    inline void exceptIfNotDefaultable();
    inline void exceptIfNotUndefinable();

    sigc::signal<
        void(
            // possibilyty to check new value and modify it before change
            T &supposed_new_value,

            // call this cb to cancel change.
            std::function<void()> cancel
        )>
        onBeforeSet;

    sigc::signal<
        void(
            // check new value. changing it will not
            // lead to anything
            const T &supposed_new_value
        )>
        onAfterSet;

    sigc::signal<void()> onBeforeDefault;
    sigc::signal<void()> onAfterDefault;

    sigc::signal<void()> onBeforeUndefine;
    sigc::signal<void()> onAfterUndefine;
};

} // namespace wayround_i2p::cctk

#endif
