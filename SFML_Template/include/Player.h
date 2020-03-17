#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
	sf::RectangleShape render;
	sf::RectangleShape getRenderer();
	void shoot();
	void moveLeft(sf::RectangleShape &shape);
	void moveRight(sf::RectangleShape &shape);


	Player() {
		render.setSize(sf::Vector2f(60.0F, 20.0F));
		render.setOrigin(render.getSize().x / 2.0F, render.getSize().y / 2.0F);
		render.setPosition(800 / 2, 512 - 30);
		render.setFillColor(sf::Color::Red);
	}
};