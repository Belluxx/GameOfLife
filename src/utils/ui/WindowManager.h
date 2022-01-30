#ifndef GAMEOFLIFE_WINDOWMANAGER_H
#define GAMEOFLIFE_WINDOWMANAGER_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "../board/Board.h"

using namespace std;

class WindowManager {
private:
    float colWidth;
    float rowHeight;
    int delayForIteration;
    bool draggingMouse;
    bool** matrix;

    void drawColumn(float x, float thickness, sf::Color col) const;

    void drawRow(float y, float thickness, sf::Color col) const;

    void drawRect(float w, float h, sf::Vector2f pos, sf::Color col) const;

    void drawGrid(int columns, int rows, float thickness, sf::Color col);

public:
    sf::RenderWindow* window;
    sf::Clock clock;
    Board* board;

    bool paused;

    WindowManager(int w, int h, const string &title, int fps, int delayForIteration, Board* board);

    void update();

    bool isRunning() const;

    int getWidth() const;

    int getHeight() const;

    void drawMatrix(int columns, int rows, float thickness, sf::Color col, bool** activationMatrix, sf::Color activationCol);
};


#endif //GAMEOFLIFE_WINDOWMANAGER_H
