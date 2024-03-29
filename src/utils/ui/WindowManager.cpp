#include "WindowManager.h"
#include "../board/Patterns.h"

WindowManager::WindowManager(int w, int h, const string &title, int fps, int delayForIteration, Board* board) {
    this->window = new sf::RenderWindow(sf::VideoMode(w, h), title, sf::Style::Titlebar | sf::Style::Close);
    this->delayForIteration = delayForIteration;
    this->board = board;
    this->window->setFramerateLimit(fps);
    this->draggingMouse = false;
    this->placingPattern = false;
    this->paused = false;

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

    if (ms > delayForIteration && !draggingMouse && !paused) {
        board->next();
        board->getMatrix(matrix);
        clock.restart();
    }

    sf::Event event{};
    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed: {
                window->close();
                break;
            }

            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                    case sf::Keyboard::Space:
                        paused = !paused;
                        break;

                    case sf::Keyboard::P:
                        placingPattern = !placingPattern;
                        break;

                    case sf::Keyboard::R:
                        board->reset();
                        break;

                    case sf::Keyboard::Up:
                        if (delayForIteration > 0) {
                            delayForIteration -= 30;
                        }
                        break;

                    case sf::Keyboard::Down:
                        if (delayForIteration < 1000) {
                            delayForIteration += 30;
                        }
                        break;
                    
                    default:
                        cout << "Unknown key pressed: " << event.key.code << endl;
                        break;
                }
            }

            case sf::Event::KeyReleased: {
                break;
            }

            case sf::Event::MouseButtonPressed: {
                const int x = event.mouseButton.x;
                const int y = event.mouseButton.y;
                const int cellX = x / (int) colWidth;
                const int cellY = y / (int) rowHeight;
                cout << "Click at: " << x << " " << y << endl;

                // TODO: Replace boolean pattern selection with number from keyboard associated with pattern
                if (placingPattern) {
                    board->insertPattern(cellX, cellY, Patterns::GLIDER, Patterns::GLIDER_SIZE);
                } else {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        draggingMouse = true;
                        board->setActualState(cellX, cellY, CellState::ALIVE);
                    }
                }
                break;
            }

            case sf::Event::MouseMoved: {
                if (draggingMouse) {
                    // Here event.mouseButton.x/y doesn't work as expected
                    const int x = (int) event.size.width;
                    const int y = (int) event.size.height;
                    cout << "Dragging at: " << x << " " << y << endl;

                    board->setActualState(x / (int) colWidth, y / (int) rowHeight, CellState::ALIVE);
                }
                break;
            }

            case sf::Event::MouseButtonReleased: {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    const int x = event.mouseButton.x;
                    const int y = event.mouseButton.y;
                    cout << "Release at: " << x << " " << y << endl;
                    draggingMouse = false;
                }
                break;
            }

            case sf::Event::TextEntered: {
                cout << "Char pressed: " << static_cast<char>(event.text.unicode) << endl;
                break;
            }

            case sf::Event::GainedFocus: {
                cout << "Gained focus" << endl;
                break;
            }

            case sf::Event::LostFocus: {
                cout << "Lost focus" << endl;
                break;
            }

            case sf::Event::MouseEntered: {
                cout << "Mouse entered the window" << endl;
                break;
            }

            case sf::Event::MouseLeft: {
                cout << "Mouse exited the window" << endl;
                break;
            }

            default: {
                cout << "Unknown event occurred: " << event.type << endl;
                break;
            }
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
