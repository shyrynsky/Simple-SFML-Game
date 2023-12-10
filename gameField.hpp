#pragma once
#include <stdlib.h>

#define ROOM_SIZE 9
#define MAP_SIZE 7

#include "gameTemplates.hpp"

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
    bool is_room;
};

typedef Room RoomsMtrx[MAP_SIZE][MAP_SIZE];

class Rooms
{
private:
    int active_room_x;
    int active_room_y;
    int rooms_quantity;
    bool isOneNeighbor(int curr_x, int curr_y);
    void _generateMap(int curr_x, int curr_y);
    void useTemplates(int curr_x, int curr_y);

public:
    RoomsMtrx rooms_mtrx;
    Rooms();
    int getActiveRoomX();
    int getActiveRoomY();
    bool getIsRoomDiscovered();
    void setIsRoomDiscovered(bool is_discovered);

    CellMtrx cell_mtrx;
    bool changeActiveRoom(int new_room_x, int new_room_y);
    void generateEmptyRoom(int curr_x, int curr_y);
    void generateMap();
    void closeRoom();
    void openRoom();
};