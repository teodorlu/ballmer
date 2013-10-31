#include "Main/Main.hpp"


void Main::computeLogic(const std::size_t begin, const std::size_t end)
{ // Parallel Logic
    std::uniform_real_distribution<float> height(-300.f, -10.f);
    std::uniform_real_distribution<float> width(2.f, 10.f);
    std::uniform_real_distribution<float> bredth(2.f, 10.f);
    std::uniform_real_distribution<float> starttop(0.f, 799.f);
    for (int i = begin; i < end; ++i)
    {
        writebuf.asteroids[i].move(0.f, 1.f);
        if (writebuf.asteroids[i].getPosition().y > 600)
        {
            writebuf.asteroids[i].setSize(sf::Vector2f(width(glocal.en), bredth(glocal.en)));
            writebuf.asteroids[i].setPosition(starttop(glocal.en), height(glocal.en));
        }
        else if (writebuf.asteroids[i].getGlobalBounds().intersects(writebuf.ship.getGlobalBounds()))
        {
            writebuf.ishit = true;
        }
    }
}
