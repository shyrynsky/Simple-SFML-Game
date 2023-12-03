#pragma once

#define ROOM_SIZE 9

enum CellType
{
    ctCell,
    ctWall,
    ctDoor,
    ctPlayer,
    ctEnemy
};

typedef CellType CellMtrx[ROOM_SIZE][ROOM_SIZE];

void GenerateEmptyRoom(CellMtrx cell_mtrx);