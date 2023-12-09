#include "gameRes.hpp"

GameRes::GameRes()
{
    sf::Sprite curr_enemy_sprite;
    sf::Sprite curr_item_sprite;
    font.loadFromFile("arial.ttf");

    player1_img.loadFromFile("player1.png");
    player2_img.loadFromFile("player2.png");
    player_texture.loadFromImage(player1_img);
    player_spite.setTexture(player_texture);

    enemy1_img.loadFromFile("enemy1.png");
    enemy2_img.loadFromFile("enemy2.png");
    enemy_texture.loadFromImage(enemy1_img);
    curr_enemy_sprite.setTexture(enemy_texture); // id 0
    enemy_sprites.push_back(curr_enemy_sprite);

    sword1_texture.loadFromFile("sword1.png");
    potion1_texture.loadFromFile("potion1.png");

    curr_item_sprite.setTexture(sword1_texture); // id 0
    item_sprites.push_back(curr_item_sprite);
    curr_item_sprite.setTexture(potion1_texture); // id 1
    item_sprites.push_back(curr_item_sprite);
}