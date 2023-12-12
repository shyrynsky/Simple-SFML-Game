#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using namespace sf;

class GameRes
{
private:
    bool is_1st_texture = true;
    sf::Image player1_img, player2_img; //, enemy1_img, enemy2_img;
    sf::Texture player_texture;         // , enemy_texture;
    std::vector<sf::Image> enemy_image_arr;
    std::vector<sf::Texture> enemy_texture_arr;
    // sf::Texture sword1_texture, sword2_texture, sword3_texture, sword4_texture,
    //     potion1_texture;
    std::vector<sf::Texture> items_texture_arr;

public:
    Font font;
    sf::Sprite player_spite;
    std::vector<Sprite> item_sprites;        // TODO заполнить вектор
    std::vector<Sprite> item_ground_sprites; // TODO заполнить вектор
    std::vector<Sprite> enemy_sprites;       // TODO заполнить вектор

    GameRes();
    void animateSprites(Clock &anim_clock);
};
