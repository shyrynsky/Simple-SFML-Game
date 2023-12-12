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

    health = max_health;

    for (int i = 0; i < INVENTORY_SIZE; i++)
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

auto Player::isGroundItem(std::list<GroundItem> &ground_item_list, int a_x, int a_y)
{
    for (auto iter = ground_item_list.begin(); iter != ground_item_list.end(); iter++)
    {
        if (iter->getX() == a_x && iter->getY() == a_y)
        {
            return iter;
        }
    }
    return ground_item_list.end();
}

void Player::takeItems(std::list<GroundItem> &ground_item_list)
{
    auto ground_item_iter = isGroundItem(ground_item_list, x, y);
    if (ground_item_iter != ground_item_list.end())
    {
        items[active_item - 1] = ground_item_iter->item;
        if (ground_item_iter->item.type == Item::tWeapon)
            changeActiveItem(active_item);
        ground_item_list.erase(ground_item_iter);
    }
}

bool Player::moveNextRoom(Rooms &rooms, Direction direction, std::list<Enemy> &enemy_list, std::list<GroundItem> &ground_item_list)
{
    int next_x = rooms.getActiveRoomX();
    int next_y = rooms.getActiveRoomY();
    int player_next_x;
    int player_next_y;
    switch (direction)
    {
    case dirLeft:
        if (next_x > 0)
        {
            next_x--;
            player_next_x = ROOM_SIZE - 2;
            player_next_y = ROOM_SIZE / 2;
        }
        else
            return false;
        break;
    case dirUp:
        if (next_y > 0)
        {
            next_y--;
            player_next_x = ROOM_SIZE / 2;
            player_next_y = ROOM_SIZE - 2;
        }
        else
            return false;
        break;
    case dirDown:
        if (next_y < MAP_SIZE - 1)
        {
            next_y++;
            player_next_x = ROOM_SIZE / 2;
            player_next_y = 1;
        }
        else
            return false;
        break;
    case dirRight:
        if (next_x < MAP_SIZE - 1)
        {
            next_x++;
            player_next_x = 1;
            player_next_y = ROOM_SIZE / 2;
        }
        else
            return false;
        break;
    }
    if (rooms.changeActiveRoom(next_x, next_y))
    {
        x = player_next_x;
        y = player_next_y;
        ground_item_list.clear();
        if (!rooms.getIsRoomDiscovered())
        {
            Enemy::SpawnEnemyList(rooms.cell_mtrx, enemy_list, *this);
            GroundItem::SpawnGroundItemList(rooms.cell_mtrx, enemy_list, *this, ground_item_list);
            rooms.closeRoom();
            rooms.setIsRoomDiscovered(true);
        }
        return true;
    }
    else
        return false;
}

bool Player::move(Rooms &rooms, Direction direction, std::list<Enemy> &enemy_list, std::list<GroundItem> &ground_item_list)
{
    int next_x = x;
    int next_y = y;
    switch (direction)
    {
    case dirLeft:
        if (next_x > 0)
            next_x--;
        else if (moveNextRoom(rooms, dirLeft, enemy_list, ground_item_list))
            return false;
        break;
    case dirUp:
        if (next_y > 0)
            next_y--;
        else if (moveNextRoom(rooms, dirUp, enemy_list, ground_item_list))
            return false;
        break;
    case dirDown:
        if (next_y < ROOM_SIZE - 1)
            next_y++;
        else if (moveNextRoom(rooms, dirDown, enemy_list, ground_item_list))
            return false;
        break;
    case dirRight:
        if (next_x < ROOM_SIZE - 1)
            next_x++;
        else if (moveNextRoom(rooms, dirRight, enemy_list, ground_item_list))
            return false;
        break;
    }

    if (rooms.cell_mtrx[next_y][next_x] == ctCell)
    {
        auto enemy_iter = isEnemy(enemy_list, next_x, next_y);
        if (enemy_iter != enemy_list.end())
        {
            int enemy_health = enemy_iter->getHealth();
            if (enemy_health > damage)
                enemy_iter->setHealth(enemy_health - damage);
            else
            {
                x = next_x;
                y = next_y;
                takeItems(ground_item_list);
                enemy_list.erase(enemy_iter);
                if (enemy_list.size() == 0)
                    rooms.openRoom();
            }
            last_atack_dir = direction;
            return true;
        }
        else
        {
            x = next_x;
            y = next_y;
            takeItems(ground_item_list);
        }
        last_atack_dir = dirUnknown;
        return true;
    }
    else
        return false;
}

void Player::changeActiveItem(int number)
{
    active_item = number;
    if (items[number - 1].type == Item::tWeapon)
        damage = items[number - 1].prop.damage;
    else if (items[number - 1].type == Item::tPotion)
    {
        int curr_health = health + items[number - 1].prop.health;
        curr_health = curr_health > 0 ? curr_health : 1;
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

    if (next_x == player_x && next_y == player_y &&
        (abs(x - player_x) + abs(y - player_y) == 1))
    {
        int player_health = player.getHealth();
        if (player_health > damage)
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

void getRandEmptyCell(CellMtrx cell_mtrx, std::list<Enemy> &enemy_list, Entity &player, int &x, int &y)
{
    bool is_found = false;
    while (!is_found)
    {
        x = rand() % (ROOM_SIZE - 2) + 1;
        y = rand() % (ROOM_SIZE - 2) + 1;
        if (cell_mtrx[y][x] == ctCell &&
            Entity::isEnemy(enemy_list, x, y) == enemy_list.end() &&
            (player.getX() != x || player.getY() != y))
        {
            is_found = true;
        }
    }
}

void Enemy::SpawnEnemyList(CellMtrx cell_mtrx, std::list<Enemy> &enemy_list, Entity &player)
{
    int n = rand() % 3 + 1;
    for (int i = 0; i < n; i++)
    {
        int new_x, new_y;
        getRandEmptyCell(cell_mtrx, enemy_list, player, new_x, new_y);

        int enemy_numb = rand() % ENEMY_SET_SIZE;
        Enemy enemy(new_x, new_y, enemy_set[enemy_numb].health,
                    enemy_set[enemy_numb].damage, enemy_set[enemy_numb].id);
        enemy_list.push_back(enemy);
    }
}

GroundItem::GroundItem(int a_x, int a_y, Item a_item)
{
    x = a_x;
    y = a_y;
    item = a_item;
}

int GroundItem::getX()
{
    return x;
}

int GroundItem::getY()
{
    return y;
}

void GroundItem::SpawnGroundItemList(CellMtrx cell_mtrx,
                                     std::list<Enemy> &enemy_list,
                                     Entity &player,
                                     std::list<GroundItem> &ground_item_list)
{
    int n = rand() % 3;
    if (n >= 1)
    {
        int new_x, new_y;
        getRandEmptyCell(cell_mtrx, enemy_list, player, new_x, new_y);

        int item_numb = rand() % ITEM_SET_SIZE;
        GroundItem ground_item(new_x, new_y, item_set[item_numb]);
        ground_item_list.push_back(ground_item);
    }
}