#include <iostream>
#include "Board.h"

using namespace std;

Cell::Cell(CellState state, int x, int y) {
    this->x = x;
    this->y = y;
    this->state = state;
}

Cell::Cell() {
    this->x = 0;
    this->y = 0;
    this->state = CellState::DEAD;
}

Board::Board(int w, int h) {
    this->w = w;
    this->h = h;
    this->iteration = 0;

    cells1 = new Cell* [h];
    for (int i = 0; i < h; i++)
        cells1[i] = new Cell[w];

    cells2 = new Cell* [h];
    for (int i = 0; i < h; i++)
        cells2[i] = new Cell[w];

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            cells1[y][x].x = x;
            cells1[y][x].y = y;
            cells2[y][x].x = x;
            cells2[y][x].y = y;
        }
    }
}

CellState Board::getNextState(Cell c) {
    int neighbors = 0;

    neighbors += getState(c.x - 1, c.y - 1) == CellState::ALIVE;
    neighbors += getState(c.x + 0, c.y - 1) == CellState::ALIVE;
    neighbors += getState(c.x + 1, c.y - 1) == CellState::ALIVE;
    neighbors += getState(c.x - 1, c.y + 0) == CellState::ALIVE;
    neighbors += getState(c.x + 1, c.y + 0) == CellState::ALIVE;
    neighbors += getState(c.x - 1, c.y + 1) == CellState::ALIVE;
    neighbors += getState(c.x + 0, c.y + 1) == CellState::ALIVE;
    neighbors += getState(c.x + 1, c.y + 1) == CellState::ALIVE;

    if (neighbors < MIN_NEIGHBOURS) return CellState::DEAD;
    if (neighbors == NEW_NEIGHBOURS) return CellState::ALIVE;
    if (neighbors > MAX_NEIGHBOURS) return CellState::DEAD;
    return c.state;
}

CellState Board::getState(int x, int y) {
    if (iteration % 2 == 0) {
        if (positionValid(x, y)) return cells1[y][x].state;
    } else {
        if (positionValid(x, y)) return cells2[y][x].state;
    }

    return CellState::DEAD;
}

void Board::setActualState(int x, int y, CellState state) {
    if (iteration % 2 == 0) {
        if (positionValid(x, y)) cells1[y][x].state = state;
    } else {
        if (positionValid(x, y)) cells2[y][x].state = state;
    }
}

bool Board::positionValid(int x, int y) const {
    return (x >= 0 && x < w) && (y >= 0 && y < h);
}

/**
 * Applies a pattern to the current board. Note that the coordinates of the cells
 * in the pattern must be relative from the center of the board.
 * @param pattern the array of cells that defines the pattern
 * @param patternSize the length of the cells array
 */
void Board::setInitialPattern(Cell* pattern, int patternSize) {
    for (int i = 0; i < patternSize; i++) {
        Cell c = pattern[i];
        setActualState(w / 2 + c.x, h / 2 + c.y, c.state);
    }
}

void Board::next() {
    if (iteration % 2 == 0) {
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                cells2[y][x].state = getNextState(cells1[y][x]);
            }
        }
    } else {
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                cells1[y][x].state = getNextState(cells2[y][x]);
            }
        }
    }

    iteration++;
}

void Board::getMatrix(bool** matrix) {
    if (iteration % 2 == 0) {
        for (int y = 0; y < h; y++) for (int x = 0; x < w; x++) matrix[y][x] = (cells1[y][x].state == CellState::ALIVE);
    } else {
        for (int y = 0; y < h; y++) for (int x = 0; x < w; x++) matrix[y][x] = (cells2[y][x].state == CellState::ALIVE);
    }
}

