#include "Main/Main.hpp"


void Main::delegateLogic()
{
    // Mono-threaded pre-processing ////////////////////////////
    // Used for processing some logic sequentially
    // after we've gotten commands from input
    preprocessLogic();
    ////////////////////////////////////////////////////////////

    // Multi-threaded batch processing /////////////////////////
    const std::size_t workcnt = glocal.batchwork.getWorkerCount();
    for (std::size_t i = 0; i < workcnt; ++i)
    {
        const std::size_t
            begin = (i * readbuf.asteroids.size()) / (workcnt + 1),
            end = ((i + 1) * readbuf.asteroids.size()) / (workcnt + 1);

        glocal.batchwork.issueWork
        (
            [begin, end, this]()
            {
                this->computeLogic(begin, end);
            }
         , i
        );
    }
    // Use this thread as well - considering it the last thread (letting it wait only would be a waste)
    const std::size_t
            begin = (workcnt * readbuf.asteroids.size()) / (workcnt + 1),
            end = ((workcnt + 1) * readbuf.asteroids.size()) / (workcnt + 1);
    computeLogic(begin, end);
    // Check if all workers are done
    // Internally BatchWork uses an atomic counter, and only signals when the last one has finished.
    // If workcnt == 0, then only the main thread works on physics,
    // so no condition variable is notified, so we do not need to wait
    if (workcnt > 0)
        glocal.batchwork.wait();
    ////////////////////////////////////////////////////////////

    // Renderer Synchronization ////////////////////////////////
    // Wait until the renderer has finished the frame, if it hasn't already.
    // No need to wait if we have not issued a render (it'll be false)
    if (glocal.issued_render.fetch_and_disable())
        glocal.renderwork.wait();
    ////////////////////////////////////////////////////////////

    // Mono-threaded post-processing ///////////////////////////
    // For glocal states that the renderer might use...
    postprocessLogic();
    ////////////////////////////////////////////////////////////

    // Immutability and Newton's 3rd law ///////////////////////
    // Copy all data from the new buffer to the old one
    // Readbuf will be used for rendering data
    readbuf = writebuf;
    ////////////////////////////////////////////////////////////
}
