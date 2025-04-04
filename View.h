//
// Created by Kota Ohashi on 11/22/24.
//
#ifndef MINESWEEPER_VIEW_H
#define MINESWEEPER_VIEW_H

#include <SFML/Graphics.hpp>
#include "Model.h"

class View {
private:
    sf::RenderWindow window;
    sf::Font font;
    const int cellSize = 50;

public:
    View();
    void render(const std::vector<std::vector<Node>>& states);
};

#endif //MINESWEEPERRECURSION_VIEW_H
