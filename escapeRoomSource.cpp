#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <numeric> // For std::iota

int main() {
    // Initialize the game window
    sf::RenderWindow window(sf::VideoMode(360, 360), "Nine Grid Game");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }

    // Text for starting the game
    sf::Text startText("Start Game", font, 20);
    startText.setFillColor(sf::Color::White);
    startText.setPosition((window.getSize().x - startText.getGlobalBounds().width) / 2,
        (window.getSize().y / 2) - startText.getGlobalBounds().height - 20);

    // Text for game instructions
    sf::Text instructionsText("Click the grids in the sequence they light up", font, 15);
    instructionsText.setFillColor(sf::Color::White);
    instructionsText.setPosition((window.getSize().x - instructionsText.getGlobalBounds().width) / 2,
        (window.getSize().y / 2) + 20);

    // Text for victory
    sf::Text victoryText("Victory!", font, 20);
    victoryText.setFillColor(sf::Color::Green);
    victoryText.setPosition((window.getSize().x - victoryText.getGlobalBounds().width) / 2,
        window.getSize().y / 2);

    // Grid setup
    const int gridSize = 100;
    const int gridSpacing = 10; // Spacing between grid cells
    sf::RectangleShape grid[3][3];
    std::vector<int> sequence(9); // Store the sequence
    std::iota(sequence.begin(), sequence.end(), 0); // Fill the sequence from 0 to 8
    std::random_shuffle(sequence.begin(), sequence.end()); // Shuffle the sequence

    bool clickedGrid[9] = { false }; // Track if a grid cell has been clicked
    int currentStep = 0; // Current step in the sequence
    bool gameStarted = false; // Has the game started
    bool gameWon = false; // Tracks if the game has been won

    // Calculate the total width and height of the grid
    int totalWidth = 3 * gridSize + 2 * gridSpacing;
    int totalHeight = 3 * gridSize + 2 * gridSpacing;

    // Initialize the grid
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            grid[i][j].setSize(sf::Vector2f(gridSize, gridSize));
            float x = (window.getSize().x - totalWidth) / 2 + i * (gridSize + gridSpacing);
            float y = (window.getSize().y - totalHeight) / 2 + j * (gridSize + gridSpacing);
            grid[i][j].setPosition(x, y);
            grid[i][j].setFillColor(sf::Color::Blue);
            grid[i][j].setOutlineThickness(1.f);
            grid[i][j].setOutlineColor(sf::Color::White);
        }
    }

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                int x = (mousePos.x - (window.getSize().x - totalWidth) / 2) / (gridSize + gridSpacing);
                int y = (mousePos.y - (window.getSize().y - totalHeight) / 2) / (gridSize + gridSpacing);
                int index = y * 3 + x; // Calculate the index of the grid cell clicked

                // Start the game if the "Start Game" text is clicked
                if (!gameStarted && startText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    gameStarted = true;
                    gameWon = false; // Reset the game won flag
                    std::fill(std::begin(clickedGrid), std::end(clickedGrid), false); // Reset the clicked grid tracking
                    // Reset the colors of the grid
                    for (auto& row : grid) {
                        for (auto& cell : row) {
                            cell.setFillColor(sf::Color::Blue);
                            cell.setOutlineColor(sf::Color::White);
                        }
                    }
                    currentStep = 0; // Reset the current step
                    std::random_shuffle(sequence.begin(), sequence.end()); // Shuffle the sequence for a new game
                    grid[sequence[0] / 3][sequence[0] % 3].setOutlineColor(sf::Color::Red); // Highlight the first cell to click
                }
                // Handle the grid cell clicks when the game is started
                else if (gameStarted && x >= 0 && x < 3 && y >= 0 && y < 3) {
                    if (!clickedGrid[index] && index == sequence[currentStep]) {
                        grid[x][y].setFillColor(sf::Color::Red);
                        clickedGrid[index] = true;
                        if (++currentStep == 9) { // Check if the last grid cell in the sequence is clicked
                            gameWon = true; // Set the game as won
                            gameStarted = false; // Reset the game started flag
                        }
                    }
                    else {
                        // Reset the game state without going back to the start screen
                        std::fill(std::begin(clickedGrid), std::end(clickedGrid), false); // Reset the clicked grid tracking
                        // Reset the colors of the grid
                        for (auto& row : grid) {
                            for (auto& cell : row) {
                                cell.setFillColor(sf::Color::Blue);
                                cell.setOutlineColor(sf::Color::White);
                            }
                        }
                        currentStep = 0; // Reset the current step
                        grid[sequence[0] / 3][sequence[0] % 3].setOutlineColor(sf::Color::Red); // Highlight the first cell to click again
                    }
                }
            }
        }

        window.clear(sf::Color::Black); // Clear the window with a black background

        // Draw the appropriate text based on the game state
        if (!gameStarted) {
            if (gameWon) {
                window.draw(victoryText); // Draw the victory text if the game has been won
            }
            else {
                window.draw(startText); // Draw the start text otherwise
                window.draw(instructionsText); // Draw the instructions text
            }
        }
        else {
            // Draw the grid if the game has started
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    window.draw(grid[i][j]);
                }
            }
        }

        window.display(); // Display the contents of the window
    }

    return 0;
}