#include "WindowManager.h"

WindowManager::WindowManager(int w, int h, const string &title, int fps, int delayForIteration, Board* board) {
    this->window = new sf::RenderWindow(sf::VideoMode(w, h), title);
    this->delayForIteration = delayForIteration;
    this->board = board;
    this->window->setFramerateLimit(fps);
    this->draggingMouse = false;

    this->colWidth = (float) getWidth() / (float) this->board->w;
    this->rowHeight = (float) getHeight() / (float) this->board->h;

    this->matrix = new bool* [this->board->h];
    for (int y = 0; y < this->board->h; y++) {
        this->matrix[y] = new bool[this->board->w];
    }
}

void WindowManager::update() {
    int ms = clock.getElapsedTime().asMilliseconds();
    board->getMatrix(matrix);

    drawMatrix(board->w, board->h, 1, sf::Color(0x111111FF), matrix, sf::Color::White);

    if (ms > delayForIteration && !draggingMouse) {
        board->next();
        board->getMatrix(matrix);
        clock.restart();
    }

    sf::Event event{};
    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    const int x = event.mouseButton.x;
                    const int y = event.mouseButton.y;
                    cout << "Click at: " << x << " " << y << endl;

                    draggingMouse = true;
                    board->setActualState(x / (int) colWidth, y / (int) rowHeight, CellState::ALIVE);
                }
                break;

            case sf::Event::MouseMoved:
                if (draggingMouse) {
                    // Here event.mouseButton.x/y doesn't work as expected
                    const int x = (int) event.size.width;
                    const int y = (int) event.size.height;
                    cout << "Dragging at: " << x << " " << y << endl;

                    board->setActualState(x / (int) colWidth, y / (int) rowHeight, CellState::ALIVE);
                }
                break;

            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    const int x = event.mouseButton.x;
                    const int y = event.mouseButton.y;
                    cout << "Release at: " << x << " " << y << endl;
                    draggingMouse = false;
                }
                break;
        }
    }

    window->display();
    window->clear(sf::Color::Black);
}

bool WindowManager::isRunning() const {
    return window->isOpen();
}

int WindowManager::getWidth() const {
    return (int) window->getSize().x;
}

int WindowManager::getHeight() const {
    return (int) window->getSize().y;
}

void WindowManager::drawRect(float w, float h, sf::Vector2f pos, sf::Color col) const {
    sf::RectangleShape square(sf::Vector2f(w, h));
    square.setFillColor(col);
    square.setPosition(pos);

    window->draw(square);
}

void WindowManager::drawColumn(float x, float thickness, sf::Color col) const {
    sf::RectangleShape line(sf::Vector2f(thickness, (float) getHeight()));
    line.setPosition(x, 0);
    line.setFillColor(col);

    window->draw(line);
}

void WindowManager::drawRow(float y, float thickness, sf::Color col) const {
    sf::RectangleShape line(sf::Vector2f((float) getWidth(), thickness));
    line.setPosition(0, y);
    line.setFillColor(col);

    window->draw(line);
}

void WindowManager::drawGrid(int columns, int rows, float thickness, sf::Color col) {
    for (int c = 0; c < columns; c++) {
        drawColumn(colWidth * (float) c, thickness, col);
    }

    for (int r = 0; r < columns; r++) {
        drawRow(rowHeight * (float) r, thickness, col);
    }
}

void WindowManager::drawMatrix(int columns, int rows, float thickness, sf::Color col, bool** activationMatrix,
                               sf::Color activationCol) {
    drawGrid(columns, rows, thickness, col);

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            if (activationMatrix[y][x]) {
                drawRect(colWidth, rowHeight, sf::Vector2f(colWidth * (float) x, rowHeight * (float) y), activationCol);
            }
        }
    }
}
