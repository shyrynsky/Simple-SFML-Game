#pragma once
#include <SFML/Graphics.hpp>
#include "gameLogic.hpp"

void drawRoom(sf::RenderWindow &window, CellMtrx cell_mtrx);

void drawEntity(sf::RenderWindow &window, Entity &entity, sf::Sprite &sprite);