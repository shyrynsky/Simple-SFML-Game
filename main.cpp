#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <ctime>
#include <forward_list>
#include <iostream>

#define ARR_SIZE 41
#define WALL_SIZE 10
#define WALL 1
#define ROAD 0
#define EXIT -1
#define STAIR_UP -2
#define STAIR_DOWN -3
#define PATH -4
#define START 2

typedef int Matrix[ARR_SIZE][ARR_SIZE];

struct Coords
{
    int x, y;
};

class Maze
{
private:
    Matrix matrix;
    int print_x, print_y;
    int person_x = -1, person_y = -1;
    int exit_x = -1, exit_y = -1;
    int stair_x = -1, stair_y = -1;

public:
    void generate();
    void FindExit(bool is_person_higher);
    void MakeExit();
    void print(sf::RenderWindow &window, int x, int y, sf::Color color);
    void drawPerson(sf::RenderWindow &window, sf::Vector2i mousePos);
    bool mouseInMaze(sf::Vector2i mousePos);
    bool mouseInWall(sf::Vector2i mousePos);
    void Wave(Matrix path_matrix, int x, int y, int wave_stage);
    bool IsFindedExit(Matrix path_matrix, int wave_stage);
    void DeleteDeadEnd();
    void MakeCave();

    void SetPersonCoords(int Ax, int Ay);
    void SetExitCoords(int Ax, int Ay);
    void SetMatrix(int Ax, int Ay, int value);
    int ReadMatrix(int Ax, int Ay);
    void SetStairCoords(int Ax, int Ay);
};

void Maze::generate()
{
    for (int i = 0; i < ARR_SIZE; i++)
    {
        for (int j = 0; j < ARR_SIZE; j++)
        {
            matrix[i][j] = WALL;
        }
    }

    std::forward_list<Coords> coords_list;
    Coords coords;
    int list_size = 0;

    int x = (rand() % (ARR_SIZE / 2)) * 2 + 1;
    int y = (rand() % (ARR_SIZE / 2)) * 2 + 1;
    matrix[x][y] = ROAD;

    if (y - 2 >= 0)
    {
        coords.x = x;
        coords.y = y - 2;
        coords_list.push_front(coords);
        list_size++;
    }
    if (y + 2 < ARR_SIZE)
    {
        coords.x = x;
        coords.y = y + 2;
        coords_list.push_front(coords);
        list_size++;
    }
    if (x - 2 >= 0)
    {
        coords.x = x - 2;
        coords.y = y;
        coords_list.push_front(coords);
        list_size++;
    }
    if (x + 2 < ARR_SIZE)
    {
        coords.x = x + 2;
        coords.y = y;
        coords_list.push_front(coords);
        list_size++;
    }

    while (list_size > 0)
    {
        int index = rand() % list_size;
        auto iter = std::next(coords_list.cbefore_begin(), index);
        Coords cell = *std::next(iter, 1);
        x = cell.x;
        y = cell.y;
        matrix[x][y] = ROAD;
        coords_list.erase_after(iter);
        list_size--;
        int dir_index = rand() % 4;
        bool is_filled = false;
        while (!is_filled)
        {
            switch (dir_index)
            {
            case 0:
                if (y - 2 >= 0 && matrix[x][y - 2] == ROAD)
                {
                    matrix[x][y - 1] = ROAD;
                    is_filled = true;
                }
                else
                {
                    dir_index++;
                }
                break;
            case 1:
                if (y + 2 < ARR_SIZE && matrix[x][y + 2] == ROAD)
                {
                    matrix[x][y + 1] = ROAD;
                    is_filled = true;
                }
                else
                {
                    dir_index++;
                }
                break;
            case 2:
                if (x - 2 >= 0 && matrix[x - 2][y] == ROAD)
                {
                    matrix[x - 1][y] = ROAD;
                    is_filled = true;
                }
                else
                {
                    dir_index++;
                }
                break;
            case 3:
                if (x + 2 < ARR_SIZE && matrix[x + 2][y] == ROAD)
                {
                    matrix[x + 1][y] = ROAD;
                    is_filled = true;
                }
                else
                {
                    dir_index = 0;
                }
                break;
            }
        }
        bool is_in_list;

        if (y - 2 >= 0 && matrix[x][y - 2] == WALL)
        {
            coords.x = x;
            coords.y = y - 2;
            is_in_list = false;
            for (Coords n : coords_list)
            {
                is_in_list = coords.x == n.x && coords.y == n.y;
                if (is_in_list)
                    break;
            }
            if (!is_in_list)
            {
                coords_list.push_front(coords);
                list_size++;
            }
        }
        if (y + 2 < ARR_SIZE && matrix[x][y + 2] == WALL)
        {
            coords.x = x;
            coords.y = y + 2;
            is_in_list = false;
            for (Coords n : coords_list)
            {
                is_in_list = coords.x == n.x && coords.y == n.y;
                if (is_in_list)
                    break;
            }
            if (!is_in_list)
            {
                coords_list.push_front(coords);
                list_size++;
            }
        }
        if (x - 2 >= 0 && matrix[x - 2][y] == WALL)
        {
            coords.x = x - 2;
            coords.y = y;
            is_in_list = false;
            for (Coords n : coords_list)
            {
                is_in_list = coords.x == n.x && coords.y == n.y;
                if (is_in_list)
                    break;
            }
            if (!is_in_list)
            {
                coords_list.push_front(coords);
                list_size++;
            }
        }
        if (x + 2 < ARR_SIZE && matrix[x + 2][y] == WALL)
        {
            coords.x = x + 2;
            coords.y = y;
            is_in_list = false;
            for (Coords n : coords_list)
            {
                is_in_list = coords.x == n.x && coords.y == n.y;
                if (is_in_list)
                    break;
            }
            if (!is_in_list)
            {
                coords_list.push_front(coords);
                list_size++;
            }
        }
    }
}

void Maze::FindExit(bool is_person_higher)
{
    Matrix path_matrix;
    int i, j;
    for (i = 0; i < ARR_SIZE; i++)
    {
        for (j = 0; j < ARR_SIZE; j++)
        {
            if (matrix[i][j] == WALL || matrix[i][j] == ROAD)
            {
                path_matrix[i][j] = matrix[i][j];
            }
            else
            {
                path_matrix[i][j] = 0;
            }
        }
    }
    path_matrix[exit_y][exit_x] = EXIT;
    if (is_person_higher)
    {
        path_matrix[stair_x][stair_y] = START;
        matrix[stair_x][stair_y] = START;
    }
    else
    {
        path_matrix[person_y][person_x] = START;
        matrix[person_y][person_x] = START;
    }
    int wave_stage = START;
    while (!IsFindedExit(path_matrix, wave_stage))
    {
        for (i = 0; i < ARR_SIZE; i++)
        {
            for (j = 0; j < ARR_SIZE; j++)
            {
                if (path_matrix[i][j] == wave_stage)
                {
                    Wave(path_matrix, i, j, wave_stage);
                }
            }
        }
        wave_stage++;
    }
    int x = exit_y, y = exit_x;
    for (i = wave_stage; i > START; i--)
    {
        if ((x - 1 >= 0) && path_matrix[x - 1][y] == i)
        {
            x = x - 1;
            matrix[x][y] = PATH;
        }
        if ((y - 1 >= 0) && path_matrix[x][y - 1] == i)
        {
            y = y - 1;
            matrix[x][y] = PATH;
        }
        if ((x + 1 < ARR_SIZE) && path_matrix[x + 1][y] == i)
        {
            x = x + 1;
            matrix[x][y] = PATH;
        }
        if ((y + 1 < ARR_SIZE) && path_matrix[x][y + 1] == i)
        {
            y = y + 1;
            matrix[x][y] = PATH;
        }
    }
}

bool Maze::IsFindedExit(Matrix path_matrix, int wave_stage)
{
    if ((exit_y - 1 >= 0) && path_matrix[exit_y - 1][exit_x] == wave_stage)
    {
        return true;
    }
    if ((exit_x - 1 >= 0) && path_matrix[exit_y][exit_x - 1] == wave_stage)
    {
        return true;
    }
    if ((exit_y + 1 < ARR_SIZE) && path_matrix[exit_y + 1][exit_x] == wave_stage)
    {
        return true;
    }
    if ((exit_x + 1 < ARR_SIZE) && path_matrix[exit_y][exit_x + 1] == wave_stage)
    {
        return true;
    }
    return false;
}

void Maze::Wave(Matrix path_matrix, int x, int y, int wave_stage)
{
    wave_stage++;
    if ((x - 1 >= 0) && path_matrix[x - 1][y] == ROAD)
    {
        path_matrix[x - 1][y] = wave_stage;
    }
    if ((y - 1 >= 0) && path_matrix[x][y - 1] == ROAD)
    {
        path_matrix[x][y - 1] = wave_stage;
    }
    if ((x + 1 < ARR_SIZE) && path_matrix[x + 1][y] == ROAD)
    {
        path_matrix[x + 1][y] = wave_stage;
    }
    if ((y + 1 < ARR_SIZE) && path_matrix[x][y + 1] == ROAD)
    {
        path_matrix[x][y + 1] = wave_stage;
    }
}

void Maze::MakeExit()
{
    int x = 0;
    int y;
    int i;

    do
    {
        y = (rand() % (ARR_SIZE / 2)) * 2 + 1;
        for (i = 1; i < ARR_SIZE; i += 2)
        {
            if (matrix[y][i] == ROAD)
            {
                x = i;
                break;
            }
        }
    } while (x == 0);
    matrix[y][0] = EXIT;
    exit_x = 0;
    exit_y = y;
    for (i = 1; i < x; i++)
    {
        matrix[y][i] = ROAD;
    }
}

void Maze::DeleteDeadEnd()
{
    int i, j;
    Matrix temp_matrix;
    for (i = 0; i < ARR_SIZE; i++)
    {
        for (j = 0; j < ARR_SIZE; j++)
        {
            int count = 0;
            if ((i - 1 >= 0) && matrix[i - 1][j] == WALL)
            {
                count++;
            }
            if ((j - 1 >= 0) && matrix[i][j - 1] == WALL)
            {
                count++;
            }
            if ((i + 1 < ARR_SIZE) && matrix[i + 1][j] == WALL)
            {
                count++;
            }
            if ((j + 1 < ARR_SIZE) && matrix[i][j + 1] == WALL)
            {
                count++;
            }
            if (count >= 3)
            {
                temp_matrix[i][j] = WALL;
            }
            else
            {
                temp_matrix[i][j] = ROAD;
            }
        }
    }
    for (i = 0; i < ARR_SIZE; i++)
    {
        for (j = 0; j < ARR_SIZE; j++)
        {
            if (temp_matrix[i][j] == WALL)
            {
                matrix[i][j] = WALL;
            }
        }
    }
}

void Maze::MakeCave()
{
    int i, j;
    Matrix temp_matrix;
    for (i = 0; i < ARR_SIZE; i++)
    {
        for (j = 0; j < ARR_SIZE; j++)
        {
            int count = 0;
            if ((i - 1 >= 0) && matrix[i - 1][j] == ROAD)
            {
                count++;
            }
            if ((j - 1 >= 0) && matrix[i][j - 1] == ROAD)
            {
                count++;
            }
            if ((i + 1 < ARR_SIZE) && matrix[i + 1][j] == ROAD)
            {
                count++;
            }
            if ((j + 1 < ARR_SIZE) && matrix[i][j + 1] == ROAD)
            {
                count++;
            }
            if (count >= 2)
            {
                temp_matrix[i][j] = ROAD;
            }
            else
            {
                temp_matrix[i][j] = WALL;
            }
        }
    }
    for (i = 0; i < ARR_SIZE; i++)
    {
        for (j = 0; j < ARR_SIZE; j++)
        {
            if (temp_matrix[i][j] == ROAD)
            {
                matrix[i][j] = ROAD;
            }
        }
    }
}

void Maze::drawPerson(sf::RenderWindow &window, sf::Vector2i mousePos)
{

    if (mouseInMaze(mousePos) && !mouseInWall(mousePos))
    {
        sf::CircleShape circle;
        circle.setRadius(WALL_SIZE / 2);
        circle.setFillColor(sf::Color::White);
        person_x = (mousePos.x - print_x) / WALL_SIZE;
        person_y = (mousePos.y - print_y) / WALL_SIZE;
        circle.setPosition(person_x * WALL_SIZE + print_x, person_y * WALL_SIZE + print_y);
        window.draw(circle);
    }
}

bool Maze::mouseInMaze(sf::Vector2i mousePos)
{
    return mousePos.x >= print_x && mousePos.x < print_x + WALL_SIZE * ARR_SIZE && mousePos.y >= print_y && mousePos.y < print_y + WALL_SIZE * ARR_SIZE;
}

bool Maze::mouseInWall(sf::Vector2i mousePos)
{
    return matrix[(mousePos.y - print_y) / WALL_SIZE][(mousePos.x - print_x) / WALL_SIZE] == WALL;
}

void Maze::SetPersonCoords(int Ax, int Ay)
{
    person_x = Ax;
    person_y = Ay;
}

void Maze::SetExitCoords(int Ax, int Ay)
{
    exit_x = Ax;
    exit_y = Ay;
}

void Maze::SetMatrix(int Ax, int Ay, int value)
{
    matrix[Ax][Ay] = value;
}

int Maze::ReadMatrix(int Ax, int Ay)
{
    return matrix[Ax][Ay];
}

void Maze::SetStairCoords(int Ax, int Ay)
{
    stair_x = Ax;
    stair_y = Ay;
}

void Maze::print(sf::RenderWindow &window, int x, int y, sf::Color color)
{
    sf::RectangleShape cell(sf::Vector2f(WALL_SIZE, WALL_SIZE));
    cell.setFillColor(color);
    sf::CircleShape circle;
    circle.setRadius(WALL_SIZE / 3);
    circle.setFillColor(sf::Color::White);

    print_x = x;
    print_y = y;

    for (int i = 0; i < ARR_SIZE; ++i)
    {
        for (int j = 0; j < ARR_SIZE; ++j)
        {
            switch (matrix[i][j])
            {
            case WALL:
                cell.setPosition(x + j * WALL_SIZE, y + i * WALL_SIZE);
                window.draw(cell);
                break;

            case STAIR_UP:
            case STAIR_DOWN:
                cell.setFillColor(sf::Color::Yellow);
                cell.setPosition(x + j * WALL_SIZE, y + i * WALL_SIZE);
                window.draw(cell);
                cell.setFillColor(color);
                break;

            case PATH:
                circle.setPosition(x + j * WALL_SIZE + WALL_SIZE / 4, y + i * WALL_SIZE + WALL_SIZE / 4);
                window.draw(circle);
                break;

            case START:
                circle.setRadius(WALL_SIZE / 2);
                circle.setPosition(x + j * WALL_SIZE, y + i * WALL_SIZE);
                window.draw(circle);
                circle.setRadius(WALL_SIZE / 3);
                break;
            }
        }
    }
}

void ConnectMazes(Maze &floor_1, Maze &floor_2)
{
    bool is_connected = false;
    int x, y;
    do
    {
        x = (rand() % (ARR_SIZE / 2)) * 2 + 1;
        y = (rand() % (ARR_SIZE / 2)) * 2 + 1;
        is_connected = floor_1.ReadMatrix(x, y) == ROAD && floor_2.ReadMatrix(x, y) == ROAD;
    } while (!is_connected);
    floor_1.SetMatrix(x, y, STAIR_UP);
    floor_2.SetMatrix(x, y, STAIR_DOWN);
    floor_2.SetExitCoords(y, x);
    floor_1.SetStairCoords(x, y);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1500, 800), "Maze", sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    srand((unsigned)time(NULL));

    Maze maze1;
    Maze maze2;
    Maze maze3;
    maze1.generate();
    maze2.generate();
    maze3.generate();

    maze1.DeleteDeadEnd();
    maze1.DeleteDeadEnd();
    maze1.DeleteDeadEnd();
    maze1.MakeCave();
    maze1.MakeCave();
    maze1.MakeCave();
    maze1.DeleteDeadEnd();
    maze1.DeleteDeadEnd();

    maze1.MakeExit();
    ConnectMazes(maze1, maze2);
    ConnectMazes(maze2, maze3);

    while (window.isOpen())
    {
        sf::Event event;
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                if (maze1.mouseInMaze(mousePos))
                {
                    maze1.FindExit(false);
                }
                else
                {
                    if (maze2.mouseInMaze(mousePos))
                    {
                        maze2.FindExit(false);
                        maze1.FindExit(true);
                    }
                    else
                    {
                        if (maze3.mouseInMaze(mousePos))
                        {
                            maze3.FindExit(false);
                            maze2.FindExit(true);
                            maze1.FindExit(true);
                        }
                    }
                }
                break;
            }
        }

        window.clear();

        maze1.print(window, 48, 150, sf::Color(0, 0, 100));
        maze2.print(window, 548, 150, sf::Color(100, 0, 0));
        maze3.print(window, 1048, 150, sf::Color(0, 100, 0));

        maze1.drawPerson(window, mousePos);
        maze2.drawPerson(window, mousePos);
        maze3.drawPerson(window, mousePos);

        window.display();
    }

    return 0;
}
