#include "Main/Main.hpp"


void Main::delegateRender()
{
    // Simply signal the 1-threaded
    // Render processor that a new frame ready!
    if (glocal.render_separately)
    {
        if (glocal.issued_render.fetch_and_enable() == false)
        {
            glocal.renderwork.issueWork
            (
                std::bind(&Main::render, this)
                , 0
            );
        }
    }
    else
    {
        // Or we draw in the main thread
        // By calling directly
        render();
    }
}
