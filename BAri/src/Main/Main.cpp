#include "Main/Main.hpp"


Main::Main()
{

}


Main::~Main()
{
    // If we do not do this, the renderer may still be working
    // The thread therefore dies unexpectedly -> undefined behaviour
    if (glocal.issued_render.fetch_and_disable())
        glocal.renderwork.wait();
}


ttl::Runnable *Main::run()
{
    while (glocal.active)
    {
        glocal.ips.limit();
        delegateInput();
        if (glocal.rit.isFirstReady())
            delegateLogic();
        if (glocal.rit.isSecondReady())
            delegateRender();
    }
    return nullptr;
}
