#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <optional>
#include <string>

int main() {
    // --- Step 0.6: window ---
    sf::RenderWindow window(sf::VideoMode({1280u, 720u}), "Suika Versus");
    window.setFramerateLimit(60);

    // --- Step 0.7: font with fallback ---
    const std::array<std::string, 2> fontPaths = {
        "assets/fonts/font.ttf",
        "C:/Windows/Fonts/arial.ttf"
    };

    sf::Font font;
    std::string loadedPath;
    for (const auto& path : fontPaths) {
        if (font.openFromFile(path)) {
            loadedPath = path;
            break;
        }
    }
    if (loadedPath.empty()) {
        std::cerr << "No font found\n";
        return 1;
    }

    // SFML 3: sf::Text requires the font in the constructor    
    sf::Text text(font, "Suika Versus\nFont: " + loadedPath, 28);
    text.setFillColor(sf::Color::White);
    text.setPosition({20.f, 20.f});

    sf::CircleShape circle(60.f);
    circle.setOrigin({60.f, 60.f});            // center instead of top-left
    circle.setPosition({640.f, 360.f});
    circle.setFillColor(sf::Color(230, 60, 60));

    while (window.isOpen()) {
        // SFML 3: events are std::optional<sf::Event>, queried by type
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color(30, 30, 40));
        window.draw(circle);
        window.draw(text);
        window.display();
    }
    return 0;
}