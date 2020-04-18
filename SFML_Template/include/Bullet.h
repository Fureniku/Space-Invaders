#pragma once
#include <SFML/Graphics.hpp>

class Bullet {
public:
	sf::RectangleShape render;
	//True for if a player fired it, false for an alien.
	bool isPlayerOwned;

	Bullet() {}

	Bullet(bool playerOwned, int startX, int startY) {
		render.setSize(sf::Vector2f(2.0F, 10.0F));
		render.setOrigin(render.getSize().x / 2.0F, render.getSize().y / 2.0F);
		render.setPosition(startX, startY);
		render.setFillColor(sf::Color::White);

		isPlayerOwned = playerOwned;
	}

	sf::RectangleShape getSprite(); //Technically not a sprite but lets keep consistency with other similar functions.
	void setSprite(sf::RectangleShape shape);
	void move(sf::RectangleShape &shape, int amount);
};