#include "gameField.hpp"
Rooms::Rooms()
{
    generateMap();
    changeActiveRoom(active_room_x, active_room_y);
    setIsRoomDiscovered(true);
}

int Rooms::getActiveRoomX()
{
    return active_room_x;
}
int Rooms::getActiveRoomY()
{
    return active_room_y;
}

bool Rooms::getIsRoomDiscovered()
{
    return rooms_mtrx[active_room_y][active_room_x].is_discovered;
}

bool Rooms::getIsBossRoom()
{
    return rooms_mtrx[active_room_y][active_room_x].is_boss_room;
}

bool Rooms::getIsTreasure()
{
    return rooms_mtrx[active_room_y][active_room_x].is_treasure;
}

void Rooms::setIsRoomDiscovered(bool is_discovered)
{
    rooms_mtrx[active_room_y][active_room_x].is_discovered = is_discovered;
}

bool Rooms::changeActiveRoom(int new_room_x, int new_room_y)
{
    if (!rooms_mtrx[new_room_y][new_room_x].is_room)
        return false;
    for (int i = 0; i < ROOM_SIZE; i++)
    {
        for (int j = 0; j < ROOM_SIZE; j++)
        {
            cell_mtrx[i][j] = rooms_mtrx[new_room_y][new_room_x].cell_mtrx[i][j];
        }
    }
    active_room_x = new_room_x;
    active_room_y = new_room_y;
    return true;
}

void Rooms::generateEmptyRoom(int curr_x, int curr_y)
{
    for (int column = 0; column < ROOM_SIZE; column++)
    {
        if (column == ROOM_SIZE / 2 && curr_y > 0 && rooms_mtrx[curr_y - 1][curr_x].is_room)
            rooms_mtrx[curr_y][curr_x].cell_mtrx[0][column] = ctCell;
        else
            rooms_mtrx[curr_y][curr_x].cell_mtrx[0][column] = ctWall;
    }
    for (int row = 1; row < ROOM_SIZE - 1; row++)
    {
        if (row == ROOM_SIZE / 2 && curr_x > 0 && rooms_mtrx[curr_y][curr_x - 1].is_room)
            rooms_mtrx[curr_y][curr_x].cell_mtrx[row][0] = ctCell;
        else
            rooms_mtrx[curr_y][curr_x].cell_mtrx[row][0] = ctWall;
        for (int column = 1; column < ROOM_SIZE - 1; column++)
        {
            rooms_mtrx[curr_y][curr_x].cell_mtrx[row][column] = ctCell;
        }
        if (row == ROOM_SIZE / 2 && curr_x < MAP_SIZE - 1 && rooms_mtrx[curr_y][curr_x + 1].is_room)
            rooms_mtrx[curr_y][curr_x].cell_mtrx[row][ROOM_SIZE - 1] = ctCell;
        else
            rooms_mtrx[curr_y][curr_x].cell_mtrx[row][ROOM_SIZE - 1] = ctWall;
    }
    for (int column = 0; column < ROOM_SIZE; column++)
    {
        if (column == ROOM_SIZE / 2 && curr_y < MAP_SIZE - 1 && rooms_mtrx[curr_y + 1][curr_x].is_room)
            rooms_mtrx[curr_y][curr_x].cell_mtrx[ROOM_SIZE - 1][column] = ctCell;
        else
            rooms_mtrx[curr_y][curr_x].cell_mtrx[ROOM_SIZE - 1][column] = ctWall;
    }
}

bool Rooms::isOneNeighbor(int curr_x, int curr_y)
{
    int neighbors = 0;

    if (curr_x > 0 && rooms_mtrx[curr_y][curr_x - 1].is_room)
    {
        neighbors++;
    }
    if (curr_y > 0 && rooms_mtrx[curr_y - 1][curr_x].is_room)
    {
        neighbors++;
    }
    if (curr_x < MAP_SIZE - 1 && rooms_mtrx[curr_y][curr_x + 1].is_room)
    {
        neighbors++;
    }
    if (curr_y < MAP_SIZE - 1 && rooms_mtrx[curr_y + 1][curr_x].is_room)
    {
        neighbors++;
    }

    return neighbors == 1;
}

void Rooms::_generateMap(int curr_x, int curr_y)
{
    if (rooms_mtrx[curr_y][curr_x].is_room == false)
        rooms_quantity++;
    rooms_mtrx[curr_y][curr_x].is_room = true;
    bool is_new_room = rand() % 2;
    if (curr_x > 0 && //! rooms_mtrx[curr_y][curr_x - 1].is_room &&
        isOneNeighbor(curr_x - 1, curr_y) && is_new_room)
    {
        _generateMap(curr_x - 1, curr_y);
    }
    is_new_room = rand() % 2;
    if (curr_y > 0 && //! rooms_mtrx[curr_y - 1][curr_x].is_room &&
        isOneNeighbor(curr_x, curr_y - 1) && is_new_room)
    {
        _generateMap(curr_x, curr_y - 1);
    }
    is_new_room = rand() % 2;
    if (curr_x < MAP_SIZE - 1 && //! rooms_mtrx[curr_y][curr_x + 1].is_room &&
        isOneNeighbor(curr_x + 1, curr_y) && is_new_room)
    {
        _generateMap(curr_x + 1, curr_y);
    }
    is_new_room = rand() % 2;
    if (curr_y < MAP_SIZE - 1 && //! rooms_mtrx[curr_y + 1][curr_x].is_room &&
        isOneNeighbor(curr_x, curr_y + 1) && is_new_room)
    {
        _generateMap(curr_x, curr_y + 1);
    }
}

void Rooms::generateMap()
{
    rooms_quantity = 0;
    active_room_x = MAP_SIZE / 2;
    active_room_y = MAP_SIZE / 2;
    for (int i = 0; i < MAP_SIZE; i++)
    {
        for (int j = 0; j < MAP_SIZE; j++)
        {
            rooms_mtrx[i][j].is_room = false;
            rooms_mtrx[i][j].is_discovered = false;
            rooms_mtrx[i][j].is_boss_room = false;
            rooms_mtrx[i][j].is_treasure = false;
        }
    }
    int i = 0;
    while (rooms_quantity < 10 && i < 10)
    {
        _generateMap(active_room_x, active_room_y);
        i++;
    }
    std::vector<std::pair<int, int>> poss_spec_room;

    for (int i = 0; i < MAP_SIZE; i++)
    {
        for (int j = 0; j < MAP_SIZE; j++)
        {
            if (rooms_mtrx[i][j].is_room == true)
            {
                generateEmptyRoom(j, i);
                if (active_room_x != j || active_room_y != i)
                {
                    useTemplates(j, i);
                    if (isOneNeighbor(j, i))
                        poss_spec_room.push_back({j, i});
                }
            }
        }
    }
    int n = rand() % poss_spec_room.size();
    int m = n;
    if (poss_spec_room.size() >= 2)
    {
        while (m == n)
            m = rand() % poss_spec_room.size();
        rooms_mtrx[poss_spec_room[m].second][poss_spec_room[m].first].is_treasure = true;
    }
    rooms_mtrx[poss_spec_room[n].second][poss_spec_room[n].first].is_boss_room = true;
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

void Rooms::useTemplates(int curr_x, int curr_y)
{
    int temp_numb = rand() % TEMPLATES_SIZE;
    for (int i = 0; i < ROOM_SIZE; i++)
    {
        for (int j = 0; j < ROOM_SIZE; j++)
        {
            if (templates[temp_numb][i][j] == 1)
                rooms_mtrx[curr_y][curr_x].cell_mtrx[i][j] = ctWall;
        }
    }
}