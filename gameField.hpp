#pragma once
#define ROOM_SIZE 9
#define MAP_SIZE 5

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

typedef CellType CellMtrx[ROOM_SIZE][ROOM_SIZE];

struct Room
{
    CellMtrx cell_mtrx;
    bool is_discovered;
};

typedef Room RoomsMtrx[MAP_SIZE][MAP_SIZE];

class Rooms
{
private:
    RoomsMtrx rooms_mtrx;
    int active_room_x;
    int active_room_y;

public:
    Rooms();

    CellMtrx cell_mtrx;
    void generateEmptyRoom();
    void closeRoom();
    void openRoom();
};