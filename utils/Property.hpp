#ifndef WAYROUND_I2P_20240125_022823_735156
#define WAYROUND_I2P_20240125_022823_735156

#include <functional>

#include <sigc++/signal.h>
// #include <unicode/unistr.h>

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
    validityCheckFunc<T> isValid;

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
        validityCheckFuncRef<T> isValid       = nullptr
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
    bool isDefault(const T &);
    void resetToDefault();

    T    getUndefined();
    bool isUndefined();
    void undefine();

    bool isValid(const T &);

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

template <class T>
Property<T> Property<T>::create(
    T                      &var,
    getterFunc<T>           getter,
    setterFunc<T>           setter,
    getterFunc<T>           getDefault,
    bool                    isDefaultable,
    getterFunc<T>           getUndefined,
    bool                    isUndefinable,
    validityCheckFuncRef<T> isValid
)
{
    if (!getter)
    {
        getter = [&var]()
        {
            return var;
        };
    }

    if (!setter)
    {
        setter = [&var, isValid](T new_val)
        {
            if (isValid)
            {
                if (!isValid(var))
                {
                    return false;
                }
            }
            var = new_val;
            return true;
        };
    }

    auto ret = Property(
        PropertyConfig<T>{
            .isUndefinable = isUndefinable,
            .isDefaultable = isDefaultable,
            .isValid       = isValid,
            .getDefault    = getDefault,
            .getUndefined  = getUndefined,
            .getter        = getter,
            .setter        = setter,
        }
    );

    return ret;
}

template <class T>
Property<T>::Property(const PropertyConfig<T> &cfg)
{
    this->cfg = cfg;
}

template <class T>
Property<T>::~Property()
{
}

template <class T>
bool Property<T>::set(const T &value)
{
    if (cfg.isValid && !cfg.isValid(value))
    {
        return false;
    }

    auto  val_to_set_int = value;
    auto &val_to_set     = val_to_set_int;

    bool cancel_set = false;

    std::function cancel_set_cb =
        [&cancel_set]()
    {
        cancel_set = true;
    };

    onBeforeSet_.emit(val_to_set, cancel_set_cb);

    if (!cancel_set)
    {
        cfg.setter(val_to_set);
        onAfterSet_.emit(val_to_set);
    }

    return true;
}

template <class T>
T Property<T>::get()
{
    // todo: take in account default/undefined state

    if (cfg.isUndefinable && isUndefined())
    {
        return getUndefined();
    }

    if (cfg.isDefaultable && isDefault())
    {
        return getDefault();
    }
    return cfg.getter();
}

template <class T>
bool Property<T>::isDefaultable()
{
    return cfg.isDefaultable;
}

template <class T>
bool Property<T>::isUndefinable()
{
    return cfg.isUndefinable;
}

template <class T>
T Property<T>::getDefault()
{
    exceptIfNotDefaultable();
    return cfg.getDefault();
}

template <class T>
bool Property<T>::isDefault()
{
    exceptIfNotDefaultable();
    return state_default;
}

template <class T>
bool Property<T>::isDefault(const T &v)
{
    exceptIfNotDefaultable();
    return v == getDefault();
}

template <class T>
void Property<T>::resetToDefault()
{
    if (cfg.resetting_to_default_calls_setter_with_result_of_getDefault) {}
    exceptIfNotDefaultable();
    onBeforeDefault_.emit();
    state_default = true;
    // todo: for some reason this next line is ok to compile,
    //       wile this field not in cfg.
    //       not touching it for now to see how compiler behave next.
    if (cfg.resetting_to_default_calls_setter_with_result_of_getDefault)
    {
        cfg.setter(getDefault());
    }
    onAfterDefault_.emit();
}

template <class T>
T Property<T>::getUndefined()
{
    exceptIfNotUndefinable();
    return cfg.getUndefined();
}

template <class T>
bool Property<T>::isUndefined()
{
    exceptIfNotUndefinable();
    return state_undefined;
}

template <class T>
void Property<T>::undefine()
{
    onBeforeUndefine_.emit();
    state_undefined = true;
    onAfterUndefine_.emit();
}

template <class T>
bool Property<T>::isValid(const T &v)
{
    return cfg.isValid(v);
}

template <class T>
void Property<T>::exceptIfNotDefaultable()
{
    if (!cfg.isDefaultable)
    {
        throw std::runtime_error("property not defaultable");
    }
}

template <class T>
void Property<T>::exceptIfNotUndefinable()
{
    if (!cfg.isUndefinable)
    {
        throw std::runtime_error("property not undefinable");
    }
}

} // namespace wayround_i2p::cctk

#endif
