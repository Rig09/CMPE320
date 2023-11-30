#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

enum class GameState {
    MainMenu,
    GamePlay
};

class Button {
public:
    Button(float x, float y, float width, float height, Texture& texture, Texture& hoverTexture);

    bool isMouseOver(RenderWindow& window);
    bool isClicked(sf::RenderWindow& window);
    void draw(RenderWindow& window);

private:
    RectangleShape shape;
    const Texture& buttonTexture;
    const Texture& hoverTexture;
};

Button::Button(float x, float y, float width, float height, Texture& texture, Texture& hoverTexture)
    : buttonTexture(texture), hoverTexture(hoverTexture) {
    shape.setPosition(x, y);
    shape.setSize(Vector2f(width, height));
    shape.setTexture(&buttonTexture);
}

bool Button::isMouseOver(RenderWindow& window) {
    Vector2f mousePosition = Vector2f(Mouse::getPosition(window));
    bool isOver = shape.getGlobalBounds().contains(mousePosition);

    if (isOver) {
        shape.setTexture(&hoverTexture); // Change texture to show when hovered
    }
    else {
        shape.setTexture(&buttonTexture); // Reset texture
    }

    return isOver;
}

bool Button::isClicked(sf::RenderWindow& window) {
    return isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void Button::draw(RenderWindow& window) {
    window.draw(shape);
}

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
            // Update game play logic
                


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