#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

class GameRes
{
private:
    bool is_1st_texture = true;
    sf::Image player1_img, player2_img, enemy1_img, enemy2_img;
    sf::Texture player_texture, enemy_texture;
    sf::Texture sword1_texture, potion1_texture;

public:
    Font font;
    sf::Sprite player_spite;
    std::vector<Sprite> item_sprites;        // TODO заполнить вектор
    std::vector<Sprite> item_ground_sprites; // TODO заполнить вектор
    std::vector<Sprite> enemy_sprites;       // TODO заполнить вектор

    GameRes();
    void animateSprites(Clock &anim_clock);
};
