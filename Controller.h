#ifndef MINESWEEPER_CONTROLLER_H
#define MINESWEEPER_CONTROLLER_H

#include "Model.h"
#include "View.h"

class Controller {
private:
    Model& model;
    View& view;

    bool backtrackSolve(std::vector<Node>& grid, int flagsPlaced, int currentIndex);

public:
    Controller(Model& model, View& view);
    void start();
};

#endif // MINESWEEPER_CONTROLLER_H
