#include <SFML/Graphics.hpp>
#include <iostream>
int main() {
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Game from scratch!", sf::Style::Close | sf::Style :: Resize);
	sf::RectangleShape player(sf::Vector2f(100.0f, 100.0f));
	player.setPosition(206.0f, 206.0f);
	sf::Texture playerTexture;
	playerTexture.loadFromFile("Hull_01.png");
	player.setTexture(&playerTexture);
	while (window.isOpen()) {
		sf::Event evnt;
		while (window.pollEvent(evnt)) {

			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			}
			window.clear();
			window.draw(player);
			window.display();
		}
	}
	return 0;
}