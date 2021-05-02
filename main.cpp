#include <iostream>
#include <random>
#include <bits/stdc++.h>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "ui_code.hpp"

struct CellGrid {
    bool* cell_map;
    bool* temp_map;
    uint width;
    uint height;

    CellGrid(const uint& _width, const uint& _height) {
        width = _width;
        height = _height;
        cell_map = new bool[width*height];
        temp_map = new bool[width*height];
    }

    void next_generation(bool* new_location) {
        for (uint y = 0; y < height; ++y) {
            for (uint x = 0; x < width; ++x) {
                // Get neighbours
                int neighbours = 0 - cell_map[height * x + y];
                const uint max_x = (x+1==width) ? width : x+1;
                const uint max_y = (y+1==height) ? height : y+1;
                for (uint ry = (y == 0) ? 0 : y-1; ry <= max_y; ++ry) {
                    for (uint rx = (x == 0) ? 0 : x-1; rx <= max_x; ++rx) {
                        neighbours += cell_map[height * rx + ry];
                    }
                }
                
                if (cell_map[width * x + y]) {
                    if (neighbours == 2 || neighbours == 3) {
                        new_location[height * x + y] = true;
                    }
                    else {
                        new_location[height * x + y] = false;
                    }
                }
                else {
                    if (neighbours == 3) {
                        new_location[height * x + y] = true;
                    }
                    else {
                        new_location[height * x + y] = false;
                    }
                }
                
            }
        }
    }

    void update() {
        next_generation(temp_map);
        memcpy(cell_map, temp_map, (width*height) * sizeof *temp_map);
    }

    ~CellGrid() {
        delete[] cell_map;
        delete[] temp_map;
    }
};

int main() {
    uint width = 1000, height = 1000;
    srand(time(NULL));
    CellGrid grid(width,height);
    sf::RenderWindow window(sf::VideoMode(1000,1000), "Conway's Game of Life");
    //window.setFramerateLimit(30);
    GridUI ui(width, height);

    for (int i = 0; i < width*height; ++i) {
        if (rand() % 10 + 1 <= 5) {
            grid.cell_map[i] = true;
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        grid.update();
        ui.update_vertices(grid.cell_map);

        window.clear();
        window.draw(ui);
        window.display();
    }
}