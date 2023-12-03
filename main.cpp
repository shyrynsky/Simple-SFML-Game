#include <SFML/Graphics.hpp>
// #include <stdlib.h>
// #include <ctime>
// #include <forward_list>
// using namespace sf;
#include "gameView.hpp"
#include "gameLogic.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Game", sf::Style::Close);
    window.setFramerateLimit(120);
    // srand((unsigned)time(NULL));

    CellMtrx cell_mtrx;
    GenerateEmptyRoom(cell_mtrx);
    while (window.isOpen())
    {
        sf::Event event;
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:

                break;
            }
        }

        window.clear();

        drawRoom(window, cell_mtrx);

        window.display();
    }

    return 0;
}
