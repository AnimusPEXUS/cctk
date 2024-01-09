#ifndef WAYROUND_I2P_20240109_203545_243786
#define WAYROUND_I2P_20240109_203545_243786

#include <experimental/scope>
#include <functional>
#include <mutex>

namespace wayround_i2p::cctk
{
template <class R, class... Types>
R recursionGuard(
    bool                      &already_running,
    std::mutex                &call_mutex,
    std::function<void()>      already_running_cb,
    std::function<R(Types...)> target,
    Types... args
)
{
    if (already_running)
    {
        return already_running_cb();
    }

    std::experimental::fundamentals_v3::scope_exit(
        [&already_running]()
        {
            already_running = false;
        }
    );

    return target(args...);
}

} // namespace wayround_i2p::cctk

#endif
