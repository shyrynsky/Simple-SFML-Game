#include "gameView.hpp"

using namespace sf;

#define CELL_SIZE 100
#define BORDER_SIZE 4

const int start_x = (1920 - (CELL_SIZE * (ROOM_SIZE + 2))) / 2;
const int start_y = CELL_SIZE / 2;

void drawRoom(sf::RenderWindow &window, CellMtrx cell_mtrx)
{

    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - BORDER_SIZE, CELL_SIZE - BORDER_SIZE));
    cell.setFillColor(sf::Color(160, 82, 45));
    cell.setOutlineThickness(BORDER_SIZE);
    cell.setOutlineColor(sf::Color::Black);
    sf::RectangleShape wall(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    wall.setFillColor(sf::Color(105, 105, 105));
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
            default:
                break;
            }
        }
    }
}

void drawEntity(sf::RenderWindow &window, Entity &entity, sf::Sprite &sprite)
{
    int curr_x = entity.getX();
    int curr_y = entity.getY();
    int curr_health = entity.getHealth();
    int curr_max_health = entity.getMaxHealth();
    int draw_x = start_x + curr_x * CELL_SIZE;
    int draw_y = start_y + curr_y * CELL_SIZE;

    // TODO нормально отрисовывать финальные спрайты
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