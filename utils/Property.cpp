#include "utils/Property.hpp"

namespace wayround_i2p::cctk
{

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
bool Property<T>::set(T value)
{
    if (cfg.valueValidityCheck && !cfg.valueValidityCheck(value))
    {
        return false;
    }

    auto &val_to_set = value;
    bool  cancel_set = false;

    std::function cancel_set_cb =
        [&cancel_set]()
    {
        cancel_set = true;
    };

    onBeforeSet.emit(&val_to_set, cancel_set_cb);

    if (!cancel_set)
    {
        cfg.setter(val_to_set);
        onAfterSet.emit(&val_to_set);
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
bool Property<T>::isDefault(T v)
{
    exceptIfNotDefaultable();
    return v == getDefault();
}

template <class T>
void Property<T>::resetToDefault()
{
    exceptIfNotDefaultable();
    onBeforeDefault.emit();
    state_default = true;
    // todo: for some reason this next line is ok to compile,
    //       wile this field not in cfg.
    //       not touching it for now to see how compiler behave next.
    if (cfg.resetting_to_default_calls_setter_with_result_of_getDefault)
    {
        cfg.setter(getDefault());
    }
    onAfterDefault.emit();
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
    onBeforeUndefine.emit();
    state_undefined = true;
    onAfterUndefine.emit();
}

} // namespace wayround_i2p::cctk
