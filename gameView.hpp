#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "gameLogic.hpp"

void drawRoom(sf::RenderWindow &window, CellMtrx cell_mtrx);

void drawEntity(sf::RenderWindow &window, Entity &entity, sf::Sprite &sprite);

void drawInventory(sf::RenderWindow &window, sf::Font &font, Player &player, std::vector<sf::Sprite> &item_sprites);