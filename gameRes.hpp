#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using namespace sf;

class GameRes
{
private:
    bool is_1st_texture = true;
    sf::Image player1_img, player2_img;
    sf::Texture player_texture;
    std::vector<sf::Image> enemy_image_arr;
    std::vector<sf::Texture> enemy_texture_arr;
    std::vector<sf::Texture> items_texture_arr;

public:
    Font font;
    sf::Sprite player_spite;
    std::vector<Sprite> item_sprites;
    std::vector<Sprite> item_ground_sprites;
    std::vector<Sprite> enemy_sprites;

    GameRes();
    void animateSprites(Clock &anim_clock);
};
