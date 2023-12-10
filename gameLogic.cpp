#include "gameLogic.hpp"

Entity::Entity(int a_x, int a_y, int a_max_helth)
{
    x = a_x;
    y = a_y;
    max_health = a_max_helth;
    health = a_max_helth;
    last_atack_dir = dirUnknown;
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

void Entity::setHealth(int a_health)
{
    health = a_health;
}

int Entity::getMaxHealth()
{
    return max_health;
}

Direction Entity::getLastAttackDir()
{
    return last_atack_dir;
}

Player::Player(int a_x, int a_y, int a_max_helth) : Entity(a_x, a_y, a_max_helth)
{
    damage = 1;

    Item empty_item;
    empty_item.id = -1;
    empty_item.name = "";
    empty_item.type = Item::Type::tUndef;

    items[0].id = 0;
    items[0].name = "обычный меч";
    items[0].type = Item::tWeapon;
    items[0].prop.damage = 10;

    items[5].id = 1;
    items[5].name = "малое зелье здоровья";
    items[5].type = Item::tPotion;
    items[5].prop.health = 30;

    health = max_health;

    for (int i = 1; i < INVENTORY_SIZE - 1; i++)
    {
        items[i] = empty_item;
    }
    changeActiveItem(1);
}

Item *Player::getItems()
{
    return items;
}

int Player::getActiveItem()
{
    return active_item;
}

auto Entity::isEnemy(std::list<Enemy> &enemy_list, int a_x, int a_y)
{
    for (auto iter = enemy_list.begin(); iter != enemy_list.end(); iter++)
    {
        if (iter->getX() == a_x && iter->getY() == a_y)
        {
            return iter;
        }
    }
    return enemy_list.end();
}

void Player::move(Rooms &rooms, Direction direction, std::list<Enemy> &enemy_list) // TODO сделать bool
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

    if (rooms.cell_mtrx[next_y][next_x] == ctCell)
    {
        auto enemy_iter = isEnemy(enemy_list, next_x, next_y);
        if (enemy_iter != enemy_list.end())
        {
            int enemy_health = enemy_iter->getHealth();
            if (enemy_health >= damage)
                enemy_iter->setHealth(enemy_health - damage);
            else
            {
                x = next_x;
                y = next_y;
                enemy_list.erase(enemy_iter);
                if (enemy_list.size() == 0)
                    rooms.openRoom();
            }
            last_atack_dir = direction;
            return;
        }
        else
        {
            x = next_x;
            y = next_y;
        }
    }
    last_atack_dir = dirUnknown;
}

void Player::changeActiveItem(int number)
{
    active_item = number;
    if (items[number - 1].type == Item::tWeapon)
        damage = items[number - 1].prop.damage;
    else if (items[number - 1].type == Item::tPotion)
    {
        int curr_health = health + items[number - 1].prop.health;
        health = curr_health > max_health ? max_health : curr_health;
        items[number - 1].type = Item::tUndef;
        damage = 1;
    }
    else
        damage = 1;
}

Enemy::Enemy(int a_x, int a_y, int a_max_helth, int a_damage, int a_id) : Entity(a_x, a_y, a_max_helth)
{
    damage = a_damage;
    id = a_id;
}

int Enemy::getId()
{
    return id;
}

bool Enemy::IsFindedEnd(SearchMatrix path_matrix, int wave_stage, int end_x, int end_y)
{
    if ((end_y - 1 >= 0) && path_matrix[end_y - 1][end_x] == wave_stage)
    {
        return true;
    }
    if ((end_x - 1 >= 0) && path_matrix[end_y][end_x - 1] == wave_stage)
    {
        return true;
    }
    if ((end_y + 1 < ROOM_SIZE) && path_matrix[end_y + 1][end_x] == wave_stage)
    {
        return true;
    }
    if ((end_x + 1 < ROOM_SIZE) && path_matrix[end_y][end_x + 1] == wave_stage)
    {
        return true;
    }
    return false;
}

bool Enemy::Wave(SearchMatrix path_matrix, int a_x, int a_y, int wave_stage)
{
    bool result = false;
    wave_stage++;
    if ((a_x - 1 >= 0) && path_matrix[a_x - 1][a_y] == ctCell)
    {
        path_matrix[a_x - 1][a_y] = wave_stage;
        result = true;
    }
    if ((a_y - 1 >= 0) && path_matrix[a_x][a_y - 1] == ctCell)
    {
        path_matrix[a_x][a_y - 1] = wave_stage;
        result = true;
    }
    if ((a_x + 1 < ROOM_SIZE) && path_matrix[a_x + 1][a_y] == ctCell)
    {
        path_matrix[a_x + 1][a_y] = wave_stage;
        result = true;
    }
    if ((a_y + 1 < ROOM_SIZE) && path_matrix[a_x][a_y + 1] == ctCell)
    {
        path_matrix[a_x][a_y + 1] = wave_stage;
        result = true;
    }
    return result;
}

void Enemy::move(CellMtrx cell_mtrx, Entity &player, std::list<Enemy> &enemy_list) // потестить бы
{
    int player_x = player.getX();
    int player_y = player.getY();
    SearchMatrix search_mtrx;
    for (int i = 0; i < ROOM_SIZE; i++)
    {
        for (int j = 0; j < ROOM_SIZE; j++)
        {
            if (cell_mtrx[i][j] == ctCell && isEnemy(enemy_list, j, i) == enemy_list.end())
                search_mtrx[i][j] = (int)ctCell;
            else
                search_mtrx[i][j] = (int)ctWall;
        }
    }
    search_mtrx[y][x] = ctStartSearch;
    search_mtrx[player_y][player_x] = ctEndSearch;

    int wave_stage = ctStartSearch;
    bool is_deadend = false;
    while (!is_deadend && !IsFindedEnd(search_mtrx, wave_stage, player_x, player_y))
    {
        is_deadend = true;
        for (int i = 0; i < ROOM_SIZE; i++)
        {
            for (int j = 0; j < ROOM_SIZE; j++)
            {
                if (search_mtrx[i][j] == wave_stage)
                {
                    if (Wave(search_mtrx, i, j, wave_stage))
                        is_deadend = false;
                }
            }
        }
        wave_stage++;
    }
    if (is_deadend)
        return;
    int next_x = player_x;
    int next_y = player_y;
    for (int i = wave_stage; i > ctStartSearch; i--)
    {
        if ((next_x - 1 >= 0) && search_mtrx[next_y][next_x - 1] == i)
        {
            next_x -= 1;
        }
        if ((next_y - 1 >= 0) && search_mtrx[next_y - 1][next_x] == i)
        {
            next_y -= 1;
        }
        if ((next_x + 1 < ROOM_SIZE) && search_mtrx[next_y][next_x + 1] == i)
        {
            next_x += 1;
        }
        if ((next_y + 1 < ROOM_SIZE) && search_mtrx[next_y + 1][next_x] == i)
        {
            next_y += 1;
        }
    }

    if (next_x == player_x && next_y == player_y)
    {
        int player_health = player.getHealth();
        if (player_health >= damage)
            player.setHealth(player_health - damage);
        else
        {
            // конец игры
            exit(EXIT_SUCCESS);
        }
        Direction direction = dirUnknown;
        if (next_x > x)
            direction = dirRight;
        if (next_x < x)
            direction = dirLeft;
        if (next_y > y)
            direction = dirDown;
        if (next_y < y)
            direction = dirUp;
        last_atack_dir = direction;
        return;
    }
    else
    {
        x = next_x;
        y = next_y;
    }
    last_atack_dir = dirUnknown;
}

void Enemy::moveEnemyList(CellMtrx cell_mtrx, std::list<Enemy> &enemy_list, Entity &player)
{
    for (Enemy &enemy : enemy_list)
    {
        enemy.move(cell_mtrx, player, enemy_list);
    }
}

// void generateEmptyRoom(CellMtrx cell_mtrx)
// {
//     for (int column = 0; column < ROOM_SIZE; column++)
//     {
//         if (column != ROOM_SIZE / 2)
//             cell_mtrx[0][column] = ctWall;
//         else
//             cell_mtrx[0][column] = ctCell;
//     }
//     for (int row = 1; row < ROOM_SIZE - 1; row++)
//     {
//         if (row != ROOM_SIZE / 2)
//             cell_mtrx[row][0] = ctWall;
//         else
//             cell_mtrx[row][0] = ctCell;
//         for (int column = 1; column < ROOM_SIZE - 1; column++)
//         {
//             cell_mtrx[row][column] = ctCell;
//         }
//         if (row != ROOM_SIZE / 2)
//             cell_mtrx[row][ROOM_SIZE - 1] = ctWall;
//         else
//             cell_mtrx[row][ROOM_SIZE - 1] = ctCell;
//     }
//     for (int column = 0; column < ROOM_SIZE; column++)
//     {
//         if (column != ROOM_SIZE / 2)
//             cell_mtrx[ROOM_SIZE - 1][column] = ctWall;
//         else
//             cell_mtrx[ROOM_SIZE - 1][column] = ctCell;
//     }
// }

// void closeRoom(CellMtrx cell_mtrx)
// {
//     if (cell_mtrx[0][ROOM_SIZE / 2] == ctCell)
//         cell_mtrx[0][ROOM_SIZE / 2] = ctDoor;

//     if (cell_mtrx[ROOM_SIZE - 1][ROOM_SIZE / 2] == ctCell)
//         cell_mtrx[ROOM_SIZE - 1][ROOM_SIZE / 2] = ctDoor;

//     if (cell_mtrx[ROOM_SIZE / 2][0] == ctCell)
//         cell_mtrx[ROOM_SIZE / 2][0] = ctDoor;

//     if (cell_mtrx[ROOM_SIZE / 2][ROOM_SIZE - 1] == ctCell)
//         cell_mtrx[ROOM_SIZE / 2][ROOM_SIZE - 1] = ctDoor;
// }

// void openRoom(CellMtrx cell_mtrx)
// {
//     if (cell_mtrx[0][ROOM_SIZE / 2] == ctDoor)
//         cell_mtrx[0][ROOM_SIZE / 2] = ctCell;

//     if (cell_mtrx[ROOM_SIZE - 1][ROOM_SIZE / 2] == ctDoor)
//         cell_mtrx[ROOM_SIZE - 1][ROOM_SIZE / 2] = ctCell;

//     if (cell_mtrx[ROOM_SIZE / 2][0] == ctDoor)
//         cell_mtrx[ROOM_SIZE / 2][0] = ctCell;

//     if (cell_mtrx[ROOM_SIZE / 2][ROOM_SIZE - 1] == ctDoor)
//         cell_mtrx[ROOM_SIZE / 2][ROOM_SIZE - 1] = ctCell;
// }