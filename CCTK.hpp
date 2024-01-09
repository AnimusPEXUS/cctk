#ifndef WAYROUND_I2P_20240109_203545_243034
#define WAYROUND_I2P_20240109_203545_243034

#include <memory>

#include <sigc++/sigc++.h>
#include <unicode/unistr.h>

#include "interfaces/interfaces.hpp"
#include "types/types.hpp"

namespace wayround_i2p::cctk
{

class CCTK
{
  public:
    static std::shared_ptr<CCTK> create();

    ~CCTK();

    int applyCmdLineArgs(int argc, char **args);

    int init();
    int run();

    int setSystem(std::shared_ptr<SystemI> sys);

    std::shared_ptr<WindowI> createWindow();

    std::shared_ptr<KeyboardI> getKeyboard();
    std::shared_ptr<PointerI>  getPointer();

    std::weak_ptr<sigc::signal<void()>> get_sigAfterStart();

  protected:
    CCTK();

  private:
    std::shared_ptr<SystemI> system;

    std::shared_ptr<sigc::signal<void()>> sigAfterStart;

    bool running = false;
};

} // namespace wayround_i2p::cctk

#endif
