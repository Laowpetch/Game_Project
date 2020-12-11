#include<SFML/Graphics.hpp>
#include<iostream>
#include<math.h>
#include<vector>
#include<stdio.h>
using namespace sf;
//functionprototype;;
void shoot(float, float);
void shot(float, float);
void enemyFly();
//bulletclass;;
class Bulleted {
public:
	sf::RectangleShape bullet;
	sf::Texture BULLET;
	void set(float x, float y)
	{
		BULLET.loadFromFile("bullet.png");
		bullet.setTexture(&BULLET);
		bullet.setSize(sf::Vector2f(30.0f, 30.0f));
		bullet.setPosition(x, y);
	}
	sf::Vector2f GetPosition() 
	{ 
		return bullet.getPosition(); 
	}
	//Collider GetCollider() { return Collider(bullet); }
};
Bulleted bullet[6];
//enemyclass;;
class Enemy01 {
public :
	sf::RectangleShape enemy1;
	sf::Texture EN1;
	void set(float x, float y, float animationframe)
	{
		int animationFrame = animationframe;
		EN1.loadFromFile("enemy1.png");
		enemy1.setTexture(&EN1);
		int spriteSizeX = EN1.getSize().x / 7;
		int spriteSizeY = EN1.getSize().y / 1;
		enemy1.setTextureRect(sf::IntRect(0, 0, spriteSizeX, spriteSizeY));
		enemy1.setTextureRect(sf::IntRect(spriteSizeX * animationFrame, spriteSizeY * 0, spriteSizeX, spriteSizeY));
		enemy1.setSize(sf::Vector2f(60.f, 60.f));
		enemy1.setPosition(x,y);
	}
	void animation(float animationframe) {
		int animationFrame = animationframe;
		int spriteSizeX = EN1.getSize().x / 7;
		int spriteSizeY = EN1.getSize().y / 1;
		enemy1.setTextureRect(sf::IntRect(0, 0, spriteSizeX, spriteSizeY));
		enemy1.setTextureRect(sf::IntRect(spriteSizeX * animationFrame, spriteSizeY * 0, spriteSizeX, spriteSizeY));

	}
	sf::Vector2f GetPosition()
	{
		return enemy1.getPosition();
	}
};
Enemy01 enemy1[10];
//globalvariable;;
int chk_1[6] = { 0,0,0,0,0,0 };
int pst = 2;
int pst1[6];
int chksup_1[1] = { 0 };
int pst1sup[1];
int enemy1ch[10] = {0,0,0,0,0,0,0,0,0,0};
int enemyRandomStatus;
clock_t start = -0.2, end = 0;
Clock enemycl;
Clock mainClock;
//mainfunction;;
int main() {
	//generalvariable;;
	float enemyTime;
	//renderwindow;;
	sf::RenderWindow window(sf::VideoMode(1200, 600), "Pachara Loawpetch 63010629");
	//bgtexture;;
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("bg.png"))
	{
		std::cout << "load failed" << std::endl;
	}
	//playertexture;;
	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("player_plane.png"))
	{
		std::cout << "load failed" << std::endl;
	}
	//firetexture;;
	sf::Texture fireTexture;
	if (!fireTexture.loadFromFile("fire.png"))
	{
		std::cout << "load failed" << std::endl;
	}
	//bg;;
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	//player;;
	sf::Sprite playerSprite;
	playerSprite.setTexture(playerTexture);
	int spriteSizeX = playerTexture.getSize().x/3;
	int spriteSizeY = playerTexture.getSize().y/2;
	playerSprite.setTextureRect(sf::IntRect(0, 0, spriteSizeX, spriteSizeY));
	playerSprite.setPosition(150,50);
	//fire;;
	sf::Sprite fireSprite;
	fireSprite.setTexture(fireTexture);
	int fspriteSizeX = playerTexture.getSize().x / 4;
	int fspriteSizeY = playerTexture.getSize().y / 1;
	fireSprite.setTextureRect(sf::IntRect(0, 0, fspriteSizeX, fspriteSizeY));
	fireSprite.setPosition(90, 57);
	//generalvariables;;
	int animationFrame = 0;
	int fireframe=0;
	float yBorder=50;
	int movement = 0;
	int i = 0;
	int frameNumber=0;
	float ttime;
	int timer;
	//generalCommands
	//printf("%d\n", frameNumber);
	//gameloop;;
	while (window.isOpen())
	{
		//randomNumber;;
		srand(time(NULL));
		//other;;
		ttime = mainClock.getElapsedTime().asSeconds();
		timer = ttime;
		enemyTime = enemycl.getElapsedTime().asSeconds();
		movement = 0;
		if (enemyTime > 7.000) {
			enemycl.restart();
		}
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
		///////////////////;;
		if (movement == 0) {
			playerSprite.setTextureRect(sf::IntRect(0, 0, spriteSizeX, spriteSizeY));
		}
		else if (movement == 2 && yBorder <= 530) {
			playerSprite.move(0.f, 3.f);
			fireSprite.move(0.f, 3.f);
			yBorder += 3;
			playerSprite.setTextureRect(sf::IntRect(spriteSizeX * animationFrame, spriteSizeY * 1, spriteSizeX, spriteSizeY));
		}
		else if (movement == 1 && yBorder >= 0) {
			playerSprite.move(0.f, -3.f);
			fireSprite.move(0.f, -3.f);
			yBorder -= 3;
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
		/////////////////;;
		window.draw(backgroundSprite);
		window.draw(playerSprite);
		window.draw(fireSprite);
		for (int i = 0; i < 6; i++) {
			if (chk_1[i] == 1) {
				window.draw(bullet[i].bullet);
			}
		}
		//enemymove;;
		for (int i = 0; i < 10; i++) {
			if (enemy1ch[i] == 0 && frameNumber%500==0) {
				enemy1[i].set(1000, rand()%600, enemyTime);
				enemy1ch[i] = 1;
				break;
			}
		}
		for (int i = 0; i < 10; i++) {
			float enemyPosition = enemy1[i].enemy1.getPosition().x;
			if (enemyPosition < 0) {
				enemy1ch[i] = 0;
			}
		}
		for (int i = 0; i <= 10; i++) {
			if (enemy1ch[i] == 1) {
				window.draw(enemy1[i].enemy1);
			}
		}
		for (int i = 0; i < 10; i++) {
			if (enemy1ch[i] == 1) {
				float speed = .5f;
				enemy1[i].enemy1.move(-speed, 0);
				enemy1[i].animation(enemyTime);
				}
		}
		void enemyFly();
		//windowcommands;;
		window.display();
		window.clear();
		frameNumber++;
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