#include <SFML/Graphics.hpp>
#include <ctime>
#include "gameView.hpp"
#include "gameLogic.hpp"
#include "gameRes.hpp"
#include "MenuHandler.hpp"

using namespace sf;

void handleMenuFrame(Event &event, MenuHandler &handler, RenderWindow &window, GameRes &r /*, Player &const player, list<Booster> &const boosters, list<Bullet> &bullets, list<Enemy> &const enemies, Background &const background*/)
{
    window.clear(Color(145, 142, 138));
    if (window.pollEvent(event))
    {
        switch (event.type)
        {
        case Event::Closed:
            window.close();
            break;
        case Event::MouseButtonReleased:
            if (event.mouseButton.button == Mouse::Left)
                handler.selectAction(window);
            break;
        }
    }
    handler.update(window);
    window.display();
    if (!handler.active())
    {
        r.setSFXStatus(handler.getChangeableParameterValue("sound"), handler.getChangeableParameterValue("music"));
    }
}

void createMainMenu(MenuHandler &handler, const Font &uiFont, const RenderWindow &window)
{
    auto &mainMenu = handler.createMenu(uiFont, "main", "TheRogueLikeGame", 100);
    float offset = mainMenu.getTitleRect().width / 2;
    mainMenu.setTitlePos(window.getSize().x / 2 - offset, 100 + window.getSize().y / 4);

    auto &but1 = mainMenu.addButton(uiFont, "Start", 80, true);
    offset = but1.getButtonRect().width / 2;
    but1.setPos(window.getSize().x / 2 - offset, 100 + window.getSize().y / 3 + 90);

    auto &but2 = mainMenu.addButton(uiFont, "Settings", 80, false, false, "settings");
    offset = but2.getButtonRect().width / 2;
    but2.setPos(window.getSize().x / 2 - offset, 100 + window.getSize().y / 3 + 180);

    auto &but3 = mainMenu.addButton(uiFont, "Exit", 80, false, true);
    offset = but3.getButtonRect().width / 2;
    but3.setPos(window.getSize().x / 2 - offset, 100 + window.getSize().y / 3 + 270);
}

void createSettingsMenu(MenuHandler &handler, Font &uiFont, RenderWindow &window)
{
    auto &settingsMenu = handler.createMenu(uiFont, "settings", "", 80);

    auto &but1 = settingsMenu.addButton(uiFont, "Sound", 80, false, false, "", "sound");
    float offset = but1.getButtonRect().width / 2;
    but1.setPos(window.getSize().x / 2 - offset, 100 + window.getSize().y / 3 + 90);

    auto &but2 = settingsMenu.addButton(uiFont, "Music", 80, false, false, "", "music");
    offset = but2.getButtonRect().width / 2;
    but2.setPos(window.getSize().x / 2 - offset, 100 + window.getSize().y / 3 + 180);

    auto &but3 = settingsMenu.addButton(uiFont, "Back", 80, false, false, "main");
    offset = but3.getButtonRect().width / 2;
    but3.setPos(window.getSize().x / 2 - offset, 100 + window.getSize().y / 3 + 270);
}

void createGameOverMenu(MenuHandler &handler, Font &uiFont, RenderWindow &window)
{
    auto &gameOverMenu = handler.createMenu(uiFont, "gameover", "", 100);

    auto &but3 = gameOverMenu.addButton(uiFont, "Exit", 80, false, true);
    float offset = but3.getButtonRect().width / 2;
    but3.setPos(window.getSize().x / 2 - offset, 100 + window.getSize().y / 3 + 270);
}

void addMenus(MenuHandler &handler, Font &uiFont, RenderWindow &window)
{
    createMainMenu(handler, uiFont, window);
    createSettingsMenu(handler, uiFont, window);
    createGameOverMenu(handler, uiFont, window);
}

void processAfterMove(Player &player, std::list<Enemy> &enemy_list, Rooms rooms, sf::Clock &fight_clock, GameRes &r)
{
    if (player.getLastAttackDir() != dirUnknown)
    {
        fight_clock.restart();
        r.playHit();
    }
    Enemy::moveEnemyList(rooms.cell_mtrx, enemy_list, player);
    for (Enemy &enemy : enemy_list)
    {
        if (enemy.getLastAttackDir() != dirUnknown)
        {
            fight_clock.restart();
            r.playHit();
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Game", sf::Style::Close);
    window.setFramerateLimit(120);
    srand((unsigned)time(NULL));

    GameRes r;

    MenuHandler handler;
    handler.addChangeableParameter("sound", true);
    handler.addChangeableParameter("music", true);
    addMenus(handler, r.font, window);

    Rooms rooms;
    std::string mesStr;
    Player player(2, 4, 100);

    std::list<Enemy> enemy_list;
    std::list<GroundItem> ground_item_list;
    GroundItem ground_item1(4, 4, item_set[0]);
    ground_item_list.push_back(ground_item1);
    GroundItem ground_item2(4, 5, item_set[ITEM_SET_SIZE - 2]);
    ground_item_list.push_back(ground_item2);

    sf::Clock anim_clock, fight_clock;
    sf::Event event;
    while (window.isOpen())
    {

        if (handler.active())
        {
            handleMenuFrame(event, handler, window, r);
        }
        else if (!is_game_over)
        {
            if (rooms.getIsBossRoom())
                r.updateSong(0);
            else
                r.updateSong(1);

            while (window.pollEvent(event))
            {

                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                    case sf::Keyboard::A:
                        if (player.move(rooms, dirLeft, enemy_list, ground_item_list, mesStr))
                            processAfterMove(player, enemy_list, rooms, fight_clock, r);
                        break;
                    case sf::Keyboard::W:
                        if (player.move(rooms, dirUp, enemy_list, ground_item_list, mesStr))
                            processAfterMove(player, enemy_list, rooms, fight_clock, r);
                        break;
                    case sf::Keyboard::S:
                        if (player.move(rooms, dirDown, enemy_list, ground_item_list, mesStr))
                            processAfterMove(player, enemy_list, rooms, fight_clock, r);
                        break;
                    case sf::Keyboard::D:
                        if (player.move(rooms, dirRight, enemy_list, ground_item_list, mesStr))
                            processAfterMove(player, enemy_list, rooms, fight_clock, r);
                        break;
                    }
                    if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num6)
                        player.changeActiveItem(event.key.code - sf::Keyboard::Num0);
                    break;
                }
            }

            window.clear(Color(195, 192, 188));

            drawRoom(window, rooms.cell_mtrx);

            drawGroundItemList(window, ground_item_list, r.item_ground_sprites);
            drawEntity(window, player, r.player_spite, fight_clock);
            drawEnemyList(window, enemy_list, r.enemy_sprites, fight_clock);

            drawInventory(window, r.font, player, r.item_sprites);
            drawMiniMap(window, rooms);
            drawPlayerStatus(window, player, r.font, mesStr);

            window.display();

            r.animateSprites(anim_clock);
        }
        else
        {
            handler.setMenuActive("gameover");
            std::string title_string = is_won ? "You won!!!" : "game over (((";
            handler.getCurrentMenu()->title.setString(title_string);
            float offset = handler.getCurrentMenu()->getTitleRect().width / 2;
            handler.getCurrentMenu()->setTitlePos(window.getSize().x / 2 - offset, 100 + window.getSize().y / 4);
        }
    }

    return 0;
}
