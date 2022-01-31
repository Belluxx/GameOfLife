#include "Patterns.h"

const Cell Patterns::GLIDER[GLIDER_SIZE] = {
        Cell(CellState::ALIVE, -1, 1),
        Cell(CellState::ALIVE, 0, 1),
        Cell(CellState::ALIVE, 1, 1),
        Cell(CellState::ALIVE, 1, 0),
        Cell(CellState::ALIVE, 0, -1),
};

const Cell Patterns::R_PENTOMINO[R_PENTOMINO_SIZE] = {
        Cell(CellState::ALIVE, 0, 0),
        Cell(CellState::ALIVE, 0, 1),
        Cell(CellState::ALIVE, -1, 0),
        Cell(CellState::ALIVE, 0, -1),
        Cell(CellState::ALIVE, 1, -1),
};