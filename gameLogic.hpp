#pragma once

#define ROOM_SIZE 9

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

class Entity
{
protected:
    int health;
    int x, y;

public:
    Entity(int a_x, int a_y, int a_helth);

    int getX();
    int getY();
    int getHealth();
};

class Player : public Entity
{
private:
    // weapon
public:
    Player(int a_x, int a_y, int a_helth);
    void move(CellMtrx cell_mtrx, Direction direction);
};

void generateEmptyRoom(CellMtrx cell_mtrx);