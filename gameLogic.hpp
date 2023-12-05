#pragma once
#include <string>

#define ROOM_SIZE 9
#define INVENTORY_SIZE 6

enum CellType
{
    ctCell,
    ctWall,
    ctDoor
    // ctPlayer,
    // ctEnemy
};

enum Direction
{
    dirUp,
    dirDown,
    dirLeft,
    dirRight
};

typedef CellType CellMtrx[ROOM_SIZE][ROOM_SIZE];

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

// class Inventory
// {
// private:

// public:
//     Inventory();

// };

class Entity
{
protected:
    int max_health, health;
    int x, y;

public:
    Entity(int a_x, int a_y, int a_max_helth);

    int getX();
    int getY();
    int getHealth();
    int getMaxHealth();
};

class Player : public Entity
{
private:
    Item items[INVENTORY_SIZE];
    int active_item;
    int damage;

public:
    Player(int a_x, int a_y, int a_max_helth);

    Item *getItems();
    int getActiveItem();

    void changeActiveItem(int number);
    void move(CellMtrx cell_mtrx, Direction direction);
};

void generateEmptyRoom(CellMtrx cell_mtrx);