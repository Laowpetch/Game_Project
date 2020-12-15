#include<SFML/Graphics.hpp>
#include<iostream>
#include<math.h>
#include<vector>
#include<stdio.h>
using namespace sf;

//functionprototype;;
void shoot(float, float);
void shot(float, float);
void enemyGenerate(float);
void BE1Checkcollision();

void III();
void IIImove();

class ITEM {
public:
	sf::RectangleShape Item;
	sf::Texture II;
	void set(float x, float y) {
		II.loadFromFile("heart.png");
		Item.setTexture(&II);
		Item.setSize(sf::Vector2f(30.f, 30.f));
		Item.setPosition(x, y);
	}
	sf::Vector2f GetPosition()
	{
		return Item.getPosition();
	}
	FloatRect GetGlobleBounds()
	{
		return Item.getGlobalBounds();
	};

};
ITEM item;

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
	FloatRect GetGlobleBounds() 
	{
		return bullet.getGlobalBounds(); 
	};
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
	FloatRect GetGlobleBounds() 
	{ 
		return enemy1.getGlobalBounds(); 
	};
};
Enemy01 enemy1[10];

//globalvariable;;

int heartItem = 0;

int chk_1[6] = { 0,0,0,0,0,0 };
int pst = 2;
int pst1[6];
int chksup_1[1] = { 0 };
int pst1sup[1];
int enemy1ch[10] = {0,0,0,0,0,0,0,0,0,0};
int enemyRandomStatus;
int bloodc = 4;
clock_t start = -0.2, end = 0;
Clock enemycl;
Clock mainClock;
Clock bloodClock;

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

	//blood;;
	sf::RectangleShape blood;
	blood.setFillColor(sf::Color::Red);
	blood.setPosition(50,25);
	blood.setSize(sf::Vector2f(200,25));
	
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
	
	//gameover
	sf::RectangleShape gameover;
	gameover.setSize(sf::Vector2f(1200, 600));
	sf::Texture overTexture;
	overTexture.loadFromFile("Gameover.jpg");
	gameover.setTexture(&overTexture);
	
	//generalvariables;;
	int animationFrame = 0;
	int fireframe=0;
	float yBorder=50;
	int movement = 0;
	int i = 0;
	int frameNumber=0;
	float ttime;
	float bloodTime;
	int timer;
	int state=0;
	
	//Fontsetting;;
	Font gameFont;
	gameFont.loadFromFile("FrostbiteBossFight-dL0Z.ttf");
	Font headerFont;
	headerFont.loadFromFile("BigSpace-rPKx.ttf");
	Text header;
	Text START;
	Text HIGHSCORE;
	Text EXIT;
	Text NAME;
	Text restart;

	//Header
	header.setFont(headerFont);
	header.setOutlineColor(Color::White);
	header.setOutlineThickness(2);
	header.setFillColor(Color::Black);
	header.setStyle(Text::Italic);
	header.setString("Defending the world");
	header.setCharacterSize(60);
	header.setPosition(100, 75);

	
	//STARTatmenu
	START.setFont(gameFont);
	START.setOutlineColor(Color::Black);
	START.setOutlineThickness(5);
	START.setFillColor(Color::White);
	START.setStyle(Text::Regular);
	START.setString("START");
	START.setCharacterSize(35);
	START.setPosition(100, 275);

	//HIFHGSCOREatmenu
	HIGHSCORE.setFont(gameFont);
	HIGHSCORE.setOutlineColor(Color::Black);
	HIGHSCORE.setOutlineThickness(5);
	HIGHSCORE.setFillColor(Color::White);
	HIGHSCORE.setStyle(Text::Regular);
	HIGHSCORE.setString("HIGHSCORE");
	HIGHSCORE.setCharacterSize(35);
	HIGHSCORE.setPosition(100, 375);
	
	//EXITatmenu
	EXIT.setFont(gameFont);
	EXIT.setOutlineColor(Color::Black);
	EXIT.setOutlineThickness(5);
	EXIT.setFillColor(Color::White);
	EXIT.setStyle(Text::Regular);
	EXIT.setString("EXIT");
	EXIT.setCharacterSize(35);
	EXIT.setPosition(100, 475);
	
	//NAMEatmenu
	NAME.setFont(gameFont);
	NAME.setOutlineColor(Color::White);
	NAME.setOutlineThickness(3);
	NAME.setFillColor(Color::Black);
	NAME.setStyle(Text::Regular);
	NAME.setString("Pachara  Loawpetch  63010629");
	NAME.setCharacterSize(20);
	NAME.setPosition(925, 570);

	//restart at gameover
	restart.setFont(gameFont);
	restart.setFillColor(Color::White);
	restart.setStyle(Text::Regular);
	restart.setString("Please  press  'R'  going  back  to  main  menu");
	restart.setCharacterSize(50);
	restart.setPosition(180, 400);

	//gameloop;;
	while (window.isOpen())
	{	
		//menu;;
		if (state == 0) {


			//menubg;;
			sf::RectangleShape menubg;
			menubg.setSize(sf::Vector2f(1200, 600));
			sf::Texture menuTexture;
			menuTexture.loadFromFile("menubg.jpg");
			menubg.setTexture(&menuTexture);
			window.draw(menubg);

			//menuButton
			Vector2i mouse = Mouse::getPosition(window);


			if (mouse.x > 100 and mouse.x < 172 and mouse.y>284 and mouse.y < 316) {
				START.setFillColor(Color::Blue);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					int enemy1ch[10] = { 0,0,0,0,0,0,0,0,0,0 };
					int chk_1[6] = { 0,0,0,0,0,0 };
					bloodc = 4;
					mainClock.restart();

					state = 1;
				}
			}
			else {
				START.setFillColor(Color::White);
			}

			if (mouse.x > 100 and mouse.x < 249 and mouse.y > 384 and mouse.y < 415) {
				HIGHSCORE.setFillColor(Color::Blue);
			}
			else {
				HIGHSCORE.setFillColor(Color::White);
			}

			if (mouse.x > 100 and mouse.x < 154 and mouse.y > 484 and mouse.y < 515)
			{
				EXIT.setFillColor(Color::Blue);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
				{
					window.close();
				}
			}
			else {
				EXIT.setFillColor(Color::White);
			}
			window.draw(header);
			window.draw(NAME);
			window.draw(START);
			window.draw(HIGHSCORE);
			window.draw(EXIT);
			//windowcommand;;
			window.display();
			window.clear();
		}
		
		//playingstate
		else if (state == 1) {
			int a;

			//randomNumber;;
			srand(time(NULL));
			a = rand();
			a = rand();

			//other;;
			ttime = mainClock.getElapsedTime().asSeconds();
			timer = ttime;
			enemyTime = enemycl.getElapsedTime().asSeconds();
			bloodTime = bloodClock.getElapsedTime().asSeconds();
			movement = 0;
			if (enemyTime > 7.000) {
				enemycl.restart();
			}

			sf::Vector2f pos = playerSprite.getPosition();
			shoot(pos.x, pos.y);
			shot(pos.x, pos.y);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				movement = 2;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				movement = 1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}

			if (movement == 0) {
				playerSprite.setTextureRect(sf::IntRect(0, 0, spriteSizeX, spriteSizeY));
			}
			else if (movement == 2 && yBorder <= 530) {

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
					playerSprite.move(0.f, 2.f);
					fireSprite.move(0.f, 2.f);
					yBorder += 2;
				}
				else {
					playerSprite.move(0.f, 1.f);
					fireSprite.move(0.f, 1.f);
					yBorder += 1;
					playerSprite.setTextureRect(sf::IntRect(spriteSizeX * animationFrame, spriteSizeY * 1, spriteSizeX, spriteSizeY));
				}
				playerSprite.setTextureRect(sf::IntRect(spriteSizeX * animationFrame, spriteSizeY * 1, spriteSizeX, spriteSizeY));
			}
			else if (movement == 1 && yBorder >= 0) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
					playerSprite.move(0.f, -2.f);
					fireSprite.move(0.f, -2.f);
					yBorder -= 2;
				}
				else {
					playerSprite.move(0.f, -1.f);
					fireSprite.move(0.f, -1.f);
					yBorder -= 1;
					playerSprite.setTextureRect(sf::IntRect(spriteSizeX* animationFrame, spriteSizeY * 1, spriteSizeX, spriteSizeY));
				}
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
			window.draw(backgroundSprite);
			window.draw(playerSprite);
			window.draw(fireSprite);
			for (int i = 0; i < 6; i++) {
				if (chk_1[i] == 1) {
					window.draw(bullet[i].bullet);
				}
			}
			//blood
			if (bloodc == 4) {
				blood.setSize(sf::Vector2f(200, 25));
			}
			else if (bloodc == 3) {
				blood.setSize(sf::Vector2f(150, 25));
			}
			else if (bloodc == 2) {
				blood.setSize(sf::Vector2f(100, 25));
			}
			else if (bloodc == 1) {
				blood.setSize(sf::Vector2f(50, 25));
			}

			if (playerSprite.getGlobalBounds().intersects(item.GetGlobleBounds())) {
				heartItem = 0;
				if (bloodc < 4) {
					bloodc++;
				}
			}

			//enemymove;;
			enemyGenerate(enemyTime);
			for (int i = 0; i < 10; i++) {
				float enemyPosition = enemy1[i].enemy1.getPosition().x;
				if (enemyPosition < 0) {
					enemy1ch[i] = 0;
					if (bloodTime > 3) {
						bloodc--;
						bloodClock.restart();
					}
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
					if (ttime > 50) {
						speed = ttime / 100;
					}
					enemy1[i].enemy1.move(-speed, 0);
					enemy1[i].animation(enemyTime);
				}
			}
			BE1Checkcollision();
			III();
			IIImove();
			if (bloodc != 0) {
				window.draw(blood);
			}
			else {
				window.draw(gameover);
				window.draw(restart);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
					state = 0;
				}
			}
			if (bloodc < 0) {
				bloodc = 0;
			}
			if (heartItem == 1) {
				window.draw(item.Item);
			}

			//windowcommands;;
			window.display();
			window.clear();
			frameNumber++;
		}
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
void enemyGenerate(float enemyTime) {
	end = clock();
	float dif = (float)(end - start) / CLOCKS_PER_SEC;
	for (int i = 0; i < 10; i++) {
		if (enemy1ch[i] == 0 && dif > .75) {
			enemy1[i].set(1000, rand() % 500, enemyTime);
			enemy1ch[i] = 1;
			start = clock();
			break;
		}
	}
}
void BE1Checkcollision() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 6; j++)
		{
			if (bullet[j].GetGlobleBounds().intersects(enemy1[i].GetGlobleBounds()))
			{
				chk_1[j] = 0;
				enemy1ch[i] = 0;
				bullet[j].set(-100, 100);
				enemy1[i].set(1300, 700, 1);
			}
		}
	}
}
void III() {
	int a = rand();
	if (heartItem == 0 && a%23 == 0) {
		item.set(1700, rand() % 600);
		heartItem = 1;
	}
}
void IIImove() {
	if (heartItem == 1) {
		item.Item.move(-.3, 0);
	}
	if (item.Item.getPosition().x <= 30) {
		heartItem = 0;
	}
}