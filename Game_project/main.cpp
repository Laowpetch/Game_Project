#include <SFML/Graphics.hpp>
#include <iostream>
int main() {
	sf::RenderWindow window(sf::VideoMode(1200, 600), "Pachara Loawpetch 63010629");
	//////bg
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("bg.png"))
	{
		std::cout << "load failed" << std::endl;
	}
	//////Texture
	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("player_plane.png"))
	{
		std::cout << "load failed" << std::endl;
	}
	//////Fire
	sf::Texture fireTexture;
	if (!fireTexture.loadFromFile("fire.png"))
	{
		std::cout << "load failed" << std::endl;
	}
	//////bg
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	//////Sprite
	sf::Sprite shapeSprite;
	shapeSprite.setTexture(playerTexture);
	int spriteSizeX = playerTexture.getSize().x/3;
	int spriteSizeY = playerTexture.getSize().y/2;
	shapeSprite.setTextureRect(sf::IntRect(0, 0, spriteSizeX, spriteSizeY));
	shapeSprite.setPosition(150,50);
	//////fireSprite
	sf::Sprite fireSprite;
	fireSprite.setTexture(fireTexture);
	int fspriteSizeX = playerTexture.getSize().x / 4;
	int fspriteSizeY = playerTexture.getSize().y / 1;
	fireSprite.setTextureRect(sf::IntRect(0, 0, fspriteSizeX, fspriteSizeY));
	fireSprite.setPosition(90, 57);
	///////statements
	int animationFrame = 0;
	int fireframe=0;
	float yBorder=50;
	while (window.isOpen())
	{
		int movement=0;
		window.draw(backgroundSprite);
		window.draw(shapeSprite);
		window.draw(fireSprite);
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
			else if (movement == 2 && yBorder != 530) {
				shapeSprite.move(0.f, 1.f);
				fireSprite.move(0.f, 1.f);
				yBorder += 1;
				shapeSprite.setTextureRect(sf::IntRect(spriteSizeX * animationFrame, spriteSizeY * 1, spriteSizeX, spriteSizeY));

			}
			else if (movement == 1 && yBorder != 0) {
				shapeSprite.move(0.f, -1.f);
				fireSprite.move(0.f, -1.f);
				yBorder -= 1;
				shapeSprite.setTextureRect(sf::IntRect(spriteSizeX * animationFrame, 0, spriteSizeX, spriteSizeY));
			}
			fireSprite.setTextureRect(sf::IntRect(spriteSizeX * fireframe, 0, fspriteSizeX, fspriteSizeY));
		fireframe++;
		if (fireframe >= 3) {
			fireframe = 0;
		}
		animationFrame++;
		if (animationFrame >= 2) {
			animationFrame = 2;
		}
		window.clear();
	}
	return 0;
}