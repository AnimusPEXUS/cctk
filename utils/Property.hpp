#ifndef WAYROUND_I2P_20240109_203545_244014
#define WAYROUND_I2P_20240109_203545_244014

#include <functional>

#include <sigc++/signal.h>

namespace wayround_i2p::cctk
{

/*!
 *   functionality to enable Properties in cctk.
 *
 *   Property can be a simple get/set property, with two options:
 *   1. possibility to have default state;
 *   2. possibility to have undefined state.
 *   this is configured at construction time and should be not changed afterwards.
 *
 *   If Property current state is undefined, - attempt to get it's value, leads
 *   to call getUndefined(), in which you can return value or throw exception;
 *   Property doesn't use getter() in undefined state.
 *
 *   If Property is in default state - it uses function getDefault() to know which
 *   value is actually default and doesn't use getter() to get value.
 *
 *   If Property not Defaultable - calling functions related to default state -
 *   leads to exception.
 *
 *   If Property not Undefinable - calling functions related to undefined state -
 *   leads to exception.
 *
 *   Setting any valid value to property - makes Propery undefault and defined.
 */

template <class T>
using getterFunc = std::function<T()>;

template <class T>
using setterFunc = std::function<bool(const T &)>;

template <class T>
using validityCheckFunc = std::function<bool(T)>;

template <class T>
using validityCheckFuncRef = std::function<bool(const T &)>;

// note: at this point it is intentional to not make isUndefinable/isDefaultable
//       a Property parameter and to not disable corresponding functions via
//       traits. - that is to not overcomplicate this cunctional and not make
//       it hard to read and understand.

template <class T>
struct PropertyConfig
{
    bool isUndefinable = false;
    bool isDefaultable = false;

    //! return true if valid
    //! (optional)
    //! this cb is used if setter not defined and Property is using it's own
    //! default setter
    validityCheckFunc<T> valueValidityCheck;

    //! must be defined if Property is defaultable. used to get actual default
    //! value. it isn't required to constantly be same result, so this way,
    //! you can get value else where.
    getterFunc<T> getDefault;

    //! must be defined if Property is undefinable. allows you to take action in
    //! case of attempt to get value from property in undefined state
    getterFunc<T> getUndefined;

    //! must be defined. you provide actual property value
    getterFunc<T> getter;

    //! must be defined. you store somewhere actual property value
    setterFunc<T> setter;
};

template <class T>
class Property
{
  public:
    // Getter/Setter/External
    static Property<T> create(
        T                      &var,
        getterFunc<T>           getter        = nullptr,
        setterFunc<T>           setter        = nullptr,
        getterFunc<T>           getDefault    = nullptr,
        bool                    isDefaultable = false,
        getterFunc<T>           getUndefined  = nullptr,
        bool                    isUndefinable = false,
        validityCheckFuncRef<T> checker       = nullptr
    );

    Property(const PropertyConfig<T> &cfg);
    ~Property();

    // returns true if value set ok
    bool set(const T &value);
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

    using onBeforeSetSig = sigc::signal<
        void(
            // possibilyty to check new value and modify it before change
            T &supposed_new_value,

            // call this cb to cancel change.
            std::function<void()> cancel
        )>;

    using onAfterSetSig = sigc::signal<
        void(
            // check new value. changing it will not
            // lead to anything
            const T &supposed_new_value
        )>;

    using voidSig = sigc::signal<void()>;

    onBeforeSetSig onBeforeSet() { return onBeforeSet_; };
    onAfterSetSig  onAfterSet() { return onAfterSet_; };
    voidSig        onBeforeDefault() { return onBeforeDefault_; };
    voidSig        onAfterDefault() { return onAfterDefault_; };
    voidSig        onBeforeUndefine() { return onBeforeUndefine_; };
    voidSig        onAfterUndefine() { return onAfterUndefine_; };

  private:
    PropertyConfig<T> cfg;

    bool state_default;
    bool state_undefined;

    inline void exceptIfNotDefaultable();
    inline void exceptIfNotUndefinable();

    onBeforeSetSig onBeforeSet_;
    onAfterSetSig  onAfterSet_;

    voidSig onBeforeDefault_;
    voidSig onAfterDefault_;

    voidSig onBeforeUndefine_;
    voidSig onAfterUndefine_;
};

} // namespace wayround_i2p::cctk

#endif
