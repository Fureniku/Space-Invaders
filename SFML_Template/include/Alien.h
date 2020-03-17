#pragma once
#include <SFML/Graphics.hpp>

class Alien {
public:
	sf::RectangleShape render;
	bool dead = false;

	Alien(sf::Color col, int startX, int startY) {
		render.setSize(sf::Vector2f(24.0F, 16.0F));
		render.setOrigin(render.getSize().x / 2.0F, render.getSize().y / 2.0F);
		render.setPosition(startX, startY);
		render.setFillColor(col);
	}

	sf::RectangleShape getRenderer();
	void move(sf::RectangleShape shape, int moveX, int moveY);
	void setRenderer(sf::RectangleShape shape);
	void setDead();
	bool isDead();
};