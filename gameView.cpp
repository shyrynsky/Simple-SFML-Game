#include "gameView.hpp"

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

    // sprite.setPosition(sf::Vector2f(curr_x, curr_y));
    sprite.setPosition(start_x + curr_x * CELL_SIZE, start_y + curr_y * CELL_SIZE);
    window.draw(sprite);
}