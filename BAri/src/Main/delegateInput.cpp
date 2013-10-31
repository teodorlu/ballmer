#include "Main/Main.hpp"


void Main::delegateInput()
{
    while (glocal.window.pollEvent(glocal.event))
    {
        switch (glocal.event.type)
        {
            case sf::Event::KeyPressed:
                switch (glocal.event.key.code)
                {
                    case sf::Keyboard::Escape:
                        glocal.active = false;
                        break;
                    case sf::Keyboard::Up:
                        writebuf.ship.move(0.f, -1.f);
                        break;
                    case sf::Keyboard::Down:
                        writebuf.ship.move(0.f, 1.f);
                        break;
                    case sf::Keyboard::Left:
                        writebuf.ship.move(-1.f, 0.f);
                        break;
                    case sf::Keyboard::Right:
                        writebuf.ship.move(1.f, 0.f);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        writebuf.ship.move(0.f, -1.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        writebuf.ship.move(0.f, 1.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        writebuf.ship.move(-1.f, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        writebuf.ship.move(1.f, 0.f);
    }
}
