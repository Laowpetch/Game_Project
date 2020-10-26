#include <SFML/Graphics.hpp>
#include <iostream>
int main() {
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Game from scratch!");

	//////circle

	sf::CircleShape collision(100.f);
	collision.setPosition({ 200.f,200.f });
	collision.setFillColor(sf::Color::Red);

	//////Texture
	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("player_plane.png"))
	{
		std::cout << "load failed" << std::endl;
	}

	//////Sprite

	sf::Sprite shapeSprite;
	shapeSprite.setTexture(playerTexture);

	int spriteSizeX = playerTexture.getSize().x/3;
	int spriteSizeY = playerTexture.getSize().y/2;

	shapeSprite.setTextureRect(sf::IntRect(0, 0, spriteSizeX, spriteSizeY));
	shapeSprite.setPosition(150,50);

	int animationFrame = 0;

	while (window.isOpen())
	{
		int movement=0;
		window.draw(shapeSprite);
		window.draw(collision);
		window.display();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
		{
			movement = 2;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			movement = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
		if (movement == 0) {
			shapeSprite.setTextureRect(sf::IntRect(0, 0, spriteSizeX, spriteSizeY));
		}
		else if (movement == 2) {
			shapeSprite.move(0.f, 1.f);
			shapeSprite.setTextureRect(sf::IntRect(spriteSizeX * animationFrame, spriteSizeY * 1, spriteSizeX, spriteSizeY));
		}
		else if (movement == 1) {
			shapeSprite.move(0.f, -1.f);
			shapeSprite.setTextureRect(sf::IntRect(spriteSizeX * animationFrame, 0, spriteSizeX, spriteSizeY));
		}
		animationFrame++;
		if (animationFrame >= 2) {
			animationFrame = 2;
		}
		window.clear();
	}
	return 0;
}