#include <iostream>
#include <SFML/Graphics.hpp>
#include "utils/board/Board.h"
#include "utils/ui/WindowManager.h"

using namespace std;

#define FPS 60
#define ITERATION_DELAY 50
#define COLUMNS 160
#define ROWS 90

int main() {
    static Cell R_PENTOMINO[5] = {
            Cell(CellState::ALIVE, 0, 0),
            Cell(CellState::ALIVE, 0, 1),
            Cell(CellState::ALIVE, -1, 0),
            Cell(CellState::ALIVE, 0, -1),
            Cell(CellState::ALIVE, 1, -1),
    };

    static Cell GLIDER[5] = {
            Cell(CellState::ALIVE, -1, 1),
            Cell(CellState::ALIVE, 0, 1),
            Cell(CellState::ALIVE, 1, 1),
            Cell(CellState::ALIVE, 1, 0),
            Cell(CellState::ALIVE, 0, -1),
    };

    Board b(COLUMNS, ROWS);
    b.setInitialPattern(R_PENTOMINO, 5);

    bool** matrix = new bool*[b.h];
    for (int y = 0; y < b.h; y++) {
        matrix[y] = new bool[b.w];
    }

    WindowManager wm(1920, 1080, "Game of life");
    wm.window->setFramerateLimit(FPS);
    sf::Clock c;
    b.getMatrix(matrix);
    while (wm.isRunning()) {
        int ms = c.getElapsedTime().asMilliseconds();

        wm.drawMatrix(b.w, b.h, 1, sf::Color(0x111111FF), matrix, sf::Color::White);
        wm.update();
        if (ms > ITERATION_DELAY) {
            b.next();
            b.getMatrix(matrix);
            c.restart();
        }
    }

    return 0;
}
