#include <SFML/Graphics.hpp>
// #include <stdlib.h>
// #include <ctime>
// #include <forward_list>
// using namespace sf;
#include "gameView.hpp"
#include "gameLogic.hpp"

using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Game", sf::Style::Close);
    window.setFramerateLimit(120);
    // srand((unsigned)time(NULL));

    sf::Image player1_img, player2_img;
    player1_img.loadFromFile("player1.png");
    player2_img.loadFromFile("player2.png");
    sf::Texture player_texture;
    player_texture.loadFromImage(player1_img);
    bool is_1st_texture = true;
    sf::Sprite player_spite;
    player_spite.setTexture(player_texture);

    CellMtrx cell_mtrx;
    generateEmptyRoom(cell_mtrx);
    Player player(1, 4, 100);

    sf::Clock clock;
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
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::A:
                    player.move(cell_mtrx, dirLeft);
                    break;
                case sf::Keyboard::W:
                    player.move(cell_mtrx, dirUp);
                    break;
                case sf::Keyboard::S:
                    player.move(cell_mtrx, dirDown);
                    break;
                case sf::Keyboard::D:
                    player.move(cell_mtrx, dirRight);
                    break;
                }
                break;
            }
        }

        window.clear();

        drawRoom(window, cell_mtrx);
        drawEntity(window, player, player_spite);

        window.display();

        if (clock.getElapsedTime().asMilliseconds() > 500)
        {
            if (is_1st_texture)
                player_texture.loadFromImage(player2_img);
            else
                player_texture.loadFromImage(player1_img);
            is_1st_texture = !is_1st_texture;
            clock.restart();
        }
    }

    return 0;
}
