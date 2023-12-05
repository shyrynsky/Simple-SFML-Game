#include "gameLogic.hpp"

Entity::Entity(int a_x, int a_y, int a_max_helth)
{
    x = a_x;
    y = a_y;
    max_health = a_max_helth;
    health = a_max_helth;
}

int Entity::getX()
{
    return x;
}

int Entity::getY()
{
    return y;
}

int Entity::getHealth()
{
    return health;
}

int Entity::getMaxHealth()
{
    return max_health;
}

Player::Player(int a_x, int a_y, int a_max_helth) : Entity(a_x, a_y, a_max_helth) {}

void Player::move(CellMtrx cell_mtrx, Direction direction)
{
    int next_x = x;
    int next_y = y;
    switch (direction)
    {
    case dirLeft:
        if (next_x > 0)
            next_x--;
        break;
    case dirUp:
        if (next_y > 0)
            next_y--;
        break;
    case dirDown:
        if (next_y < ROOM_SIZE - 1)
            next_y++;
        break;
    case dirRight:
        if (next_x < ROOM_SIZE - 1)
            next_x++;
        break;
    }

    if (cell_mtrx[next_y][next_x] == ctCell)
    {
        x = next_x;
        y = next_y;
    }
}

Inventory::Inventory()
{
    Item empty_item;
    empty_item.id = -1;
    empty_item.name = "";
    empty_item.type = Item::Type::tUndef;
    for (int i = 0; i < INVENTORY_SIZE; i++)
    {
        items[i] = empty_item;
    }
    active_item = 1;
}

Item *Inventory::getItems()
{
    return items;
}

int Inventory::getActiveItem()
{
    return active_item;
}

void Inventory::changeActiveItem(int number)
{
    active_item = number;
}

void generateEmptyRoom(CellMtrx cell_mtrx)
{
    for (int column = 0; column < ROOM_SIZE; column++)
    {
        if (column != ROOM_SIZE / 2)
            cell_mtrx[0][column] = ctWall;
        else
            cell_mtrx[0][column] = ctCell;
    }
    for (int row = 1; row < ROOM_SIZE - 1; row++)
    {
        if (row != ROOM_SIZE / 2)
            cell_mtrx[row][0] = ctWall;
        else
            cell_mtrx[row][0] = ctCell;
        for (int column = 1; column < ROOM_SIZE - 1; column++)
        {
            cell_mtrx[row][column] = ctCell;
        }
        if (row != ROOM_SIZE / 2)
            cell_mtrx[row][ROOM_SIZE - 1] = ctWall;
        else
            cell_mtrx[row][ROOM_SIZE - 1] = ctCell;
    }
    for (int column = 0; column < ROOM_SIZE; column++)
    {
        if (column != ROOM_SIZE / 2)
            cell_mtrx[ROOM_SIZE - 1][column] = ctWall;
        else
            cell_mtrx[ROOM_SIZE - 1][column] = ctCell;
    }
}
