#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/window.hpp>
#include <SFML/system.hpp>

class Button {
public:
    Button(float x, float y, float width, float height, sf::Texture& texture, sf::Texture& hoverTexture);

    bool isMouseOver(sf::RenderWindow& window);
    bool isClicked(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

private:
    sf::RectangleShape shape;
    const sf::Texture& buttonTexture;
    const sf::Texture& hoverTexture;
};
