#include "WindowManager.h"

WindowManager::WindowManager(int w, int h, const string &title) {
    window = new sf::RenderWindow(sf::VideoMode(w, h), title);
}

void WindowManager::update() {
    sf::Event event{};
    while(window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) window->close();
    }


    window->display();
    window->clear(sf::Color::Black);
}

bool WindowManager::isRunning() {
    return window->isOpen();
}

int WindowManager::getWidth() {
    return (int) window->getSize().x;
}

int WindowManager::getHeight() {
    return (int) window->getSize().y;
}

void WindowManager::drawLine(sf::Vector2f start, sf::Vector2f end, sf::Color col) {
    sf::Vertex line[] = {
            sf::Vertex(start),
            sf::Vertex(end)
    };
    line[0].color = col;
    line[1].color = col;

    window->draw(line, 2, sf::Lines);
}

void WindowManager::drawRect(float w, float h, sf::Vector2f pos, sf::Color col) {
    sf::RectangleShape square(sf::Vector2f(w, h));
    square.setFillColor(col);
    square.setPosition(pos);

    window->draw(square);
}

void WindowManager::drawColumn(float x, float thickness, sf::Color col) {
    sf::RectangleShape line(sf::Vector2f(thickness, (float) getHeight()));
    line.setPosition(x, 0);
    line.setFillColor(col);

    window->draw(line);
}

void WindowManager::drawRow(float y, float thickness, sf::Color col) {
    sf::RectangleShape line(sf::Vector2f((float) getWidth(), thickness));
    line.setPosition(0, y);
    line.setFillColor(col);

    window->draw(line);
}

void WindowManager::drawGrid(int columns, int rows, float thickness, sf::Color col) {
    const float colWidth = (float) getWidth() / (float) columns;
    const float rowHeight = (float) getHeight() / (float) rows;

    for (int c = 0; c < columns; c++) {
        drawColumn(colWidth * (float) c, thickness, col);
    }

    for (int r = 0; r < columns; r++) {
        drawRow(rowHeight * (float) r, thickness, col);
    }
}

void WindowManager::drawMatrix(int columns, int rows, float thickness, sf::Color col, bool** activationMatrix, sf::Color activationCol) {
    drawGrid(columns, rows, thickness, col);

    const float colWidth = (float) getWidth() / (float) columns;
    const float rowHeight = (float) getHeight() / (float) rows;
    const int cells = columns * rows;

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            if (activationMatrix[y][x]) {
                drawRect(colWidth, rowHeight, sf::Vector2f(colWidth * (float) x, rowHeight * (float) y), activationCol);
            }
        }
    }
}
