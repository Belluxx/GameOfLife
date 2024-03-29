#ifndef GAMEOFLIFE_BOARD_H
#define GAMEOFLIFE_BOARD_H

enum class CellState {
    ALIVE,
    DEAD
};

class Cell {
public:
    CellState state;
    int x, y;

    Cell(CellState state, int x, int y);

    Cell();
};

class Board {
private:
    static const int MIN_NEIGHBOURS = 2;
    static const int MAX_NEIGHBOURS = 3;
    static const int NEW_NEIGHBOURS = 3;

    Cell** cells1;
    Cell** cells2;

    CellState evaluateNextState(Cell c);

    bool positionValid(int x, int y) const;

public:
    int h, w;
    unsigned long long int iteration;

    Board(int w, int h);

    void insertPattern(int x, int y, const Cell* pattern, const int patternSize);

    void next();

    void reset();

    CellState getActualState(int x, int y);

    void setActualState(int x, int y, CellState state);

    void getMatrix(bool** matrix);
};


#endif //GAMEOFLIFE_BOARD_H
