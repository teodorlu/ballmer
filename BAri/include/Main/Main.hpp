#ifndef MAIN_HPP_INCLUDED
#define MAIN_HPP_INCLUDED

////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////
#include <TTL.hpp> // My own little library
#include <SFML/Graphics.hpp> // SFML's library used to draw.
#include <iostream> // Simple I/O
#include "Main/Buffered.hpp"
#include "Main/Glocal.hpp"


class Main : public ttl::Runnable
{
public:

    Main();
    ~Main();

private:

    Buffered readbuf, writebuf; // Allocate 2 identical copies
    Glocal glocal;

    void delegateInput();
    void delegateLogic();
        void preprocessLogic();
        void computeLogic(const std::size_t begin, const std::size_t end);
        void postprocessLogic();
    void delegateRender();
        void render();

    virtual ttl::Runnable *run() override;

};

#endif // MAIN_HPP_INCLUDED
