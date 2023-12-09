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

    CellMtrx cell_mtrx;
    generateEmptyRoom(cell_mtrx);
    closeRoom(cell_mtrx);
    Player player(1, 4, 100);

    std::list<Enemy> enemy_list;
    Enemy enemy(4, 4, 30, 10, 0);
    enemy_list.push_back(enemy);
    Enemy enemy2(6, 6, 30, 10, 0);
    enemy_list.push_back(enemy2);

    sf::Clock anim_clock, fight_clock;
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
                    player.move(cell_mtrx, dirLeft, enemy_list);
                    if (player.getLastAttackDir() != dirUnknown) // TODO еще проверку у врагов
                        fight_clock.restart();
                    Enemy::moveEnemyList(cell_mtrx, enemy_list, player);
                    break;
                case sf::Keyboard::W:
                    player.move(cell_mtrx, dirUp, enemy_list);
                    if (player.getLastAttackDir() != dirUnknown)
                        fight_clock.restart();
                    Enemy::moveEnemyList(cell_mtrx, enemy_list, player);
                    break;
                case sf::Keyboard::S:
                    player.move(cell_mtrx, dirDown, enemy_list);
                    if (player.getLastAttackDir() != dirUnknown)
                        fight_clock.restart();
                    Enemy::moveEnemyList(cell_mtrx, enemy_list, player);
                    break;
                case sf::Keyboard::D:
                    player.move(cell_mtrx, dirRight, enemy_list);
                    if (player.getLastAttackDir() != dirUnknown)
                        fight_clock.restart();
                    Enemy::moveEnemyList(cell_mtrx, enemy_list, player);
                    break;
                }
                if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num6)
                    player.changeActiveItem(event.key.code - sf::Keyboard::Num0);
                break;
            }
        }

        window.clear(Color(195, 192, 188));

        drawRoom(window, cell_mtrx);

        drawEntity(window, player, r.player_spite, fight_clock);
        drawEnemyList(window, enemy_list, r.enemy_sprites, fight_clock);

        drawInventory(window, r.font, player, r.item_sprites);

        window.display();

        r.animateSprites(anim_clock);
    }

    return 0;
}
