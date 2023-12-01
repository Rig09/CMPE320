#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class tic {
public:
    tic();
    void setupText(Text& text, Font& font, String phrase);
    void placeShapes(int& placedObjects, int numShapes, CircleShape* shapes, int szGrid, int xOff, int yOff, int rows, int cols, int mouseX, int mouseY);
    void draw(RenderWindow& window, RectangleShape& grid, CircleShape* shapes, int placedObjects, int szGrid, int xOff, int yOff, int rows, int cols);
    void start(RenderWindow& window, int szGrid, int rows, int cols, int xOff, int yOff, String phrase);
    bool checkFail(const bool onGrid[3][3]);
    bool onGrid[3][3] = { false };



private:
    const int rows;
    const int cols;
    int placedObjects;
    int szGrid;
    const int numShapes;

};