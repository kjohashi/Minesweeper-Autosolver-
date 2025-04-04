//
// Created by Kota Ohashi on 11/22/24.
//

#ifndef MINESWEEPER_MODEL_H
#define MINESWEEPER_MODEL_H

#include <vector>
#include <cstdlib>
#include <ctime>

struct Coordinate {
    int x, y;

    Coordinate(int x, int y) : x(x), y(y) {}
};

class Node {
public:
    int x, y;
    char content;

    Node(int x, int y, char content = '-') : x(x), y(y), content(content) {}
};

class Model {
private:
    std::vector<Node> grid;
    std::vector<Coordinate> bombCoordinates;

    void initializeGrid();
    void placeBombs();
    void calculateNumbersAroundBombs();

public:
    Model();

    static const int GRID_SIZE = 5;
    static const int NUM_BOMBS = 3;

    std::vector<Node>& getGrid();
    const std::vector<Coordinate>& getBombCoordinates() const;
    void saveState();
    std::vector<std::vector<Node>> recursionStates;
};

#endif // MINESWEEPER_MODEL_H
