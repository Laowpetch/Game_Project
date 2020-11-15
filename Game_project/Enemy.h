#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"
class Enemy {
public:
	Enemy(sf::Vector2f size) {
		enemy.setSize(size);
		enemy.setFillColor(sf::Color::Red);
	}

	void setPos(sf::Vector2f newPos) {
		enemy.setPosition(newPos);
	}
	void checkColl(Bullet bullet) {
		if (bullet.getRight() > enemy.getPosition().x && 
			bullet.getTop() < enemy.getPosition().y + enemy.getSize().y &&
			bullet.getButtom() > enemy.getPosition().y) {
			enemy.setPosition(sf::Vector2f(4234412, 4234412));
		}
	}
	void draw(sf::RenderWindow& window) {
		window.draw(enemy);
	}
private:
	sf::RectangleShape enemy;
};
