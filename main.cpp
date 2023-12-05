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

    Font font;
    font.loadFromFile("arial.ttf");
    sf::Image player1_img, player2_img;
    player1_img.loadFromFile("player1.png");
    player2_img.loadFromFile("player2.png");
    sf::Texture player_texture;
    player_texture.loadFromImage(player1_img);
    bool is_1st_texture = true;
    sf::Sprite player_spite;
    player_spite.setTexture(player_texture);

    std::vector<Sprite> item_sprites; // TODO заполнить вектор
    sf::Sprite curr_sprite;
    sf::Texture sword1_texture, potion1_texture;
    sword1_texture.loadFromFile("sword1.png");
    potion1_texture.loadFromFile("potion1.png");
    curr_sprite.setTexture(sword1_texture);
    item_sprites.push_back(curr_sprite);
    curr_sprite.setTexture(potion1_texture);
    item_sprites.push_back(curr_sprite);

    CellMtrx cell_mtrx;
    generateEmptyRoom(cell_mtrx);
    Player player(1, 4, 100);

    sf::Clock anim_clock;
    while (window.isOpen())
    {
        sf::Event event;
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
        drawEntity(window, player, player_spite);
        drawInventory(window, font, player, item_sprites);

        window.display();

        if (anim_clock.getElapsedTime().asMilliseconds() > 500)
        {
            if (is_1st_texture)
                player_texture.loadFromImage(player2_img);
            else
                player_texture.loadFromImage(player1_img);
            is_1st_texture = !is_1st_texture;
            anim_clock.restart();
        }
    }

    return 0;
}
