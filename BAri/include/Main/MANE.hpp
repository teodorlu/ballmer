#ifndef MANE_HPP_INCLUDED
#define MANE_HPP_INCLUDED

////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////
#include <TTL.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>



class MANE : public ttl::Runnable
{
public:

    MANE()
    {
    }

    ~MANE()
    {
        if (glocal.issued_render.fetch_and_disable())
            glocal.renderwork.wait();
    }

private:

    std::size_t fib(const std::size_t n)
    {
        switch (n)
        {
            case 0: return 0;
            case 1: return 1;
            default: return fib(n - 1) + fib(n - 2);
        }
    }

    struct Buffered
    {
        Buffered()
        {

            sf::Sprite man;
            tex.loadFromFile("../../res/HuntedLunaEyesWideWithWonder.png", sf::IntRect(0, 8, 0, 8));
            man.setTexture(tex, false);
            units = {man};

            font.loadFromFile("../../res/visitor1.ttf");
            fps.setFont(font);
            ips.setFont(font);
            particles.setFont(font);
            mtrender.setFont(font);
            workthrs.setFont(font);
            avglooptime.setFont(font);
            true_ips.setFont(font);
            mane_wait_for_render.setFont(font);

            fps.setCharacterSize(20);
            ips.setCharacterSize(20);
            particles.setCharacterSize(20);
            mtrender.setCharacterSize(20);
            workthrs.setCharacterSize(20);
            avglooptime.setCharacterSize(20);
            true_ips.setCharacterSize(20);
            mane_wait_for_render.setCharacterSize(20);

            fps.setString("FPS: 60");
            ips.setString("IPS: 60");
            particles.setString("Particles: 10000");
            mtrender.setString("MTR: On");
            workthrs.setString("Workers: 6");
            avglooptime.setString("Average Loop Time (latest 100): 0 us");
            true_ips.setString("Effective ips: 0");
            mane_wait_for_render.setString("MANE Wait For Renderer: 0");

            ips.setPosition(0, fps.getGlobalBounds().height + fps.getGlobalBounds().top);
            particles.setPosition(0, ips.getGlobalBounds().height + ips.getGlobalBounds().top);
            mtrender.setPosition(0, particles.getGlobalBounds().height + particles.getGlobalBounds().top);
            workthrs.setPosition(0, mtrender.getGlobalBounds().height + mtrender.getGlobalBounds().top);
            avglooptime.setPosition(0, workthrs.getGlobalBounds().height + workthrs.getGlobalBounds().top);
            true_ips.setPosition(0, avglooptime.getGlobalBounds().height + avglooptime.getGlobalBounds().top);
            mane_wait_for_render.setPosition(0, true_ips.getGlobalBounds().height + true_ips.getGlobalBounds().top);

            cs.setRadius(10.f);
            cs.setFillColor(sf::Color::Red);
            cs.setPosition(400, 300);

            std::mt19937 en(0xFF);
            std::uniform_real_distribution<float> distx(0, 780);
            std::uniform_real_distribution<float> disty(0, 580);
            std::uniform_int_distribution<char> rgb(127, 255);
            for (int i = 0; i < 10000; ++i)
            {
                rectangles.emplace_back();
                rectangles[i].setPosition(distx(en), disty(en));
                rectangles[i].setFillColor(sf::Color(rgb(en), rgb(en), rgb(en)));
                rectangles[i].setSize(sf::Vector2f(1, 1));
            }
        }
        std::vector<sf::Sprite> units;
        sf::Text fps, ips, particles, mtrender, workthrs, avglooptime, true_ips, mane_wait_for_render;
        sf::Font font;
        sf::Texture tex;
        sf::CircleShape cs;
        std::vector<sf::RectangleShape> rectangles;


    } readbuf, writebuf;

    struct Glocal
    {
        Glocal()
        :
            window(sf::VideoMode(800, 600, 32), "FS"),
            rit(60, 60),
            ips(60),
            first(0),
            second(0),
            issued_render(false),
            it_counter(0),
            render_separately(true),
            fracit(1),
            frac(10),
            avglooptime{0.f}
        {
            batchwork.setWorkerCount(6);
            renderwork.setWorkerCount(1);
            window.setActive(false);
        }

        sf::RenderWindow window;
        bool active = true;
        bool menu = false;
        sf::Event event;
        ttl::Rit rit;
        ttl::Ips ips;
        float first, second;
        ttl::BatchWorker batchwork;
        ttl::Bool issued_render;
        ttl::BatchWorker renderwork;
        int it_counter;
        bool render_separately;
        int fracit, frac;
        float avglooptime[100];
        int avgloopindex;
    } glocal;

    void delegateInput()
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
                        case sf::Keyboard::A:
                        {
                            glocal.batchwork.setWorkerCount(glocal.batchwork.getWorkerCount() > 0 ? glocal.batchwork.getWorkerCount() - 1 : 0);
                            writebuf.workthrs.setString("Workers: " + std::to_string(glocal.batchwork.getWorkerCount()));
                        } break;
                        case sf::Keyboard::D:
                        {
                            glocal.batchwork.setWorkerCount(glocal.batchwork.getWorkerCount() + 1);
                            writebuf.workthrs.setString("Workers: " + std::to_string(glocal.batchwork.getWorkerCount()));
                        } break;
                        case sf::Keyboard::Q:
                        {
                            if (writebuf.rectangles.size() >= 100)
                                writebuf.rectangles.erase(writebuf.rectangles.begin() + writebuf.rectangles.size() - 100, writebuf.rectangles.end());
                            writebuf.particles.setString("Particles: " + std::to_string(writebuf.rectangles.size()));
                        } return;
                        case sf::Keyboard::E:
                        {
                            std::mt19937 en(0xFF);
                            std::uniform_real_distribution<float> distx(0, 780);
                            std::uniform_real_distribution<float> disty(0, 580);
                            std::uniform_int_distribution<char> rgb(127, 255);
                            for (int i = 0; i < 100; ++i)
                            {
                                writebuf.rectangles.emplace_back();
                                writebuf.rectangles.back().setPosition(distx(en), disty(en));
                                writebuf.rectangles.back().setFillColor(sf::Color(rgb(en), rgb(en), rgb(en)));
                                writebuf.rectangles.back().setSize(sf::Vector2f(1, 1));
                            }
                            writebuf.particles.setString("Particles: " + std::to_string(writebuf.rectangles.size()));
                        } return;
                        case sf::Keyboard::Up:
                        {
                            std::size_t dist = glocal.rit.getFirstDistribution();
                            dist++;
                            glocal.rit.setDistribution(dist, glocal.rit.getSecondDistribution());
                        } break;
                        case sf::Keyboard::Down:
                        {
                            std::size_t dist = glocal.rit.getFirstDistribution();
                            dist--;
                            if (dist == 0)
                                dist = 1;
                            glocal.rit.setDistribution(dist, glocal.rit.getSecondDistribution());
                        } break;
                        case sf::Keyboard::Left:
                        {
                            std::size_t dist = glocal.rit.getSecondDistribution();
                            dist--;
                            if (dist == 0)
                                dist = 1;
                            glocal.rit.setDistribution(glocal.rit.getFirstDistribution(), dist);
                        } break;
                        case sf::Keyboard::Right:
                        {
                            std::size_t dist = glocal.rit.getSecondDistribution();
                            dist++;
                            glocal.rit.setDistribution(glocal.rit.getFirstDistribution(), dist);
                        } break;
                        case sf::Keyboard::R:
                        {
                            glocal.render_separately = !glocal.render_separately;
                            if (!glocal.render_separately)
                            {
                                if (glocal.issued_render.fetch_and_disable())
                                    glocal.renderwork.wait();
                                glocal.renderwork.issueWork
                                (
                                    [&]()
                                    {
                                        glocal.window.setActive(false);
                                    }
                                    , 0
                                );
                                glocal.renderwork.wait();
                            }
                            else
                            {
                                glocal.window.setActive(false);
                            }
                            writebuf.mtrender.setString(std::string("MTR: ") + (glocal.render_separately ? "On" : "Off"));
                            return;
                        } break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            glocal.ips.setIps(std::max(glocal.rit.getFirstDistribution(), glocal.rit.getSecondDistribution()));
            writebuf.fps.setString("FPS: " + std::to_string(glocal.rit.getSecondDistribution()));
            writebuf.ips.setString("IPS: " + std::to_string(glocal.rit.getFirstDistribution()));
        }
    }

    void delegateLogic()
    {
        glocal.first += 0.02f;
        writebuf.cs.setPosition(400 + 50 * std::sin(glocal.first), 300 + 50 * std::cos(glocal.first));

        const std::size_t workcnt = glocal.batchwork.getWorkerCount();
        for (std::size_t i = 0; i < workcnt; ++i)
        {
            glocal.batchwork.issueWork
            (
                [i, this]()
                {
                    this->logic(i);
                }
             , i
            );
        }
        logic(workcnt);
        if (workcnt > 0)
            glocal.batchwork.wait();
        if (glocal.issued_render.fetch_and_disable())
            glocal.renderwork.wait();
            readbuf = writebuf;
    }

    void logic(const std::size_t thread)
    { // Parallel Logic
        const std::size_t workcnt = glocal.batchwork.getWorkerCount();
        const std::size_t
            start = (thread * writebuf.rectangles.size()) / (workcnt + 1),
            end = ((thread + 1) * writebuf.rectangles.size()) / (workcnt + 1);

        std::mt19937 en(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
        std::uniform_real_distribution<float> dist(1.f, 6.f);
        for (int i = start; i < end; ++i)
        {
            writebuf.rectangles[i].move(sf::Vector2f(dist(en), dist(en)));
            if (writebuf.rectangles[i].getPosition().y > 600 || writebuf.rectangles[i].getPosition().x > 800)
                writebuf.rectangles[i].setPosition(sf::Vector2f(0.f, 0.f));

        }
    }
    ////////////////////////////////////////////////////////////
    void delegateRender()
    {
        std::function<void()> render_function =
        [&]()
        {
            glocal.second += 0.02f;
            glocal.window.clear();
            for (auto &x : readbuf.units)
                glocal.window.draw(x);
            for (auto &x : readbuf.rectangles)
                glocal.window.draw(x);
            glocal.window.draw(readbuf.fps);
            glocal.window.draw(readbuf.ips);
            glocal.window.draw(readbuf.particles);
            glocal.window.draw(readbuf.mtrender);
            glocal.window.draw(readbuf.workthrs);
            glocal.window.draw(readbuf.avglooptime);
            glocal.window.draw(readbuf.true_ips);
            glocal.window.draw(readbuf.mane_wait_for_render);
            glocal.window.draw(readbuf.cs);
            glocal.window.display();
//            glFinish();
        };

        if (glocal.render_separately)
        {
            if (glocal.issued_render.fetch_and_enable() == false)
            {
                glocal.renderwork.issueWork
                (
                    render_function
                    , 0
                );
            }
        }
        else
        {
            render_function();
        }
    }

    void computeAverageLoopTime()
    {
        glocal.avglooptime[glocal.avgloopindex++] = glocal.ips.getDelay().count();
        if (glocal.avgloopindex == std::extent<decltype(glocal.avglooptime), 0>::value)
            glocal.avgloopindex = 0;

        float avg = 0.f;
        for (std::size_t i = 0; i < std::extent<decltype(glocal.avglooptime), 0>::value; ++i)
            avg += glocal.avglooptime[i];

        avg /= 100.f;

        writebuf.avglooptime.setString("Average Loop Time (latest 100): " + std::to_string(avg) + " us");
        writebuf.true_ips.setString("Effective IPS: " + std::to_string(1000000.f / avg));
    }

    ////////////////////////////////////////////////////////////
    virtual ttl::Runnable *run() override
    {
        while (glocal.active == true)
        {
            glocal.ips.limit();
            delegateInput();
            if (glocal.rit.isFirstReady())
                delegateLogic();
            if (glocal.rit.isSecondReady())
                delegateRender();
            computeAverageLoopTime();
        }
        return nullptr;
    }

};

#endif // MANE_HPP_INCLUDED
