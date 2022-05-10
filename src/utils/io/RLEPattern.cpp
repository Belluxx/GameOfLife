#include "RLEPattern.h"

RLEPattern::RLEPattern(int w, int h) {
    this->w = w;
    this->h = h;

    cells = new Cell* [h];
    for (int i = 0; i < h; i++)
        cells[i] = new Cell[w];

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            cells[y][x].x = x;
            cells[y][x].y = y;
        }
    }
}

void RLEPattern::setCellState(int x, int y, CellState state) const {
    cells[y][x].state = state;
}
