#ifndef GAMEOFLIFE_WINDOWMANAGER_H
#define GAMEOFLIFE_WINDOWMANAGER_H

#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class WindowManager {
private:

public:
    sf::RenderWindow* window;

    WindowManager(int w, int h, const string &title);

    void update();

    bool isRunning();

    int getWidth();

    int getHeight();

    void drawLine(sf::Vector2f start, sf::Vector2f end, sf::Color col);

    void drawColumn(float x, float thickness, sf::Color col);

    void drawRow(float y, float thickness, sf::Color col);

    void drawRect(float w, float h, sf::Vector2f pos, sf::Color col);

    void drawGrid(int columns, int rows, float thickness, sf::Color col);

    void drawMatrix(int columns, int rows, float thickness, sf::Color col, bool** activationMatrix, sf::Color activationCol);
};


#endif //GAMEOFLIFE_WINDOWMANAGER_H
