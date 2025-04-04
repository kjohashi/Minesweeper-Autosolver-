//
// Created by Kota Ohashi on 11/22/24.
//

#include "View.h"
#include <iostream>
View::View() : window(sf::VideoMode(1920, 1080), "Minesweeper") {
    // Set initial values for cell size and window size
    const int cellSize = 50;  // Each cell's size in pixels (can be adjusted)
    int windowSize = Model::GRID_SIZE * cellSize;  // Window size based on grid size

    // Resize the window according to grid size
    window.create(sf::VideoMode(windowSize, windowSize), "Minesweeper");
}

void View::render(const std::vector<std::vector<Node>>& states) {
    int currentState = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Right) {
                    currentState = (currentState + 1) % states.size();
                } else if (event.key.code == sf::Keyboard::Left) {
                    currentState = (currentState - 1 + states.size()) % states.size();
                }
            }
        }

        window.clear();
        const auto& grid = states[currentState];

        sf::Texture bombTexture;
        sf::Texture flagTexture;
        sf::Texture blankTexture;
        sf::Texture numberTextures[8];

        // Load the textures (do this once, for example, in the constructor)
        if (!bombTexture.loadFromFile("*.png")) {
            std::cout << "Error." << std::endl;
        }
        if (!flagTexture.loadFromFile("F.png")) {
            std::cout << "Error." << std::endl;
        }
        if (!blankTexture.loadFromFile("-.png")) {
            std::cout << "Error." << std::endl;
        }
        for (int i = 0; i < 8; ++i) {
            if (!numberTextures[i].loadFromFile(std::to_string(i+1) + ".png")) {
                std::cout << "Error." << std::endl;
            }
        }

        for (int i = 0; i < Model::GRID_SIZE; ++i) {
            for (int j = 0; j < Model::GRID_SIZE; ++j) {
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(j * cellSize, i * cellSize);
                cell.setOutlineColor(sf::Color::Black);
                cell.setOutlineThickness(1);

                char content = grid[i * Model::GRID_SIZE + j].content;
                if (content == '*') {
                    cell.setTexture(&bombTexture); //Bombs
                } else if (content == 'F') {
                    cell.setTexture(&flagTexture); //Flags
                } else if (content == '-'){
                    cell.setTexture(&blankTexture); //Blanks
                } else if (content >= '1' && content <= '8') {
                    int num = content - '1'; // Convert character '1' to '8' to index 0-7
                    cell.setTexture(&numberTextures[num]); // Numbered cells
                }

                window.draw(cell);
            }
        }

        window.display();
    }
}
