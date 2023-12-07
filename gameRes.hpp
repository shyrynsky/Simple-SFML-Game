#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

class GameRes
{
private:
    /* data */
public:
    Font font;
    sf::Image player1_img, player2_img, enemy1_img, enemy2_img;
    sf::Texture player_texture, enemy_texture;
    sf::Sprite player_spite, enemy_sprite;

    std::vector<Sprite> item_sprites; // TODO заполнить вектор
    sf::Sprite curr_sprite;
    sf::Texture sword1_texture, potion1_texture;

    GameRes();
};
