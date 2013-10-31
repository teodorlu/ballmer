#ifndef BUFFERED_HPP_INCLUDED
#define BUFFERED_HPP_INCLUDED

////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp> // SFML's library used to draw.


struct Buffered
{
    Buffered()
    {
        std::mt19937 en;
        std::uniform_real_distribution<float> dist(0, 799.f);
        std::uniform_real_distribution<float> ht(-300.f, 0.f);
        for (int i = 0; i < 1000; ++i)
        {
            asteroids.emplace_back();
            asteroids.back().setSize(sf::Vector2f(3, 3));
            asteroids.back().setFillColor(sf::Color::Red);
            asteroids.back().setPosition(dist(en), ht(en));
        }

        //
        ship.setPosition(300, 300);
        ship.setSize(sf::Vector2f(20, 20));
        ship.setFillColor(sf::Color(127, 127, 127));
    }

    /// ///////////////////
    std::vector<sf::RectangleShape> asteroids;
    sf::RectangleShape ship;
    bool ishit = false;
};


#endif // BUFFERED_HPP_INCLUDED
