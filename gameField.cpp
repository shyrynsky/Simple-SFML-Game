#include "gameField.hpp"

Rooms::Rooms()
{
    active_room_x = -1;
    active_room_y = -1; // TODO
}

void Rooms::generateEmptyRoom()
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

void Rooms::closeRoom()
{
    if (cell_mtrx[0][ROOM_SIZE / 2] == ctCell)
        cell_mtrx[0][ROOM_SIZE / 2] = ctDoor;

    if (cell_mtrx[ROOM_SIZE - 1][ROOM_SIZE / 2] == ctCell)
        cell_mtrx[ROOM_SIZE - 1][ROOM_SIZE / 2] = ctDoor;

    if (cell_mtrx[ROOM_SIZE / 2][0] == ctCell)
        cell_mtrx[ROOM_SIZE / 2][0] = ctDoor;

    if (cell_mtrx[ROOM_SIZE / 2][ROOM_SIZE - 1] == ctCell)
        cell_mtrx[ROOM_SIZE / 2][ROOM_SIZE - 1] = ctDoor;
}

void Rooms::openRoom()
{
    if (cell_mtrx[0][ROOM_SIZE / 2] == ctDoor)
        cell_mtrx[0][ROOM_SIZE / 2] = ctCell;

    if (cell_mtrx[ROOM_SIZE - 1][ROOM_SIZE / 2] == ctDoor)
        cell_mtrx[ROOM_SIZE - 1][ROOM_SIZE / 2] = ctCell;

    if (cell_mtrx[ROOM_SIZE / 2][0] == ctDoor)
        cell_mtrx[ROOM_SIZE / 2][0] = ctCell;

    if (cell_mtrx[ROOM_SIZE / 2][ROOM_SIZE - 1] == ctDoor)
        cell_mtrx[ROOM_SIZE / 2][ROOM_SIZE - 1] = ctCell;
}