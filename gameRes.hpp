#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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

    SoundBuffer hitBuff;
    Sound hitSound;
    std::string songs[2];
    Music currSong;
    bool onMusic, onSound;

public:
    Font font;
    sf::Sprite player_spite;
    std::vector<Sprite> item_sprites;
    std::vector<Sprite> item_ground_sprites;
    std::vector<Sprite> enemy_sprites;

    GameRes();
    void animateSprites(Clock &anim_clock);
    void playHit();
    void updateSong(const int &);
    void setSFXStatus(const bool &, const bool &);
    void resetSong();
};
