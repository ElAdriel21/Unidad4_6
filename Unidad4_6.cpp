#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
class ET {
public:
    sf::Sprite sprite;
    sf::Texture etTexture;

    ET() {
        if (etTexture.loadFromFile("et.png")) {
            sprite.setTexture(etTexture);
            sprite.setScale(0.1, 0.1);
            int x = rand() % (1000 - 64);
            int y = rand() % (1000 - 64);
            sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
        }
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "6");

    sf::Texture textureCrosshair;

    sf::Clock clock;
    float elapsedTime = 0.0f;
    float creationInterval = 5.0f;

    int points = 0;
    std::vector<ET> ets;

    textureCrosshair.loadFromFile("crosshair.png");
    sf::Sprite crossHair(textureCrosshair);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                for (auto it = ets.begin(); it != ets.end(); ++it) {
                    if (it->sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        it = ets.erase(it);
                        points += 1;
                        break;
                    }
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();
        elapsedTime += deltaTime;

        if ((elapsedTime >= creationInterval) && (points < 5)) {
            ets.push_back(ET());
            elapsedTime = 0.0f; 
        }

        window.clear();

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        crossHair.setPosition(static_cast<sf::Vector2f>(mousePos) - sf::Vector2f(64, 64));
        window.draw(crossHair);

        for (const ET& et : ets) {
            window.draw(et.sprite);
        }

        window.display();
    }
}