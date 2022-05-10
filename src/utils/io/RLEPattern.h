#ifndef GAMEOFLIFE_RLEPATTERN_H
#define GAMEOFLIFE_RLEPATTERN_H

#include <string>
#include "../board/Board.h"

using namespace std;

class RLEPattern {
private:
public:
    Cell** cells;
    int w, h;

    RLEPattern(int w, int h);

    void setCellState(int x, int y, CellState state) const;
};


#endif //GAMEOFLIFE_RLEPATTERN_H
