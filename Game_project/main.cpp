#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include<vector>
using namespace sf;
void shoot(float, float);
void shot(float, float);
sf::Texture* BULLET;
class Bulleted {
public:
	sf::RectangleShape bullet;

	void set(float x, float y)
	{
		bullet.setTexture(BULLET);
		bullet.setSize(sf::Vector2f(30.0f, 30.0f));
		bullet.setPosition(x, y);
	}

	sf::Vector2f GetPosition() { return bullet.getPosition(); }
	//Collider GetCollider() { return Collider(bullet); }
};

Bulleted bullet[6];
int chk_1[6] = { 0,0,0,0,0,0 };
int pst = 2;
int pst1[6];
int chksup_1[1] = { 0 };
int pst1sup[1];
clock_t start = -0.2, end = 0;

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
	int a=0;
	//gameloop
	while (window.isOpen())
	{
		movement = 0;
		sf::Vector2f pos = playerSprite.getPosition();
		shoot(pos.x, pos.y);
		shot(pos.x, pos.y);
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
		///////////////////

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
		window.draw(backgroundSprite);
		window.draw(playerSprite);
		window.draw(fireSprite);
		for (int i = 0; i < 6; i++) {
			if (chk_1[i] == 1) {
				window.draw(bullet[i].bullet);
			}
		}
		window.display();
		window.clear();
		a++;
	}
	return 0;
}
void shoot(float x, float y) {
	end = clock();
	float dif = (float)(end - start) / CLOCKS_PER_SEC;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)&& dif>0.2) {
		for (int i = 0; i < 6; i++) {
			if (chk_1[i] == 0) {
				if (pst == 2) {
					bullet[i].set(x + 60.0f, y + 30.0f);
				}
				pst1[i] = pst;
				chk_1[i] = 1;
				start = clock();
				break;
			}
		}
	}
}
void shot(float x, float y) {
	for (int i = 0; i < 6; i++) {
		if (chk_1[i] == 1) {
			float speed = 3.0f;
			if (pst1[i] == 1) {
				bullet[i].bullet.move(-speed, 0);
			}
			if (pst1[i] == 2) {
				bullet[i].bullet.move(speed, 0);
			}
			if (bullet[i].bullet.getPosition().x > 1200) {
				chk_1[i] = 0;
			}
		}
	}
}