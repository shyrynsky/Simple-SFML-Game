#pragma once
#include <string>
// #include <vector>
#include <list>

#define ROOM_SIZE 9
#define INVENTORY_SIZE 6

enum CellType
{
    ctCell,
    ctWall,
    ctDoor,
    // ctPlayer,
    // ctEnemy
    ctStartSearch,
    ctEndSearch = -1
};

enum Direction
{
    dirUp,
    dirDown,
    dirLeft,
    dirRight,
    dirUnknown
};

typedef CellType CellMtrx[ROOM_SIZE][ROOM_SIZE];
typedef int SearchMatrix[ROOM_SIZE][ROOM_SIZE];

struct Item
{
    int id;
    std::string name;
    enum Type
    {
        tUndef,
        tWeapon,
        tPotion
    } type;
    union Prop
    {
        int damage;
        int health;
    } prop;
};

class Enemy;

class Entity
{
protected:
    int max_health, health;
    int x, y;
    int damage;
    Direction last_atack_dir;
    auto isEnemy(std::list<Enemy> &enemy_list, int a_x, int a_y);

public:
    Entity(int a_x, int a_y, int a_max_helth);

    int getX();
    int getY();
    int getHealth();
    void setHealth(int a_health);
    int getMaxHealth();
    Direction getLastAttackDir();
};

class Player : public Entity
{
private:
    Item items[INVENTORY_SIZE];
    int active_item;

public:
    Player(int a_x, int a_y, int a_max_helth);

    Item *getItems();
    int getActiveItem();

    void changeActiveItem(int number);
    void move(CellMtrx cell_mtrx, Direction direction, std::list<Enemy> &enemy_list);
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
};

void generateEmptyRoom(CellMtrx cell_mtrx);