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
void BE1Checkcollision(float);
void III();
void IIImove();

class BBGG {
public:
	sf::RectangleShape bg;
	sf::Texture b;
	void set() {
		b.loadFromFile("bg.jpg");
		bg.setTexture(&b);
		bg.setSize(sf::Vector2f(3600, 600));
		bg.setPosition(0, 0);
	}
	void animation(float animationFrame) {
		int spriteSizeX = bg.getSize().x / 1;
		int spriteSizeY = bg.getSize().y / 1;
		bg.setTextureRect(sf::IntRect(0, 0, spriteSizeX, spriteSizeY));
		bg.setTextureRect(sf::IntRect(spriteSizeX * animationFrame, spriteSizeY * 0, spriteSizeX, spriteSizeY));

	}

};
BBGG background;

class LIFE {
public:
	sf::RectangleShape life;
	sf::Texture ll;
	void set(float x, float y) {
		ll.loadFromFile("life.png");
		life.setTexture(&ll);
		life.setSize(sf::Vector2f(60, 60));
		life.setPosition(x, y);
	}
};
LIFE l1, l2, l3, l4;

class ITEM {
public:
	sf::RectangleShape Item;
	sf::Texture II;
	void set(float x, float y) {
		II.loadFromFile("heart.png");
		Item.setTexture(&II);
		Item.setSize(sf::Vector2f(40.f, 40.f));
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
public:
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
		enemy1.setPosition(x, y);
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
int enemy1ch[10] = { 0,0,0,0,0,0,0,0,0,0 };
int enemyRandomStatus;
int bloodc = 4;
int kanan = 0;
clock_t start = -0.2, end = 0;
Clock enemycl;
Clock mainClock;
Clock bloodClock;
Clock heartclock;
Clock bgclock;

//mainfunction;;
int main() {

	//generalvariable;;
	float enemyTime;

	//renderwindow;;
	sf::RenderWindow window(sf::VideoMode(1200, 600), "Pachara Loawpetch 63010629");

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

	sf::Texture pauseT;
	pauseT.loadFromFile("pause.jpg");
	sf::RectangleShape pausebg;
	pausebg.setSize(sf::Vector2f(1200, 600));
	pausebg.setTexture(&pauseT);

	//player;;
	sf::Sprite playerSprite;
	playerSprite.setTexture(playerTexture);
	int spriteSizeX = playerTexture.getSize().x / 3;
	int spriteSizeY = playerTexture.getSize().y / 2;
	playerSprite.setTextureRect(sf::IntRect(0, 0, spriteSizeX, spriteSizeY));
	playerSprite.setPosition(150, 250);

	//fire;;
	sf::Sprite fireSprite;
	fireSprite.setTexture(fireTexture);
	int fspriteSizeX = playerTexture.getSize().x / 4;
	int fspriteSizeY = playerTexture.getSize().y / 1;
	fireSprite.setTextureRect(sf::IntRect(0, 0, fspriteSizeX, fspriteSizeY));
	fireSprite.setPosition(90, 257);

	//gameover
	sf::RectangleShape gameover;
	gameover.setSize(sf::Vector2f(1200, 600));
	sf::Texture overTexture;
	overTexture.loadFromFile("Gameover.jpg");
	gameover.setTexture(&overTexture);

	//generalvariables;;
	int animationFrame = 0;
	int fireframe = 0;
	float yBorder = 300;
	int movement = 0;
	int i = 0;
	int frameNumber = 0;
	float ttime;
	float bloodTime;
	int timer;
	int state = 1;

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
	Text score;
	Text pauseh;
	Text pauseadv1;
	Text pauseadv2;

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
	restart.setPosition(180, 450);

	//score
	score.setFont(headerFont);
	score.setFillColor(Color::White);
	score.setStyle(Text::Regular);
	score.setCharacterSize(50);
	score.setPosition(1000, 25);

	//pauseh;;
	pauseh.setFont(headerFont);
	pauseh.setFillColor(Color::White);
	pauseh.setStyle(Text::Regular);
	pauseh.setCharacterSize(200);
	pauseh.setString("Pause");
	pauseh.setPosition(350, 50);

	//pauseadv1;;
	pauseadv1.setFont(gameFont);
	pauseadv1.setFillColor(Color::White);
	pauseadv1.setStyle(Text::Regular);
	pauseadv1.setCharacterSize(50);
	pauseadv1.setString("Press C to continue");
	pauseadv1.setPosition(400, 325);

	//pauseadv1;;
	pauseadv2.setFont(gameFont);
	pauseadv2.setFillColor(Color::White);
	pauseadv2.setStyle(Text::Regular);
	pauseadv2.setCharacterSize(25);
	pauseadv2.setString("Press esc to main menu");
	pauseadv2.setPosition(470, 450);

	l1.set(70, 28);
	l2.set(135, 28);
	l3.set(200, 28);
	l4.set(265, 28);

	background.set();

	//gameloop;;
	while (window.isOpen())
	{
		score.setString(std::to_string(kanan));
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
					kanan = 0;
					int enemy1ch[10] = { 0,0,0,0,0,0,0,0,0,0 };
					heartItem = 0;
					int chk_1[6] = { 0,0,0,0,0,0 };
					bloodc = 4;
					mainClock.restart();
					state = 1;
					for (int i = 0; i < 10; i++) {
						enemy1[i].set(1300, 700, 1);
					}
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

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
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
			score.setCharacterSize(50);
			score.setPosition(1000, 25);


			int a;
			float htime;
			float ba;
			//randomNumber;;
			srand(time(NULL));
			a = rand();
			a = rand();


			ba = bgclock.getElapsedTime().asSeconds();
			ttime = mainClock.getElapsedTime().asSeconds();
			timer = ttime;
			enemyTime = enemycl.getElapsedTime().asSeconds();
			bloodTime = bloodClock.getElapsedTime().asSeconds();
			htime = heartclock.getElapsedTime().asSeconds();
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

			if (movement == 0) {
				playerSprite.setTextureRect(sf::IntRect(0, 0, spriteSizeX, spriteSizeY));
			}
			else if (movement == 2 && yBorder <= 530) {

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
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
			else if (movement == 1 && yBorder >= 81) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
					playerSprite.move(0.f, -2.f);
					fireSprite.move(0.f, -2.f);
					yBorder -= 2;
				}
				else {
					playerSprite.move(0.f, -1.f);
					fireSprite.move(0.f, -1.f);
					yBorder -= 1;
					playerSprite.setTextureRect(sf::IntRect(spriteSizeX * animationFrame, spriteSizeY * 1, spriteSizeX, spriteSizeY));
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

			if (ba >= 70) {
				bgclock.restart();
				ba = 0;
			}
			background.animation(ba / 100);
			window.draw(background.bg);


			window.draw(playerSprite);
			window.draw(fireSprite);
			for (int i = 0; i < 6; i++) {
				if (chk_1[i] == 1) {
					window.draw(bullet[i].bullet);
				}
			}

			//blood
			if (playerSprite.getGlobalBounds().intersects(item.GetGlobleBounds()))
			{
				if (bloodc < 4 && htime>3)
				{
					bloodc++;
					heartclock.restart();
				}
				heartItem = 0;
				item.set(1700, 100);
			}

			//enemymove;;
			enemyGenerate(enemyTime);
			for (int i = 0; i < 10; i++) {
				float enemyPosition = enemy1[i].enemy1.getPosition().x;
				if (enemyPosition < 0) {
					enemy1ch[i] = 0;
					enemy1[i].set(1300, 700, 1);
					if (bloodTime > 1) {
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

			window.draw(score);
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
			BE1Checkcollision(bloodTime);
			III();
			IIImove();

			if (bloodc <= 0) {
				state = 2;
			}
			if (bloodc < 0) {
				bloodc = 0;
			}
			if (heartItem == 1) {
				window.draw(item.Item);
			}

			if (bloodc >= 4) {
				window.draw(l4.life);
			}
			if (bloodc >= 3) {
				window.draw(l3.life);
			}
			if (bloodc >= 2) {
				window.draw(l2.life);
			}
			if (bloodc >= 1) {
				window.draw(l1.life);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
				while (1) {
					window.draw(pausebg);
					window.draw(pauseh);
					window.draw(pauseadv1);
					window.draw(pauseadv2);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
						break;
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
						state = 0;
						break;
					}
					window.display();
					window.clear();
				}
			}

			//windowcommands;;
			window.display();
			window.clear();
			frameNumber++;
		}
		else if (state == 2) {
			score.setCharacterSize(100);
			score.setPosition(500, 250);


			window.draw(gameover);
			window.draw(restart);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				state = 0;
			}
			window.draw(score);
			window.display();
			window.clear();
		}
	}
	return 0;
}
void shoot(float x, float y) {
	end = clock();
	float dif = (float)(end - start) / CLOCKS_PER_SEC;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && dif > 0.2) {
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
			enemy1[i].set(1300, (rand() % 419) + 81, enemyTime);
			enemy1ch[i] = 1;
			start = clock();
			break;
		}
	}
}
void BE1Checkcollision(float bloodTime) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 6; j++)
		{
			if (bullet[j].GetGlobleBounds().intersects(enemy1[i].GetGlobleBounds()))
			{
				chk_1[j] = 0;
				enemy1ch[i] = 0;
				bullet[j].set(-100, 100);
				enemy1[i].set(1300, 700, 1);
				kanan += 100;
			}
		}
	}
}
void III() {
	int a = rand();
	if (heartItem == 0 && a % 23 == 0) {
		item.set(1700, (rand() % 419) + 81);
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