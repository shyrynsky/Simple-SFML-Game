#include "gameView.hpp"

using namespace sf;

#define CELL_SIZE 100
#define BORDER_SIZE 4

const int start_x = (1920 - (CELL_SIZE * ROOM_SIZE)) / 2;
const int start_y = CELL_SIZE / 2;

void drawRoom(sf::RenderWindow &window, CellMtrx cell_mtrx)
{

    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - BORDER_SIZE, CELL_SIZE - BORDER_SIZE));
    cell.setFillColor(sf::Color(160, 82, 45));
    cell.setOutlineThickness(BORDER_SIZE);
    cell.setOutlineColor(sf::Color::Black);
    sf::RectangleShape wall(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    wall.setFillColor(sf::Color(105, 105, 105));
    sf::RectangleShape door(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    door.setFillColor(sf::Color(55, 55, 55));
    for (int row = 0; row < ROOM_SIZE; row++)
    {
        for (int column = 0; column < ROOM_SIZE; column++)
        {
            switch (cell_mtrx[row][column])
            {
            case ctCell:
                cell.setPosition(start_x + column * CELL_SIZE, start_y + row * CELL_SIZE);
                window.draw(cell);
                break;
            case ctWall:
                wall.setPosition(start_x + column * CELL_SIZE, start_y + row * CELL_SIZE);
                window.draw(wall);
                break;
            case ctDoor:
                door.setPosition(start_x + column * CELL_SIZE, start_y + row * CELL_SIZE);
                window.draw(door);
                break;
            default:
                break;
            }
        }
    }
}

void drawEntity(sf::RenderWindow &window, Entity &entity, sf::Sprite &sprite, sf::Clock &fight_clock)
{
    int curr_x = entity.getX();
    int curr_y = entity.getY();
    int curr_health = entity.getHealth();
    int curr_max_health = entity.getMaxHealth();
    int draw_x = start_x + curr_x * CELL_SIZE;
    int draw_y = start_y + curr_y * CELL_SIZE;
    if (fight_clock.getElapsedTime().asMilliseconds() < 100)
        switch (entity.getLastAttackDir())
        {
        case dirUp:
            draw_y -= CELL_SIZE / 4;
            break;
        case dirDown:
            draw_y += CELL_SIZE / 4;
            break;
        case dirLeft:
            draw_x -= CELL_SIZE / 4;
            break;
        case dirRight:
            draw_x += CELL_SIZE / 4;
            break;
        }

    sprite.setPosition(draw_x + 5, draw_y + 20);
    window.draw(sprite);

    RectangleShape health_bar(Vector2f(CELL_SIZE * 0.8, CELL_SIZE * 0.1));
    health_bar.setOutlineThickness(BORDER_SIZE / 2);
    health_bar.setOutlineColor(Color::Black);
    health_bar.setFillColor(Color(0, 0, 0, 0));
    health_bar.setPosition(draw_x + (CELL_SIZE * 0.1 - BORDER_SIZE / 2), draw_y + 10);
    RectangleShape healt_bar_inner(Vector2f(
        CELL_SIZE * 0.8 * curr_health / curr_max_health, CELL_SIZE * 0.1));
    healt_bar_inner.setFillColor(Color::Red);
    healt_bar_inner.setPosition(draw_x + (CELL_SIZE * 0.1 - BORDER_SIZE / 2), draw_y + 10);
    window.draw(health_bar);
    window.draw(healt_bar_inner);
}

void drawEnemyList(sf::RenderWindow &window, std::list<Enemy> &enemy_list, std::vector<Sprite> &enemy_sprites, sf::Clock &fight_clock)
{
    for (Enemy enemy : enemy_list)
    {
        drawEntity(window, enemy, enemy_sprites[enemy.getId()], fight_clock);
    }
}

void drawGroundItemList(RenderWindow &window, std::list<GroundItem> &ground_item_list, std::vector<Sprite> &item_ground_sprites)
{
    for (GroundItem ground_item : ground_item_list)
    {
        int id = ground_item.item.id;
        int x = ground_item.getX();
        int y = ground_item.getY();
        item_ground_sprites[id].setPosition(start_x + x * CELL_SIZE + 20, start_y + y * CELL_SIZE + 20);
        window.draw(item_ground_sprites[id]);
    }
}

void drawInventory(sf::RenderWindow &window, sf::Font &font, Player &player, std::vector<sf::Sprite> &item_sprites)
{
    int active_item = player.getActiveItem();
    RectangleShape container(Vector2f(CELL_SIZE * 1.5 - BORDER_SIZE, CELL_SIZE * 1.5 - BORDER_SIZE));
    container.setOutlineThickness(BORDER_SIZE);
    container.setOutlineColor(Color::Black);
    container.setFillColor(Color(238, 182, 87));

    RectangleShape active_outline(Vector2f(CELL_SIZE * 1.5 - 5 * BORDER_SIZE, CELL_SIZE * 1.5 - 5 * BORDER_SIZE));
    active_outline.setOutlineThickness(BORDER_SIZE * 2);
    active_outline.setOutlineColor(Color::Red);
    active_outline.setFillColor(Color(0, 0, 0, 20));

    Text text;
    text.setFont(font);
    text.setFillColor(Color::Black);
    text.setCharacterSize(20);

    for (int i = 0; i < INVENTORY_SIZE; i++)
    {
        container.setPosition(50, i * CELL_SIZE * 1.5 + start_y);

        char n = '1' + i;
        text.setString(n);
        text.setPosition(50 + 20, i * CELL_SIZE * 1.5 + start_y + 20);

        window.draw(container);
        window.draw(text);
        if (i == active_item - 1)
        {
            active_outline.setPosition(50 + 2 * BORDER_SIZE, i * CELL_SIZE * 1.5 + start_y + 2 * BORDER_SIZE);
            window.draw(active_outline);
        }
        if (player.getItems()[i].type != Item::tUndef)
        {
            int id = player.getItems()[i].id;
            item_sprites[id].setPosition(50 + 25, i * CELL_SIZE * 1.5 + start_y + 25); // 100px
            window.draw(item_sprites[id]);
        }
    }
}

void drawMiniMap(RenderWindow &window, Rooms &rooms)
{
    int draw_x = 1920 - (0.5 * CELL_SIZE) * MAP_SIZE - (0.5 * CELL_SIZE);
    int draw_y = 1080 - (0.5 * CELL_SIZE) * MAP_SIZE - CELL_SIZE;

    sf::RectangleShape visited_room(sf::Vector2f((0.5 * CELL_SIZE) - BORDER_SIZE, (0.5 * CELL_SIZE) - BORDER_SIZE));
    visited_room.setFillColor(sf::Color(160, 82, 45));
    visited_room.setOutlineThickness(BORDER_SIZE);
    visited_room.setOutlineColor(sf::Color::Black);
    sf::RectangleShape curr_room(sf::Vector2f((0.5 * CELL_SIZE) - BORDER_SIZE, (0.5 * CELL_SIZE) - BORDER_SIZE));
    curr_room.setFillColor(sf::Color::Red);
    curr_room.setOutlineThickness(BORDER_SIZE);
    curr_room.setOutlineColor(sf::Color::Black);
    // TODO изначально скрывать всю карту от игрока
    sf::RectangleShape unvisited_room(sf::Vector2f((0.5 * CELL_SIZE), (0.5 * CELL_SIZE)));
    unvisited_room.setFillColor(sf::Color(70, 70, 70, 70));

    for (int row = 0; row < MAP_SIZE; row++)
    {
        for (int column = 0; column < MAP_SIZE; column++)
        {
            if (rooms.rooms_mtrx[row][column].is_room)
            {
                if (rooms.getActiveRoomX() == column && rooms.getActiveRoomY() == row)
                {
                    curr_room.setPosition(draw_x + column * (0.5 * CELL_SIZE), draw_y + row * (0.5 * CELL_SIZE));
                    window.draw(curr_room);
                }
                else if (rooms.rooms_mtrx[row][column].is_discovered)
                {
                    visited_room.setPosition(draw_x + column * (0.5 * CELL_SIZE), draw_y + row * (0.5 * CELL_SIZE));
                    window.draw(visited_room);
                }
                else
                {
                    unvisited_room.setPosition(draw_x + column * (0.5 * CELL_SIZE), draw_y + row * (0.5 * CELL_SIZE));
                    window.draw(unvisited_room);
                }
            }
        }
    }
}