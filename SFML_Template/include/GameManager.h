#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/Player.h"
#include "../include/Bullet.h"
#include "../include/Properties.h"
#include "../include/Alien.h"
#include "../include/Barrier.h"
#include "../include/DisplayManager.h"

class GameManager {
private:
	int barrier_1_position = 64;
	int barrier_2_position = 192;
	int barrier_3_position = 320;
	int barrier_4_position = 448;

	float const alienDefaultSpeed = 0.5f;
	int const alienDefaultShootChance = 75;

	float alienBaseSpeed = 0.5f;
	float alienSpeedModifier = 150.f; //baseSpeed - (Current dead aliens / alienSpeedMofidier) = actual speed. Higher number = more gradual increase as aliens die.
	int alienShootChance = 75;
	int mothershipSpawnChance = 200;

	bool mothershipActive = false;
	Mothership mothership;

	//The space where aliens and players can exist
	sf::FloatRect gameArea;

	//Object of our properties file
	Properties prop;

	//Create objects of clock to run the game tick for moving aliens and moving bullets
	sf::Clock alienMovementTimer;
	sf::Clock bulletMovementTimer;

	//The player's current score
	int score = 0;
	//The high score since the game was last "powered on". Gotta keep it retro! Plus I'm too lazy to do file reading
	int hiscore = 0;

	//Counter for how many aliens are currently alive
	int livingAliens = 0;

	//Generally we'll never have more than 55 aliens.
	const int maxAliens = 55;

	//Which keys are currently pressed as of last game loop
	bool leftKeyPressed = false;
	bool rightKeyPressed = false;
	bool spaceKeyPressed = false;

	bool moveRight = true;

	//Set to true to force a one second delay in processing. Adds a nice slightly retro "loading" feel when making new games.
	bool forcedPauseDelay = false;

	//Object of the player
	Player player;

	//Need an object of DisplayManager for drawing text
	DisplayManager dispMan;

	bool isGamePaused = false;
	bool isGameOver = false;

public:
	//Create a vector to hold all our lovely aliens
	std::vector<Alien>* alienVector = new std::vector<Alien>;
	//Hold all the bullets that get fired, both player- and alien-owned.
	std::vector<Bullet>* bulletVector = new std::vector<Bullet>;
	//Hold all the chunks of barrier
	std::vector<Barrier>* barrier_vector_1 = new std::vector<Barrier>;
	std::vector<Barrier>* barrier_vector_2 = new std::vector<Barrier>;
	std::vector<Barrier>* barrier_vector_3 = new std::vector<Barrier>;
	std::vector<Barrier>* barrier_vector_4 = new std::vector<Barrier>;

	GameManager(Player &p) : player(p) {
		gameArea = sf::FloatRect(32, 32, 448, 512);
	}

	void drawGameObjects(sf::RenderWindow &window);

	void setupGame(bool playerWin);
	void createBarrier(std::vector<Barrier> &vec, int xPos);
	void newGame(bool playerWin);
	void unpauseGame();
	void gameTick();
	void keyListener(sf::RenderWindow &window);

	void addToScore(int points);

	void addBulletToVector(Bullet bullet);
	bool checkBulletBarrierCollision(Bullet &bullet);

	void movePlayerBullet(Player &player);
	void moveAlienBullet(Player &player);
	void moveAliens(bool &moveRight, sf::FloatRect gameArea);

	bool gamePaused() { return isGamePaused; }
	bool gameOver() { return isGameOver; }
};