#include "SFML/Graphics.hpp"
#include "Button.h"
#include "tic.h"


using namespace sf;
using namespace std;

bool ticPuzzleWon = false;
bool boxPuzzleWon = false;

enum class GameState {
    MainMenu,
    GamePlay
};


int main()
{

    RenderWindow window(VideoMode(960, 720), "Escape320");

    GameState gameState = GameState::MainMenu;

    Texture bgTexture;
    if (!bgTexture.loadFromFile("brick-wall.png")) {
        return -1;
    }
    Sprite bgSprite1(bgTexture);
    bgSprite1.setPosition(0, 0);
    bgSprite1.setScale(1, 1);

    Texture titleTexture;
    if (!titleTexture.loadFromFile("title.png")) {
        return -1;
    }
    Sprite titleSprite(titleTexture);
    titleSprite.setPosition(182, 55);
    titleSprite.setScale(1.225, 1.225);

    Texture playButtonTexture;
    Texture optionsButtonTexture;
    Texture exitButtonTexture;
    Texture playButtonHoverTexture;
    Texture optionsButtonHoverTexture;
    Texture exitButtonHoverTexture;
    if (!playButtonTexture.loadFromFile("play-button.png") ||
        !optionsButtonTexture.loadFromFile("options-button.png") ||
        !exitButtonTexture.loadFromFile("exit-button.png") ||
        !playButtonHoverTexture.loadFromFile("play-button-hover.png") ||
        !optionsButtonHoverTexture.loadFromFile("options-button-hover.png") ||
        !exitButtonHoverTexture.loadFromFile("exit-button-hover.png")) {
        return -1;
    }

    Button playButton(365, 335, 230, 94, playButtonTexture, playButtonHoverTexture);
    Button optionsButton(365, 455, 230, 94, optionsButtonTexture, optionsButtonHoverTexture);
    Button exitButton(365, 575, 230, 94, exitButtonTexture, exitButtonHoverTexture);



    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                if (playButton.isMouseOver(window)) {
                    // Handle play button click (e.g., start the game)
                }
                else if (optionsButton.isMouseOver(window)) {
                    // Handle options button click
                }
                else if (exitButton.isMouseOver(window)) {
                    window.close(); // Close the window for the exit button
                }
            }

        }

        // Update game logic based on current state
        switch (gameState) {
        case GameState::MainMenu:
            // Update main menu logic
            if (playButton.isClicked(window)) {
                gameState = GameState::GamePlay; // Switch to the game state
            }
            playButton.isMouseOver(window);
            optionsButton.isMouseOver(window);
            exitButton.isMouseOver(window);
            break;

        case GameState::GamePlay:
            //if (boxPuzzleWon = false) {
            int placedObjects = 0;
            const int numShapes = 6;
            CircleShape shapes[numShapes];
            int szGrid = 100;
            const int rows = 3;
            const int cols = 3;
            bool onGrid[rows][cols] = { false };

            tic game;

            Font font;
            if (!font.loadFromFile("C:/Windows/Fonts/calibri.ttf")) {
                // Handle font loading failure here
                return EXIT_FAILURE;
            }

            RenderWindow window(VideoMode(800, 600), "Tic Tac Toe");

            Text text;

            String msg = "Place 6 Os without solving tic tac toe";

            game.setupText(text, font, msg);


            int xOff = (window.getSize().x - szGrid * rows) / 2;
            int yOff = (window.getSize().y - szGrid * cols) / 2;

            RectangleShape grid(Vector2f(szGrid, szGrid));
            grid.setFillColor(Color::Transparent);
            grid.setOutlineThickness(3.0f);
            grid.setOutlineColor(Color::White);


            while (window.isOpen()) {
                Event event;
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed) {
                        window.close();
                    }

                    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                        window.close();
                    }

                    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                        int mouseX = (event.mouseButton.x - xOff) / szGrid;
                        int mouseY = (event.mouseButton.y - yOff) / szGrid;
                        if (!onGrid[mouseY][mouseX] && placedObjects < 6 && !game.checkFail(onGrid)) {
                            game.placeShapes(placedObjects, numShapes, shapes, szGrid, xOff, yOff, rows, cols, mouseX, mouseY);
                            onGrid[mouseY][mouseX] = true;

                            if (game.checkFail(onGrid)) {
                                msg = "Game over you lose";
                                game.setupText(text, font, msg);

                            }

                            if (placedObjects == 6 && !game.checkFail(onGrid)) {
                                msg = "You win";
                                game.setupText(text, font, msg);
                                bool boxPuzzleWon = true;
                            }
                        }
                    }
                    window.clear();
                    game.draw(window, grid, shapes, placedObjects, szGrid, xOff, yOff, rows, cols);
                    game.setupText(text, font, msg);
                    window.draw(text);
                    window.display();
                }

                //}

            }

            break;
        }

        // Clear window 
        window.clear();

        // Draw based on current state
        switch (gameState) {
        case GameState::MainMenu:
            // Draw main menu elements
            window.draw(bgSprite1);
            window.draw(titleSprite);
            playButton.draw(window);
            optionsButton.draw(window);
            exitButton.draw(window);

            break;

        case GameState::GamePlay:
            // Draw game play elements

            break;
        }


        // Display content
        window.display();
    }

    return 0;

}