#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Bullet.h"
#include "Enemy.h"
using namespace sf;
int main() {
	//renderwindow
	sf::RenderWindow window(sf::VideoMode(1200, 600), "Pachara Loawpetch 63010629");
	//bgtexture
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("bg.png"))
	{
		std::cout << "load failed" << std::endl;
	}
	//playertexture
	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("player_plane.png"))
	{
		std::cout << "load failed" << std::endl;
	}
	//firetexture
	sf::Texture fireTexture;
	if (!fireTexture.loadFromFile("fire.png"))
	{
		std::cout << "load failed" << std::endl;
	}
	//bg
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	//player
	sf::Sprite playerSprite;
	playerSprite.setTexture(playerTexture);
	int spriteSizeX = playerTexture.getSize().x/3;
	int spriteSizeY = playerTexture.getSize().y/2;
	playerSprite.setTextureRect(sf::IntRect(0, 0, spriteSizeX, spriteSizeY));
	playerSprite.setPosition(150,50);
	//fire
	sf::Sprite fireSprite;
	fireSprite.setTexture(fireTexture);
	int fspriteSizeX = playerTexture.getSize().x / 4;
	int fspriteSizeY = playerTexture.getSize().y / 1;
	fireSprite.setTextureRect(sf::IntRect(0, 0, fspriteSizeX, fspriteSizeY));
	fireSprite.setPosition(90, 57);
	//generalvariables
	int animationFrame = 0;
	int fireframe=0;
	float yBorder=50;
	int movement = 0;
	int i = 0;
	double xbullet = 225;
	///////////////////////////////////////////
	Enemy enemy(sf::Vector2f(50, 50));
	std::vector<Bullet> bulletVec;
	
	enemy.setPos(sf::Vector2f(500, 50));
	bool isFiring = false;
	//gameloop
	while (window.isOpen())
	{
		movement = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			movement = 2;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			movement = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		{
			i = 1;
		}
		///////////////////
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
			isFiring = true;
		}
		if (movement == 0) {
			playerSprite.setTextureRect(sf::IntRect(0, 0, spriteSizeX, spriteSizeY));
		}
		else if (movement == 2 && yBorder != 530) {
			playerSprite.move(0.f, 1.f);
			fireSprite.move(0.f, 1.f);
			yBorder += 1;
			playerSprite.setTextureRect(sf::IntRect(spriteSizeX * animationFrame, spriteSizeY * 1, spriteSizeX, spriteSizeY));
		}
		else if (movement == 1 && yBorder != 0) {
			playerSprite.move(0.f, -1.f);
			fireSprite.move(0.f, -1.f);
			yBorder -= 1;
			playerSprite.setTextureRect(sf::IntRect(spriteSizeX * animationFrame, 0, spriteSizeX, spriteSizeY));
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
		/////////////////
		if (isFiring == true) {
			Bullet newBullet(sf::Vector2f(50, 5));
			newBullet.setPos(sf::Vector2f(playerSprite.getPosition().x, playerSprite.getPosition().y));
			bulletVec.push_back(newBullet);
			isFiring = false;
		}
		window.draw(backgroundSprite);
		window.draw(playerSprite);
		window.draw(fireSprite);
		enemy.draw(window);
		for (int i = 0; i < bulletVec.size(); i++) {
			bulletVec[i].draw(window);
			bulletVec[i].fire(1);
		}
		for (int i = 0; i < bulletVec.size(); i++) {
			enemy.checkColl(bulletVec[i]);
		}
		window.display();
		window.clear();
	}
	return 0;
}