#ifndef GAMEOFLIFE_RLEPARSER_H
#define GAMEOFLIFE_RLEPARSER_H

#include <string>
#include <fstream>
#include "../board/Board.h"
#include "RLEPattern.h"

using namespace std;

class RLEParser {
private:
    static bool strStartsWith(const string& s, const string& sub);
public:
    static RLEPattern parseFile(const string& filename);

    static int firstNumber(const string& s);

    static int lastNumber(const string& s);
};


#endif //GAMEOFLIFE_RLEPARSER_H
