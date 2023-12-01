#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

const int boardSizeX = 8;
const int boardSizeY = 6;
const int boardSize = 6;
const float tileSize = 60.f;
const float outerBorderWidth = 10.f;
const float innerBorderWidth = 2.f;
const float animationSpeed = 400.f;  // Pixels per second
const sf::Color greyColor(128, 128, 128);

class SlidingTilesPuzzle {
public:
    SlidingTilesPuzzle() : window(sf::VideoMode(boardSizeX* tileSize + 2 * outerBorderWidth, boardSizeY* tileSize + 2 * outerBorderWidth), "Sliding Tiles Puzzle") {
        initializeBoard();
    }

    void run() {
        while (window.isOpen()) {
            update();
            draw();
        }
    }

private:
    sf::RenderWindow window;
    sf::RectangleShape tiles[boardSizeX][boardSizeY];
    sf::RectangleShape border;

    sf::Vector2i emptyTile;  // Coordinates of the empty tile
    sf::Vector2i selectedItem;  // Coordinates of the selected item
    sf::Vector2i itemSize;  // Size of the selected item (width, height)

    void initializeBoard() {
        // Set the border around the grid
        border.setSize(sf::Vector2f(boardSizeX * tileSize + 2 * outerBorderWidth, boardSizeY * tileSize + 2 * outerBorderWidth));
        border.setPosition(0, 0);
        border.setFillColor(sf::Color::Black);


        // Initialize tiles with new board size
        for (int i = 0; i < boardSizeX; ++i) {
            for (int j = 0; j < boardSizeY; ++j) {
                tiles[i][j].setSize(sf::Vector2f(tileSize, tileSize));
                tiles[i][j].setPosition(outerBorderWidth + i * (innerBorderWidth + tileSize), outerBorderWidth + j * (innerBorderWidth + tileSize));
                tiles[i][j].setOutlineThickness(innerBorderWidth);
                tiles[i][j].setOutlineColor(sf::Color::Black);
                tiles[i][j].setFillColor(sf::Color::White);
            }
        }

        //Add black wall on the right:
        addBlackItem(2, 2, 6, 0);
        addBlackItem(2, 3, 6, 3);

        // Add green horizontal 2x1 items
        addGreenItem(2, 1, 2, 0);
        addGreyItem(2, 1, 4, 0);
        addGreenItem(2, 1, 0, 3);
        addGreenItem(2, 1, 4, 4);
        addYellowItem(2, 1, 0, 5);
        addGreenItem(2, 1, 2, 5);

        // Add grey vertical 2x1 item
        addGreyItem(1, 2, 3, 3);

        // Add yellow vertical 3x1 items
        addYellowItem(1, 3, 1, 0);
        addYellowItem(1, 3, 5, 1);
        addRedItem(2, 1, 2, 2);
    }






    void addGreenItem(int width, int height, int startX, int startY) {
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                int x = startX + i;
                int y = startY + j;

                if (x >= 0 && x < boardSizeX && y >= 0 && y < boardSizeY) {
                    tiles[x][y].setSize(sf::Vector2f(tileSize, tileSize));
                    tiles[x][y].setFillColor(sf::Color::Green);
                    tiles[x][y].setOutlineThickness(innerBorderWidth);
                    tiles[x][y].setOutlineColor(sf::Color::Green);

                }
            }
        }
    }

    void addBlackItem(int width, int height, int startX, int startY) {
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                int x = startX + i;
                int y = startY + j;

                if (x >= 0 && x < boardSizeX && y >= 0 && y < boardSizeY) {
                    tiles[x][y].setSize(sf::Vector2f(tileSize, tileSize));
                    tiles[x][y].setFillColor(sf::Color::Black);
                    tiles[x][y].setOutlineThickness(innerBorderWidth);
                    tiles[x][y].setOutlineColor(sf::Color::Black);
                }
            }
        }
    }

    void addGreyItem(int width, int height, int startX, int startY) {

        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                int x = startX + i;
                int y = startY + j;

                if (x >= 0 && x < boardSizeX && y >= 0 && y < boardSizeY) {
                    tiles[x][y].setSize(sf::Vector2f(tileSize, tileSize));
                    tiles[x][y].setFillColor(greyColor);
                    tiles[x][y].setOutlineThickness(innerBorderWidth);
                    tiles[x][y].setOutlineColor(greyColor);

                }
            }
        }
    }

    void addYellowItem(int width, int height, int startX, int startY) {
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                int x = startX + i;
                int y = startY + j;

                if (x >= 0 && x < boardSizeX && y >= 0 && y < boardSizeY) {
                    tiles[x][y].setSize(sf::Vector2f(tileSize, tileSize));
                    tiles[x][y].setFillColor(sf::Color::Yellow);
                    tiles[x][y].setOutlineThickness(innerBorderWidth);
                    tiles[x][y].setOutlineColor(sf::Color::Yellow);
                }
            }
        }
    }

    void addRedItem(int width, int height, int startX, int startY) {
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                int x = startX + i;
                int y = startY + j;

                if (x >= 0 && x < boardSizeX && y >= 0 && y < boardSizeY) {
                    tiles[x][y].setSize(sf::Vector2f(tileSize, tileSize));
                    tiles[x][y].setFillColor(sf::Color::Red);
                    tiles[x][y].setOutlineThickness(innerBorderWidth);
                    tiles[x][y].setOutlineColor(sf::Color::Red);
                }
            }
        }
    }


    void update() {
        // Update logic goes here
    }

    void draw() {
        window.clear();

        // Draw the border
        window.draw(border);

        // Draw the tiles
        for (int i = 0; i < boardSizeX; ++i) {
            for (int j = 0; j < boardSizeY; ++j) {
                window.draw(tiles[i][j]);
               
            }
        }

        window.display();
    }
};

int main() {
    SlidingTilesPuzzle puzzle;
    puzzle.run();

    return 0;
}
