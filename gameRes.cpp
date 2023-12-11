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

    curr_item_sprite.setScale(0.6, 0.6);
    curr_item_sprite.setTexture(sword1_texture);
    item_ground_sprites.push_back(curr_item_sprite);
    curr_item_sprite.setTexture(potion1_texture);
    item_ground_sprites.push_back(curr_item_sprite);
}

void GameRes::animateSprites(Clock &anim_clock)
{
    if (anim_clock.getElapsedTime().asMilliseconds() > 500)
    {
        if (is_1st_texture)
        {
            player_texture.loadFromImage(player2_img);
            enemy_texture.loadFromImage(enemy2_img);
        }
        else
        {
            player_texture.loadFromImage(player1_img);
            enemy_texture.loadFromImage(enemy1_img);
        }
        is_1st_texture = !is_1st_texture;
        anim_clock.restart();
    }
}