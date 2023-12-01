#include "tic.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

// Initialize the constructor with values
tic::tic() :rows(3), cols(3), placedObjects(0), szGrid(100), numShapes(0) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            onGrid[i][j] = false;
        }
    }
}

// Creates a phrase
void tic::setupText(Text& text, Font& font, String phrase) {
    text.setFont(font);
    text.setCharacterSize(40);
    text.setFillColor(Color::Blue);
    text.setString(phrase);
    text.setPosition(180, 60);
}

// Places the circles
void tic::placeShapes(int& placedObjects, int numShapes, CircleShape* shapes, int szGrid, int xOff, int yOff, int rows, int cols, int mouseX, int mouseY)
{
    // Iterate over the max number of shapes (6).
    if (placedObjects < numShapes) {
        if (mouseX >= 0 && mouseX < rows && mouseY >= 0 && mouseY < cols) {
            shapes[placedObjects] = CircleShape(40.f);
            shapes[placedObjects].setFillColor(Color::Green);
            shapes[placedObjects].setPosition(Vector2f(szGrid * mouseX + xOff + 10, szGrid * mouseY + yOff + 10));
            placedObjects++;
        }
    }
}

void tic::draw(RenderWindow& window, RectangleShape& grid, CircleShape* shapes, int placedObjects, int szGrid, int xOff, int yOff, int rows, int cols) {
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            grid.setPosition(Vector2f(szGrid * x + xOff, szGrid * y + yOff));
            window.draw(grid);
        }
    }
    for (int i = 0; i < placedObjects; ++i) {
        window.draw(shapes[i]);
    }
}


// Checks if the user solved tic tac toe (results in a fail)
bool tic::checkFail(const bool onGrid[3][3])
{
    // Vertical line wins
    for (int row = 0; row < 3; row++) {
        if (onGrid[row][0] && onGrid[row][1] && onGrid[row][2]) {
            return true;
        }
    }

    // Horizontal line wins
    for (int col = 0; col < 3; col++) {
        if (onGrid[0][col] && onGrid[1][col] && onGrid[2][col]) {
            return true;
        }
    }

    // Diagonal Wins
    if ((onGrid[0][0] && onGrid[1][1] && onGrid[2][2])) {
        return true;
    }

    if ((onGrid[0][2] && onGrid[1][1] && onGrid[2][0])) {
        return true;
    }

    // False if the puzzle has not been failed
    return false;
}