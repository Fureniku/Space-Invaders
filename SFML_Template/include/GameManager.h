#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/Player.h"
#include "../include/Bullet.h"
#include "../include/Alien.h"
#include "../include/Barrier.h"
#include "../include/DisplayManager.h"

class GameManager {
private:
	//The central position of the four barriers. Also used for some other screen objects (such as the score) to keep things aligned.
	int barrier_1_position = 64;
	int barrier_2_position = 192;
	int barrier_3_position = 320;
	int barrier_4_position = 448;

	//The amount of pixels the bullets should move each time they move
	const int playerBulletSpeed = 15;
	const int alienBulletSpeed = 10;

	//default values, kept here to restore back to later when we make new games
	const float alienDefaultSpeed = 0.5f;
	const float alienDefaultModifier = 70.f;
	const int alienDefaultShootChance = 75;

	//Variables which can be changed to increase difficulty over time.
	float alienBaseSpeed = 0.5f;
	float alienSpeedModifier = 70.f; 
	int alienShootChance = 75;

	//Mothership has a 1 in 200 chance to spawn each frame, so long as cooldown is still zero.
	int mothershipSpawnChance = 200;
	int mothershipCooldown = 0;

	//The ID of the next sound that should be played when an alien moves
	int moveSfxId = 0;

	//Whether sounds should play. Set to false to mute the whole game.
	bool playSFX = true;

	bool mothershipActive = false;
	//Create an empty Mothership object, we'll assign an object to it when the ship is created, and set it back to empty when destroyed.
	Mothership mothership;

	//The space where aliens and players can exist
	sf::FloatRect gameArea;

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

	//Whether the aliens should collectively move to the right
	bool moveRight = true;

	//The current size of the game window, passed from main
	int xSize;
	int ySize;

	//Object of the player
	Player player;

	//Need an object of DisplayManager for drawing text
	DisplayManager dispMan;

	//Set to true for their relevant modes.
	bool isGamePaused = false;
	bool isGameOver = false;

	//We need an instance of the alien's death sound in here, for the last alien as well as the mothership.
	sf::SoundBuffer buffer_dead;
	sf::Sound sfx_dead;

	//An array of sounds, for the aliens movement.
	sf::SoundBuffer buffer_move[4];
	sf::Sound sfx_move;

public:
	//Create a vector to hold all our lovely aliens
	std::vector<Alien>* alienVector = new std::vector<Alien>;
	//Hold all the bullets that get fired, both player- and alien-owned.
	std::vector<Bullet>* bulletVector = new std::vector<Bullet>;
	//Hold all the chunks of barrier. We have a vector for each barrier to reduce the amount of processing time to check for collisions.
	std::vector<Barrier>* barrier_vector_1 = new std::vector<Barrier>;
	std::vector<Barrier>* barrier_vector_2 = new std::vector<Barrier>;
	std::vector<Barrier>* barrier_vector_3 = new std::vector<Barrier>;
	std::vector<Barrier>* barrier_vector_4 = new std::vector<Barrier>;

	GameManager(Player &p, int screenSizeX, int screenSizeY) : player(p), dispMan(screenSizeX, screenSizeY) {
		gameArea = sf::FloatRect(32, 32, 448, 512);
		xSize = screenSizeX;
		ySize = screenSizeY;

		buffer_dead.loadFromFile(".\\assets\\sounds\\invaderkilled.wav");
		for (int i = 0; i < 4; i++) {
			buffer_move[i].loadFromFile(".\\assets\\sounds\\fastinvader" + std::to_string(i) + ".wav");
		}
	}

	void drawGameObjects(sf::RenderWindow &window);

	void setupGame(bool playerWin);
	void createBarrier(std::vector<Barrier> &vec, int xPos);
	void newGame(bool playerWin);
	void unpauseGame();
	void gameTick();
	void eventHandler(sf::RenderWindow &window);

	void addToScore(int points);

	void addBulletToVector(Bullet bullet);
	bool checkBulletBarrierCollision(Bullet &bullet);

	void movePlayerBullet(Player &player);
	void moveAlienBullet(Player &player);
	void moveAliens(bool &moveRight, sf::FloatRect gameArea);
	void toggleSound();

	bool isMothershipActive() { return mothershipActive; }
	bool gamePaused() { return isGamePaused; }
	bool gameOver() { return isGameOver; }
	bool playSound() { return playSFX; }
	
};