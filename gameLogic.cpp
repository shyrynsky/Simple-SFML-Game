#include "gameLogic.hpp"

Entity::Entity(int a_x, int a_y, int a_helth)
{
    x = a_x;
    y = a_y;
    health = a_helth;
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

Player::Player(int a_x, int a_y, int a_helth) : Entity(a_x, a_y, a_helth) {}

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
