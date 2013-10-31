#ifndef GLOCAL_HPP_INCLUDED
#define GLOCAL_HPP_INCLUDED

////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////
#include <TTL.hpp>
#include <SFML/Graphics.hpp> // SFML's library used to draw.


struct Glocal
{

    Glocal()
    :
        window(sf::VideoMode(800, 600, 32), "Ballmer's Peak!"),
        rit(60, 60),
        ips(60),
        issued_render(false),
        render_separately(true)
    {
        batchwork.setWorkerCount(6); // Main thread is used as well, so that's 7
        renderwork.setWorkerCount(1); // For rendering work.
        window.setActive(false);
    }

    sf::RenderWindow window;
    bool active = true;
    sf::Event event;
    ttl::Rit rit;
    ttl::Ips ips;
    float first, second;
    ttl::BatchWorker batchwork;
    ttl::Bool issued_render;
    ttl::BatchWorker renderwork;
    bool render_separately;
    std::mt19937 en;

};

#endif // GLOCAL_HPP_INCLUDED
