#include "Controller.h"
#include "Model.h"

Controller::Controller(Model& model, View& view) : model(model), view(view) {}

bool Controller::backtrackSolve(std::vector<Node>& grid, int flagsPlaced, int currentIndex) {
    model.saveState();
    if (flagsPlaced == Model::NUM_BOMBS) {
        for (const auto& bombCoord : model.getBombCoordinates()) {
            bool foundFlag = false;
            for (const auto& node : grid) {
                if (node.x == bombCoord.x && node.y == bombCoord.y && node.content == 'F') {
                    foundFlag = true;
                    break;
                }
            }
            if (!foundFlag) return false;
        }
        return true;
    }

    for (int i = currentIndex; i < Model::GRID_SIZE * Model::GRID_SIZE; ++i) {
        Node& node = grid[i];

        if (node.content == '-' || node.content == '*') {
            bool adjacentToNumber = false;

            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    if (dx == 0 && dy == 0) continue;
                    int nx = node.x + dx;
                    int ny = node.y + dy;
                    if (nx >= 0 && nx < Model::GRID_SIZE && ny >= 0 && ny < Model::GRID_SIZE) {
                        Node& neighbor = grid[nx * Model::GRID_SIZE + ny];
                        if (neighbor.content >= '1' && neighbor.content <= '8') {
                            adjacentToNumber = true;
                            break;
                        }
                    }
                }
                if (adjacentToNumber) break;
            }

            if (adjacentToNumber) {
                node.content = 'F';  // Place a flag
                if (backtrackSolve(grid, flagsPlaced + 1, i + 1)) {
                    return true;
                }
                node.content = '-';  // Backtrack: Remove the flag
                model.saveState();    // Save the state after backtracking
            }
        }
    }

    return false;  // No solution found, backtrack
}

void Controller::start() {
    auto& grid = model.getGrid();
    backtrackSolve(grid, 0, 0);
    view.render(model.recursionStates);
}
