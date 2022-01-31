#ifndef GAMEOFLIFE_PATTERNS_H
#define GAMEOFLIFE_PATTERNS_H

#include "Board.h"

class Patterns {
public:
    static const int GLIDER_SIZE = 5;
    static const Cell GLIDER[];

    static const int R_PENTOMINO_SIZE = 5;
    static const Cell R_PENTOMINO[R_PENTOMINO_SIZE];
};


#endif //GAMEOFLIFE_PATTERNS_H
