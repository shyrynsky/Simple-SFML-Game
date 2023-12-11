#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "gameField.hpp"
#include "gameLogic.hpp"

using namespace sf;

void drawRoom(RenderWindow &window, CellMtrx cell_mtrx);

void drawEntity(RenderWindow &window, Entity &entity, Sprite &sprite, Clock &figth_clock);

void drawEnemyList(RenderWindow &window, std::list<Enemy> &enemy_list, std::vector<Sprite> &enemy_sprites, Clock &figth_clock);

void drawGroundItemList(RenderWindow &window, std::list<GroundItem> &ground_item_list, std::vector<Sprite> &item_ground_sprites);

void drawInventory(RenderWindow &window, Font &font, Player &player, std::vector<Sprite> &item_sprites);

void drawMiniMap(RenderWindow &window, Rooms &rooms);