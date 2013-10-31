#include "Main/Main.hpp"


void Main::render()
{
    glocal.window.clear();
    for (auto &x : readbuf.asteroids)
        glocal.window.draw(x);
    glocal.window.draw(readbuf.ship);
    if (readbuf.ishit == true)
        std::cout << "Yr got hit" << rand() << std::endl;
    glocal.window.display();
}
