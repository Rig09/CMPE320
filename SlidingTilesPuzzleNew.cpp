#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class SlidingPuzzle {
public:
    SlidingPuzzle() : app(VideoMode(256, 256), "15-Puzzle!") {
        app.setFramerateLimit(60);
        t.loadFromFile("C:/Users/dtq51/images/15.png");
        initialize();
    }

    void run() {
    while (app.isOpen()) {
        handleEvents();
        if (update()) {
            std::cout << "Congratulations! Puzzle solved!\n";
            app.close();  // Close the window when the puzzle is solved
        }
        draw();
    }
}

private:
    RenderWindow app;
    Texture t;
    int w;
    int grid[6][6];
    Sprite sprite[20];

    void initialize() {
        w = 64;

        int initialOrder[] = { 12, 1, 2, 4, 11, 6, 7, 15, 14, 10, 8, 5, 3, 13, 0, 9 };
        int index = 0;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int n = initialOrder[index++];
                if (n == 0) {
                    // Set the empty tile
                    grid[i + 1][j + 1] = 16;
                }
                else {
                    sprite[n].setTexture(t);
                    sprite[n].setTextureRect(IntRect((n - 1) % 4 * w, (n - 1) / 4 * w, w, w));
                    grid[i + 1][j + 1] = n;
                }
            }
        }
    }




    void handleEvents() {
        Event e;
        while (app.pollEvent(e)) {
            if (e.type == Event::Closed)
                app.close();

            if (e.type == Event::MouseButtonPressed)
                if (e.key.code == Mouse::Left) {
                    Vector2i pos = Mouse::getPosition(app);
                    int x = pos.x / w + 1;
                    int y = pos.y / w + 1;

                    int dx = 0;
                    int dy = 0;

                    if (grid[x + 1][y] == 16) {
                        dx = 1;
                        dy = 0;
                    }
                    if (grid[x][y + 1] == 16) {
                        dx = 0;
                        dy = 1;
                    }
                    if (grid[x][y - 1] == 16) {
                        dx = 0;
                        dy = -1;
                    }
                    if (grid[x - 1][y] == 16) {
                        dx = -1;
                        dy = 0;
                    }

                    int n = grid[x][y];
                    grid[x][y] = 16;
                    grid[x + dx][y + dy] = n;

                    // Animation
                    sprite[16].move(-dx * w, -dy * w);
                    float speed = 3;

                    for (int i = 0; i < w; i += speed) {
                        sprite[n].move(speed * dx, speed * dy);
                        app.draw(sprite[16]);
                        app.draw(sprite[n]);
                        app.display();
                    }
                }
        }
    }

    bool update() {
        app.clear(Color::White);
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++) {
                int n = grid[i + 1][j + 1];
                sprite[n].setPosition(i * w, j * w);
                app.draw(sprite[n]);
            }

        app.display();

        // Check for puzzle completion
        int correctOrder[] = { 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 0 };
        int ind = 0;

        for (int i = 0; i <= 4; ++i) {
            for (int j = 0; j <= 4; ++j) {
                int n = correctOrder[ind++];
                if (grid[i + 1][j + 1] != n)  {
                    return false;
                }
            }
        }
        return true;
    }


    void draw() {
        // Drawing logic (if needed)
    }
};

int main() {
    SlidingPuzzle slidingPuzzle;
    slidingPuzzle.run();

    return 0;
}
