#pragma once
#include <string>
#include <list>
#include "gameSets.hpp"
#include "gameField.hpp"

#define INVENTORY_SIZE 6

enum Direction
{
    dirUp,
    dirDown,
    dirLeft,
    dirRight,
    dirUnknown
};

typedef int SearchMatrix[ROOM_SIZE][ROOM_SIZE];

class Entity;
class Enemy;

class GroundItem
{
private:
    int x, y;

public:
    Item item;

    GroundItem(int a_x, int a_y, Item a_item);

    int getX();
    int getY();

    static void SpawnGroundItemList(CellMtrx cell_mtrx,
                                    std::list<Enemy> &enemy_list,
                                    Entity &player,
                                    std::list<GroundItem> &ground_item_list);
};

class Entity
{
protected:
    int max_health, health;
    int x, y;
    int damage;
    Direction last_atack_dir;

public:
    Entity(int a_x, int a_y, int a_max_helth);

    int getX();
    int getY();
    int getHealth();
    void setHealth(int a_health);
    int getMaxHealth();
    Direction getLastAttackDir();
    static auto isEnemy(std::list<Enemy> &enemy_list, int a_x, int a_y);
};

class Player : public Entity
{
private:
    Item items[INVENTORY_SIZE];
    int active_item;

    auto isGroundItem(std::list<GroundItem> &ground_item_list, int a_x, int a_y);

public:
    Player(int a_x, int a_y, int a_max_helth);

    Item *getItems();
    int getActiveItem();

    void changeActiveItem(int number);
    void takeItems(std::list<GroundItem> &ground_item_list);
    bool moveNextRoom(Rooms &rooms, Direction direction, std::list<Enemy> &enemy_list, std::list<GroundItem> &ground_item_list);
    bool move(Rooms &rooms, Direction direction, std::list<Enemy> &enemy_list, std::list<GroundItem> &ground_item_list);
};

class Enemy : public Entity
{
private:
    int id;

    bool IsFindedEnd(SearchMatrix path_matrix, int wave_stage, int end_x, int end_y);
    bool Wave(SearchMatrix path_matrix, int a_x, int a_y, int wave_stage);

public:
    Enemy(int a_x, int a_y, int a_max_helth, int a_damage, int a_id);
    int getId();

    void move(CellMtrx cell_mtrx, Entity &player, std::list<Enemy> &enemy_list);
    static void moveEnemyList(CellMtrx cell_mtrx, std::list<Enemy> &enemy_list, Entity &player);
    static void SpawnEnemyList(CellMtrx cell_mtrx, std::list<Enemy> &enemy_list, Entity &player);
};