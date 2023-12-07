#include <SFML/Graphics.hpp>
// #include <stdlib.h>
// #include <ctime>
// #include <forward_list>
#include "gameView.hpp"
#include "gameLogic.hpp"
#include "gameRes.hpp"

using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Game", sf::Style::Close);
    window.setFramerateLimit(120);
    // srand((unsigned)time(NULL));

    GameRes r;
    bool is_1st_texture = true;

    CellMtrx cell_mtrx;
    generateEmptyRoom(cell_mtrx);
    Player player(1, 4, 100);
    Enemy enemy(4, 4, 30, 10);

    sf::Clock anim_clock;
    sf::Event event;
    while (window.isOpen())
    {
        // sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            // case sf::Event::MouseButtonPressed:
            //     break;
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
                if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num6)
                    player.changeActiveItem(event.key.code - sf::Keyboard::Num0);
                break;
            }
        }

        window.clear(Color(195, 192, 188));

        drawRoom(window, cell_mtrx);
        drawEntity(window, player, r.player_spite);
        drawEntity(window, enemy, r.enemy_sprite);
        drawInventory(window, r.font, player, r.item_sprites);

        window.display();

        if (anim_clock.getElapsedTime().asMilliseconds() > 500)
        {
            if (is_1st_texture)
            {
                r.player_texture.loadFromImage(r.player2_img);
                r.enemy_texture.loadFromImage(r.enemy2_img);
            }
            else
            {
                r.player_texture.loadFromImage(r.player1_img);
                r.enemy_texture.loadFromImage(r.enemy1_img);
            }
            is_1st_texture = !is_1st_texture;
            anim_clock.restart();
        }
    }

    return 0;
}
