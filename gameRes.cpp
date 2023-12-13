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

    std::vector<std::string> enemy_path = {"enemy1.png", "enemy2.png",
                                           "enemy3.png", "enemy4.png",
                                           "enemy5.png", "enemy6.png",
                                           "boss1.png", "boss2.png"};
    enemy_image_arr.resize(enemy_path.size());
    for (int i = 0; i < enemy_path.size(); i++)
    {
        enemy_image_arr[i].loadFromFile(enemy_path[i]);
    }
    enemy_texture_arr.resize(enemy_path.size() / 2);
    for (int i = 0; i < enemy_path.size(); i += 2)
    {
        enemy_texture_arr[i / 2].loadFromImage(enemy_image_arr[i]);
        curr_enemy_sprite.setTexture(enemy_texture_arr[i / 2]);
        enemy_sprites.push_back(curr_enemy_sprite);
    }

    std::vector<std::string> item_path = {"sword1.png", "sword2.png",
                                          "sword3.png", "sword4.png",
                                          "potion1.png", "potion2.png",
                                          "potion3.png", "potion4.png"};
    items_texture_arr.resize(item_path.size());
    for (int i = 0; i < item_path.size(); i++)
    {
        items_texture_arr[i].loadFromFile(item_path[i]);
        curr_item_sprite.setTexture(items_texture_arr[i]);
        item_sprites.push_back(curr_item_sprite);
    }
    curr_item_sprite.setScale(0.6, 0.6);
    for (int i = 0; i < item_path.size(); i++)
    {
        curr_item_sprite.setTexture(items_texture_arr[i]);
        item_ground_sprites.push_back(curr_item_sprite);
    }

    hitBuff.loadFromFile("hit.wav");
    hitSound.setBuffer(hitBuff);
    songs[0] = "music1.mp3";
    songs[1] = "music2.mp3";
    // for (int i = 0; i < 2; i++)
    //     songs[i] = "music" + std::to_string(i + 1) + ".mp3";
}

void GameRes::animateSprites(Clock &anim_clock)
{
    if (anim_clock.getElapsedTime().asMilliseconds() > 500)
    {
        if (is_1st_texture)
        {
            player_texture.loadFromImage(player2_img);
            for (int i = 0; i < enemy_image_arr.size(); i += 2)
                enemy_texture_arr[i / 2].loadFromImage(enemy_image_arr[i + 1]);
        }
        else
        {
            player_texture.loadFromImage(player1_img);
            for (int i = 1; i < enemy_image_arr.size(); i += 2)
                enemy_texture_arr[i / 2].loadFromImage(enemy_image_arr[i - 1]);
        }
        is_1st_texture = !is_1st_texture;
        anim_clock.restart();
    }
}

void GameRes::resetSong() // this method stops the current song
{
    currSong.stop();
}

void GameRes::updateSong(const int &sPos) // this method updates song
{
    static int pred_song = -1;
    if (onMusic)
    {                                                                          // if user turned the music on
        if (currSong.getStatus() == SoundSource::Stopped || sPos != pred_song) // if current song is stopped
        {
            pred_song = sPos;
            currSong.openFromFile(songs[sPos]); // open song file from directory
            currSong.play();                    // play this file
        }
    }
    // else
    // {
    //     if (pred_song != -1)
    //     {
    //         currSong.stop();
    //         pred_song = -1;
    //     }
    // }
}

void GameRes::playHit() // this method plays hit sound
{
    if (onSound)
        hitSound.play();
}

void GameRes::setSFXStatus(const bool &sound, const bool &music) // this method sets music and sound status (on/off)
{
    onSound = sound;
    onMusic = music;
}