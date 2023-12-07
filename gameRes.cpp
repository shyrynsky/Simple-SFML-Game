#include "gameRes.hpp"

GameRes::GameRes()
{
    font.loadFromFile("arial.ttf");

    player1_img.loadFromFile("player1.png");
    player2_img.loadFromFile("player2.png");
    player_texture.loadFromImage(player1_img);
    player_spite.setTexture(player_texture);

    enemy1_img.loadFromFile("enemy1.png");
    enemy2_img.loadFromFile("enemy2.png");
    enemy_texture.loadFromImage(enemy1_img);
    enemy_sprite.setTexture(enemy_texture);

    sword1_texture.loadFromFile("sword1.png");
    potion1_texture.loadFromFile("potion1.png");

    curr_sprite.setTexture(sword1_texture); // id 0
    item_sprites.push_back(curr_sprite);
    curr_sprite.setTexture(potion1_texture); // id 1
    item_sprites.push_back(curr_sprite);
}