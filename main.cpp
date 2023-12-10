#include <SFML/Graphics.hpp>
// #include <stdlib.h>
#include <ctime>
#include "gameView.hpp"
#include "gameLogic.hpp"
#include "gameRes.hpp"

using namespace sf;

void processAfterMove(Player &player, std::list<Enemy> &enemy_list, Rooms rooms, sf::Clock &fight_clock)
{
    if (player.getLastAttackDir() != dirUnknown)
        fight_clock.restart();
    for (Enemy &enemy : enemy_list)
    {
        if (enemy.getLastAttackDir() != dirUnknown)
            fight_clock.restart();
    }
    Enemy::moveEnemyList(rooms.cell_mtrx, enemy_list, player);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Game", sf::Style::Close);
    window.setFramerateLimit(120);
    srand((unsigned)time(NULL));

    GameRes r;
    Rooms rooms;
    rooms.generateEmptyRoom();
    rooms.closeRoom();
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
                    if (player.move(rooms, dirLeft, enemy_list))
                        processAfterMove(player, enemy_list, rooms, fight_clock);
                    break;
                case sf::Keyboard::W:
                    if (player.move(rooms, dirUp, enemy_list))
                        processAfterMove(player, enemy_list, rooms, fight_clock);
                    break;
                case sf::Keyboard::S:
                    if (player.move(rooms, dirDown, enemy_list))
                        processAfterMove(player, enemy_list, rooms, fight_clock);
                    break;
                case sf::Keyboard::D:
                    if (player.move(rooms, dirRight, enemy_list))
                        processAfterMove(player, enemy_list, rooms, fight_clock);
                    break;
                }
                if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num6)
                    player.changeActiveItem(event.key.code - sf::Keyboard::Num0);
                break;
            }
        }

        window.clear(Color(195, 192, 188));

        drawRoom(window, rooms.cell_mtrx);

        drawEntity(window, player, r.player_spite, fight_clock);
        drawEnemyList(window, enemy_list, r.enemy_sprites, fight_clock);

        drawInventory(window, r.font, player, r.item_sprites);

        window.display();

        r.animateSprites(anim_clock);
    }

    return 0;
}
