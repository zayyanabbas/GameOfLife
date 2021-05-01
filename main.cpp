#include <iostream>
#include <random>
#include <bits/stdc++.h>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "ui_code.hpp"

struct CellGrid {
    bool* cell_map;
    uint width;
    uint height;

    CellGrid(const uint& _width, const uint& _height) {
        width = _width;
        height = _height;
        cell_map = new bool[width*height];
    }

    void next_generation(bool* new_location) {
        for (uint y = 0; y < height; ++y) {
            for (uint x = 0; x < width; ++x) {
                // Get neighbours
                int neighbours = 0;
                for (int ry = -1; ry <= 1; ++ry) {
                    for (int rx = -1; rx <= 1; ++rx) {
                        if (x + rx > width || x + rx < 0 || y + ry > width || y + ry < 0 || (rx == 0 && ry == 0)) continue;

                        neighbours += cell_map[height * (x + rx) + (y + ry)];
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
        bool* temp_map = new bool[width*height];
        next_generation(temp_map);
        memcpy(cell_map, temp_map, (width*height) * sizeof *temp_map);
        delete[] temp_map;
    }

    ~CellGrid() {
        delete[] cell_map;
    }
};

int main() {
    srand(time(NULL));
    CellGrid grid(100,100);
    sf::RenderWindow window(sf::VideoMode(1000,1000), "Conway's Game of Life");
    window.setFramerateLimit(60);
    GridUI ui(100, 100);

    for (int i = 0; i < 100*100; ++i) {
        if (rand() % 10 + 1 <= 5) {
            grid.cell_map[i] = true;
        }
    }
    //print_grid(grid);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        grid.update();
        ui.update_vertices(grid.cell_map);

        window.clear(sf::Color::Blue);
        window.draw(ui);
        window.display();
    }

    //grid.update();
    //system("clear");
    //print_grid(grid);
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    
}