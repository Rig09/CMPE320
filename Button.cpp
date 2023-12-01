#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Texture& texture, sf::Texture& hoverTexture) :
    buttonTexture(texture), hoverTexture(hoverTexture) {
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));
    shape.setTexture(&buttonTexture);
}

bool Button::isMouseOver(sf::RenderWindow& window) {
    sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
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

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
}