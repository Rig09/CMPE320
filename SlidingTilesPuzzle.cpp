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
            handleEvents();
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


        // Set the initial empty tile
        emptyTile = sf::Vector2i(0, 0);
        selectedItem = sf::Vector2i(2, 2);
        itemSize = sf::Vector2i(2, 1);


        // Set the size and color for the selected item (2x1)
        highlightItem(selectedItem.x, selectedItem.y, true);

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

        // Add purple vertical 2x1 item
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

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                handleMouseClick(event.mouseButton.x, event.mouseButton.y);
            }
            else if (event.type == sf::Event::KeyPressed) {
                handleKeyPress(event.key.code);
            }
        }
    }

    void handleMouseClick(float mouseX, float mouseY) {
        // Convert mouse coordinates to grid coordinates
        int gridX = (mouseX - outerBorderWidth) / (tileSize + innerBorderWidth);
        int gridY = (mouseY - outerBorderWidth) / (tileSize + innerBorderWidth);

        // Check if the clicked position is within the grid
        if (gridX >= 0 && gridX < boardSizeX && gridY >= 0 && gridY < boardSizeY) {
            moveItem(gridX, gridY);
        }
    }

    void handleKeyPress(sf::Keyboard::Key key) {
        moveItemWithKey(key);
    }

    void moveItemWithKey(sf::Keyboard::Key key) {
        sf::Vector2i newPosition = selectedItem;

        switch (key) {
        case sf::Keyboard::Up:
            newPosition.y--;
            break;
        case sf::Keyboard::Down:
            newPosition.y++;
            break;
        case sf::Keyboard::Left:
            newPosition.x--;
            break;
        case sf::Keyboard::Right:
            newPosition.x++;
            break;
        default:
            break;
        }

        moveItem(newPosition.x, newPosition.y);
    }

    void moveItem(int x, int y) {
        // Check if the move is valid
        if (isValidMove(x, y)) {
            // Move the item
            for (int i = 0; i < itemSize.x; ++i) {
                for (int j = 0; j < itemSize.y; ++j) {
                    int currentX = selectedItem.x + i;
                    int currentY = selectedItem.y + j;

                    int newX = x + i;
                    int newY = y + j;

                    // Update the tile color and outline
                    tiles[newX][newY].setFillColor(tiles[currentX][currentY].getFillColor());
                    tiles[newX][newY].setOutlineThickness(innerBorderWidth);
                    tiles[currentX][currentY].setFillColor(sf::Color::White);
                    tiles[currentX][currentY].setOutlineThickness(innerBorderWidth);
                }
            }

            // Update selected item coordinates
            selectedItem = sf::Vector2i(x, y);
        }
    }

    bool isValidMove(int x, int y) {
        // Check if the move is within the board boundaries
        if (x < 0 || y < 0 || x + itemSize.x > boardSizeX || y + itemSize.y > boardSizeY) {
            return false;
        }

        // Check if there are no obstacles in the way
        for (int i = 0; i < itemSize.x; ++i) {
            for (int j = 0; j < itemSize.y; ++j) {
                int currentX = selectedItem.x + i;
                int currentY = selectedItem.y + j;

                if (tiles[x + i][y + j].getFillColor() != sf::Color::White && (currentX != x + i || currentY != y + j)) {
                    return false;
                }
            }
        }

        return true;
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
                // Check if the current tile is part of an item
                if (tiles[i][j].getFillColor() == sf::Color::Green || tiles[i][j].getFillColor() == greyColor || tiles[i][j].getFillColor() == sf::Color::Yellow) {
                    // Draw the item without inner borders
                    tiles[i][j].setOutlineThickness(0.f);
                    tiles[i][j].setOutlineColor(tiles[i][j].getFillColor());
                    window.draw(tiles[i][j]);
                }
                else {
                    // Draw other tiles with borders
                    tiles[i][j].setOutlineThickness(innerBorderWidth);
                    window.draw(tiles[i][j]);
                }
            }
        }

        window.display();
    }

    void selectItem(int x, int y) {
        // Check if the clicked tile is part of an item
        if (tiles[x][y].getFillColor() == sf::Color::Green || tiles[x][y].getFillColor() == sf::Color::Magenta || tiles[x][y].getFillColor() == sf::Color::Yellow) {
            highlightItem(selectedItem.x, selectedItem.y, false);
            selectedItem = sf::Vector2i(x, y);

            // Set the size of the selected item
            itemSize = getItemSize(selectedItem.x, selectedItem.y);

            highlightItem(selectedItem.x, selectedItem.y, true);
        }
    }

    void highlightItem(int startX, int startY, bool highlight) {
        for (int i = 0; i < itemSize.x; ++i) {
            for (int j = 0; j < itemSize.y; ++j) {
                int x = startX + i;
                int y = startY + j;

                if (x >= 0 && x < boardSizeX && y >= 0 && y < boardSizeY) {
                    if (highlight) {
                        tiles[x][y].setOutlineColor(sf::Color::Blue);
                    }
                    else {
                        tiles[x][y].setOutlineColor(sf::Color::Black);
                    }
                }
            }
        }
    }

    void unhighlightItem(int startX, int startY) {
        for (int i = 0; i < itemSize.x; ++i) {
            for (int j = 0; j < itemSize.y; ++j) {
                int x = startX + i;
                int y = startY + j;

                if (x >= 0 && x < boardSizeX && y >= 0 && y < boardSizeY) {
                    tiles[x][y].setOutlineColor(sf::Color::Black);
                }
            }
        }
    }

    sf::Vector2i getItemSize(int startX, int startY) {
        sf::Vector2i size(1, 1);

        sf::Color itemColor = tiles[startX][startY].getFillColor();

        // Check the size of the item in the horizontal direction
        for (int i = startX + 1; i < boardSizeX; ++i) {
            if (tiles[i][startY].getFillColor() == itemColor) {
                size.x++;
            }
            else {
                break;
            }
        }

        // Check the size of the item in the vertical direction
        for (int j = startY + 1; j < boardSizeY; ++j) {
            if (tiles[startX][j].getFillColor() == itemColor) {
                size.y++;
            }
            else {
                break;
            }
        }

        return size;
    }
};

int main() {
    SlidingTilesPuzzle puzzle;
    puzzle.run();

    return 0;
}
