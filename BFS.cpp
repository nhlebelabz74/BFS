/**
 * @file BFS2.cpp
 * @author Banzile Nhlebela
 * @brief prints out best/shortest path from start to goal of a given maze
 * @version 0.1
 * @date 2022-10-04
 *
 * @copyright Copyright (c) 2022
 */

#include <iostream>
#include <list>
#include <string>
#include <queue>

/**
 * @brief class that will store coordinates of any cell in maze
 */
class coordinate
{
    /**
     * @brief public attributes
     */
public:
    /**
     * @brief Construct a new coordinate object with coordinates (0;0)
     */
    coordinate() : x(0), y(0) {}

    /**
     * @brief Construct a new coordinate object with coordinates (i;j)
     * @param i
     * @param j
     */
    coordinate(int i, int j) : x(i), y(j) {}

    /**
     * @brief return the value of the x coordinate
     * @return int
     */
    int getX() {
        return x;
    }

    /**
     * @brief return the value of the y coordinate
     * @return int
     */
    int getY() {
        return y;
    }

    /**
     * @brief set values of x and y coordinates to given params
     * @param x_coordinate
     * @param y_coordinate
     */
    void setXY(int x_coordinate, int y_coordinate) {
        x = x_coordinate;
        y = y_coordinate;
    }

    /**
     * @brief set x coordinate to value in param
     * @param x_coordinate
     */
    void setX(int x_coordinate) {
        x = x_coordinate;
    }

    /**
     * @brief set y coordinate to value in param
     * @param y_coordinate
     */
    void setY(int y_coordinate) {
        y = y_coordinate;
    }

    /**
     * @brief compare two coordinates using ==
     * @param c
     * @return true
     * @return false
     */
    bool operator==(coordinate c)
    {
        if (x == c.getX() && y == c.getY())
            return true;

        return false;
    }

    /**
     * @brief compare two coordinates using !=
     * @param c
     * @return true
     * @return false
     */
    bool operator!=(coordinate c) {
        return !operator==(c);
    }

    /**
     * @brief comapre both x and y coordinates to given params
     * @param x_coordinate
     * @param y_coordinate
     * @return true
     * @return false
     */
    bool compare(int x_coordinate, int y_coordinate)
    {
        if (x == x_coordinate && y == y_coordinate)
            return true;

        return false;
    }

    /**
     * @brief return the coordinate as a string in the form (x;y)
     * @return std::string
     */
    std::string toString()
    {
        std::string s = "(" + std::to_string(x) + ";" + std::to_string(y) + ")";
        return s;
    }

    /**
     * @brief private attributes
     */
private:
    int x;
    int y;
};

/**
 * @brief driver code
 * @return int
 */
int main()
{
    std::queue<coordinate> q;
    coordinate start, goal;
    int row, col;

    std::cin >> row >> col;
    std::cin.ignore();

    char grid[row][col];
    coordinate parent[row][col];

    std::string s;
    for (int i = 0; i < row; i++)
    {
        getline(std::cin, s);

        for (int j = 0; j < col; j++)
        {
            grid[i][j] = s[j];

            // unvisited
            parent[i][j].setXY(-2, -2);

            if (s[j] == 'S')
                start.setXY(i, j);
            if (s[j] == 'G')
                goal.setXY(i, j);
            // walls
            if (s[j] == 'x')
                parent[i][j].setXY(-1, -1);
        }
    }

    q.push(start);

    int rowDisp[] = {1, 0, -1, 0}; // DLUR
    int colDisp[] = {0, -1, 0, 1}; // DLUR

    while (!q.empty() && parent[goal.getX()][goal.getY()].compare(-2, -2))
    {
        coordinate curr = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int r = curr.getX() + rowDisp[i], c = curr.getY() + colDisp[i];
            if ((0 <= r < row) && (0 <= c < col)) // if we don't fall off the map
            {
                if (parent[r][c].compare(-2, -2)) // if unvisited
                {
                    parent[r][c] = curr;
                    coordinate neighbour(r, c); // store coordinate for neighbour
                    q.push(neighbour);          // add neighbour to the queue
                }
            }
        }
    }

    std::list<coordinate> output;

    if (q.empty() && parent[goal.getX()][goal.getY()].compare(-2, -2)) // queue is empty and goal unvisited
        std::cout << "No Path" << std::endl;
    else
    {
        coordinate curr = goal;

        while (curr != start)
        {
            output.push_front(curr);
            curr = parent[curr.getX()][curr.getY()];
        }
        output.pop_back();

        for (auto &out : output)
            grid[out.getX()][out.getY()] = '*';

        for (auto &row : grid)
        {
            for (auto col : row)
                std::cout << col;

            std::cout << std::endl;
        }
    }

    return 0;
}
