#include "../../Duck Shooting/Header/Controllers/GameController.h"
#include <SFML/Graphics.hpp>


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Duck Game");
    GameController gameController(window);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                gameController.handleMouseClick(mousePos);
            }
        }

        gameController.update(dt);
        gameController.render();

        if (gameController.isGameOver()) {
            window.close();
            //std::cout << "Game Over! Final Score: " << gameController.getPlayerScore() << std::endl;
        }
    }

    return 0;
}
