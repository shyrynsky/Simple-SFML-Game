#include <SFML/Graphics.hpp>
#include <ctime>
#include "gameView.hpp"
#include "gameLogic.hpp"
#include "gameRes.hpp"
#include "MenuHandler.hpp"

using namespace sf;

void handleMenuFrame(Event &event, MenuHandler &handler, RenderWindow &window, GameRes &r /*, Player &const player, list<Booster> &const boosters, list<Bullet> &bullets, list<Enemy> &const enemies, Background &const background*/)
{
    // r.resetSong(); // reset current song
    window.clear(Color(145, 142, 138));
    // background.draw(window);     // draw the background on the screen
    if (window.pollEvent(event)) // if some event happened
    {
        switch (event.type) // handle the event
        {
        case Event::Closed:
            window.close(); // close the window
            break;
        case Event::MouseButtonReleased:
            if (event.mouseButton.button == Mouse::Left) // if user has released left mouse button
                handler.selectAction(window);            // handle user action
            break;
        }
    }
    handler.update(window); // update the menu handler
    window.display();       // display drawn frame
    if (!handler.active())  // if user has either returned to menu or pressed the start button
    {
        r.setSFXStatus(handler.getChangeableParameterValue("sound"), handler.getChangeableParameterValue("music")); // update sound and music settings
        // restartGame(window, boosters, player, bullets, enemies);                                                             // restart the game
    }
}

void createMainMenu(MenuHandler &handler, const Font &uiFont, const RenderWindow &window)
{
    auto &mainMenu = handler.createMenu(uiFont, "main", "Inoplanetyane", 100);           // create new object in menus list
    float offset = mainMenu.getTitleRect().width / 2;                                    // set title offset
    mainMenu.setTitlePos(window.getSize().x / 2 - offset, 100 + window.getSize().y / 4); // place the title on the screen

    auto &but1 = mainMenu.addButton(uiFont, "Start", 80, true);                      // add new button to the created menu
    offset = but1.getButtonRect().width / 2;                                         // set button offset
    but1.setPos(window.getSize().x / 2 - offset, 100 + window.getSize().y / 3 + 90); // place the created button on the screen

    auto &but2 = mainMenu.addButton(uiFont, "Settings", 80, false, false, "settings"); // add new button to the created menu
    offset = but2.getButtonRect().width / 2;                                           // set button offset
    but2.setPos(window.getSize().x / 2 - offset, 100 + window.getSize().y / 3 + 180);  // place the created button on the screen

    auto &but3 = mainMenu.addButton(uiFont, "Exit", 80, false, true);                 // add new button to the created menu
    offset = but3.getButtonRect().width / 2;                                          // set button offset
    but3.setPos(window.getSize().x / 2 - offset, 100 + window.getSize().y / 3 + 270); // place the created button on the screen
}

void createSettingsMenu(MenuHandler &handler, Font &uiFont, RenderWindow &window)
{
    auto &settingsMenu = handler.createMenu(uiFont, "settings", "", 80); // create new object in menus list

    auto &but1 = settingsMenu.addButton(uiFont, "Sound", 80, false, false, "", "sound"); // add new button to the created menu
    float offset = but1.getButtonRect().width / 2;                                       // set button offset
    but1.setPos(window.getSize().x / 2 - offset, 100 + window.getSize().y / 3 + 90);     // place the created button on the screen

    auto &but2 = settingsMenu.addButton(uiFont, "Music", 80, false, false, "", "music"); // add new button to the created menu
    offset = but2.getButtonRect().width / 2;                                             // set button offset
    but2.setPos(window.getSize().x / 2 - offset, 100 + window.getSize().y / 3 + 180);    // place the created button on the screen

    auto &but3 = settingsMenu.addButton(uiFont, "Back", 80, false, false, "main");    // add new button to the created menu
    offset = but3.getButtonRect().width / 2;                                          // set button offset
    but3.setPos(window.getSize().x / 2 - offset, 100 + window.getSize().y / 3 + 270); // place the created button on the screen
}

void createGameOverMenu(MenuHandler &handler, Font &uiFont, RenderWindow &window)
{
    auto &gameOverMenu = handler.createMenu(uiFont, "gameover", "", 100); // create new object in menus list

    // auto &but1 = gameOverMenu.addButton(uiFont, "Restart", 80, true);                // add new button to the created menu
    // float offset = but1.getButtonRect().width / 2;                                   // set button offset
    // but1.setPos(window.getSize().x / 2 - offset, 100 + window.getSize().y / 3 + 90); // place the created button on the screen

    // auto &but2 = gameOverMenu.addButton(uiFont, "Main Menu", 80, false, false, "main"); // add new button to the created menu
    // offset = but2.getButtonRect().width / 2;                                            // set button offset
    // but2.setPos(window.getSize().x / 2 - offset, 100 + window.getSize().y / 3 + 180);   // place the created button on the screen

    auto &but3 = gameOverMenu.addButton(uiFont, "Exit", 80, false, true);             // add new button to the created menu
    float offset = but3.getButtonRect().width / 2;                                    // set button offset
    but3.setPos(window.getSize().x / 2 - offset, 100 + window.getSize().y / 3 + 270); // add new button to the created menu
}

void addMenus(MenuHandler &handler, Font &uiFont, RenderWindow &window)
{
    createMainMenu(handler, uiFont, window);     // create main menu in menu handler
    createSettingsMenu(handler, uiFont, window); // create settings menu in menu handler
    createGameOverMenu(handler, uiFont, window); // create gameover menu in manu handler
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
    //------------------------------------------------------------------------------

    MenuHandler handler;                           // create an instance of menu handler class
    handler.addChangeableParameter("sound", true); // add variable parameter to menu handler instance
    handler.addChangeableParameter("music", true);
    addMenus(handler, r.font, window); // create menus

    //------------------------------------------------------------------------------

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

        //------------------------------------------------------------------------------

        if (handler.active()) // if menu is active
        {
            handleMenuFrame(event, handler, window, r); // handle user actions in menu
        }
        else if (!is_game_over)
        {
            if (rooms.getIsBossRoom())
                r.updateSong(0);
            else
                r.updateSong(1);
            //------------------------------------------------------------------------------

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
            handler.setMenuActive("gameover"); // select gameover menu
            std::string title_string = is_won ? "You won!!!" : "You lose(((";
            handler.getCurrentMenu()->title.setString(title_string);                                              // set string (total score)
            float offset = handler.getCurrentMenu()->getTitleRect().width / 2;                                    // centering the string
            handler.getCurrentMenu()->setTitlePos(window.getSize().x / 2 - offset, 100 + window.getSize().y / 4); // set string position on the screen
        }
    }

    return 0;
}
