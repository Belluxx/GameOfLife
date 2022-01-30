#include "utils/board/Board.h"
#include "utils/ui/WindowManager.h"

#define FPS 60
#define ITERATION_DELAY 50
#define WINDOOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define COLUMNS WINDOOW_WIDTH/10
#define ROWS WINDOW_HEIGHT/10

int main() {
    static Cell R_PENTOMINO[5] = {
            Cell(CellState::ALIVE, 0, 0),
            Cell(CellState::ALIVE, 0, 1),
            Cell(CellState::ALIVE, -1, 0),
            Cell(CellState::ALIVE, 0, -1),
            Cell(CellState::ALIVE, 1, -1),
    };

    Board b(COLUMNS, ROWS);
    b.setInitialPattern(R_PENTOMINO, 5);

    WindowManager wm(WINDOOW_WIDTH, WINDOW_HEIGHT, "Game of life", FPS, ITERATION_DELAY, &b);
    while (wm.isRunning()) {
        wm.update();
    }

    return 0;
}
