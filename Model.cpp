//
// Created by Kota Ohashi on 11/22/24.
//

#include "Model.h"

Model::Model() {
    initializeGrid();
}

void Model::initializeGrid() {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            grid.emplace_back(i, j);
        }
    }
    placeBombs();
    calculateNumbersAroundBombs();
}

void Model::placeBombs() {
    int bombsPlaced = 0;
    while (bombsPlaced < NUM_BOMBS) {
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;

        Node& node = grid[x * GRID_SIZE + y];
        if (node.content != '*') {
            node.content = '*';
            bombCoordinates.push_back(Coordinate(x, y));
            ++bombsPlaced;
        }
    }
}

void Model::calculateNumbersAroundBombs() {
    for (auto& node : grid) {
        if (node.content == '*') continue;

        int bombCount = 0;
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue;
                int nx = node.x + dx;
                int ny = node.y + dy;
                if (nx >= 0 && nx < GRID_SIZE && ny >= 0 && ny < GRID_SIZE) {
                    Node& neighbor = grid[nx * GRID_SIZE + ny];
                    if (neighbor.content == '*') {
                        ++bombCount;
                    }
                }
            }
        }

        if (bombCount > 0) {
            node.content = '0' + bombCount;
        }
    }
}

std::vector<Node>& Model::getGrid() {
    return grid;
}

const std::vector<Coordinate>& Model::getBombCoordinates() const {
    return bombCoordinates;
}

void Model::saveState() {
    recursionStates.push_back(grid);
}
