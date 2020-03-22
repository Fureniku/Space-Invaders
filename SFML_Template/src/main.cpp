#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/Player.h"
#include "../include/Bullet.h"
#include "../include/Properties.h"
#include "../include/Alien.h"

using std::cout;
using std::endl;

void moveBullets(bool &playerBulletActive, sf::Sprite playerSprite, float scale);
void moveAliens(sf::Clock timer, int &leftPos, int &rightPos, bool &moveRight, float scale);

//Create a vector to hold all our lovely aliens
std::vector<Alien>* alienVector = new std::vector<Alien>();
//Hold all the bullets that get fired, both player- and alien-owned.
std::vector<Bullet>* bulletVector = new std::vector<Bullet>;

//Create object of properties file
Properties prop;

int main() {
	//Get scale as a variable as we use it a lot and I don't want to write prop.getScale() 500 times.
	float scale = prop.getScale();

	//Create object of the player
	Player player;
	//And the object that physicaly draws the player
	sf::Sprite playerSprite = player.getRenderer();

	// Create a window with the constructor
	sf::RenderWindow window(sf::VideoMode(prop.getWindowXSize(), prop.getWindowYSize()), "The Invaders from Space", sf::Style::Default);

	//Place the game window in the middle of the screen (screen width/2 - window size/2, same for height)
	window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width / 2) - (prop.getWindowXSize() / 2), (sf::VideoMode::getDesktopMode().height / 2) - (prop.getWindowYSize() / 2)));

	window.setFramerateLimit(60000); // Set the limit of the the number of frames per second

	//Create an object of clock to run the game tick for moving aliens
	sf::Clock timer;

	//Create all our aliens - 5 rows of 11 aliens
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 5; j++) {
			sf::Color col = sf::Color::Magenta;
			std::string texture = "Alien_1_";
			if (j == 1) {
				col = sf::Color::Blue;
			}
			if (j == 2) {
				col = sf::Color::Yellow;
				texture = "Alien_2_";
			}
			if (j == 3) {
				col = sf::Color::Green;
				texture = "Alien_2_";
			}
			if (j == 4) {
				col = sf::Color::Cyan;
				texture = "Alien_3_";
			}
			//Add this alien to the vector, setting its colour, and starting x/y position
			alienVector->push_back(Alien(col, (i*32)*scale + (32*scale), (j*32)*scale + (96*scale), texture, scale));
		}
	}

	//Whether aliens should be moving to the right, or to the left. Inverted each time they reach the edge of the screen.
	bool moveRight = true;
	//The left-most and right-most alien positions, used for vertical movement
	int leftPos = 0;
	int rightPos = 0;

	//Which keys are currently pressed as of last game loop
	bool bIsLeftPressed  = false;
	bool bIsRightPressed = false;
	bool bIsSpacePressed = false;

	//Set true when the player fires, and back to false when the bullet goes off-screen or hits something. 
	bool playerBulletActive = false;

	//Run until the user closes the window
	while (window.isOpen()) {
		// check all user events
		sf::Event event;
		//Check the event things before we do anything else
		while (window.pollEvent(event)) {
			// User has pressed the close button
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			//Check for left/right/space press
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Left)  bIsLeftPressed  = true;
				if (event.key.code == sf::Keyboard::Right) bIsRightPressed = true;
				if (event.key.code == sf::Keyboard::Space) bIsSpacePressed = true;
			}

			//Check for release
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Left)  bIsLeftPressed  = false;
				if (event.key.code == sf::Keyboard::Right) bIsRightPressed = false;
				if (event.key.code == sf::Keyboard::Space) bIsSpacePressed = false;
			}

			//Only move left or right if one is pressed *and* the other is NOT pressed.
			if (bIsLeftPressed && !bIsRightPressed) {
				player.move(playerSprite, -15);
			}

			if (bIsRightPressed && !bIsLeftPressed) {
				player.move(playerSprite, 15);
			}

			if (bIsSpacePressed) {
				//Check there isn't already an active bullet, players can only fire one at a time.
				if (!playerBulletActive) {
					//Add a new bullet object owned by the player to the bullet vector
					bulletVector->push_back(Bullet(true, playerSprite.getPosition().x, playerSprite.getPosition().y, scale));
					playerBulletActive = true;
				}
			}
		}

		//Move any currently existing bullets
		moveBullets(playerBulletActive, playerSprite, scale);

		//Move the aliens
		moveAliens(timer, leftPos, rightPos, moveRight, scale);

		window.clear();
		for (int i = 0; i < alienVector->size(); i++) {
			//Draw all aliens
			window.draw(alienVector->at(i).getRenderer());
		}

		for (int i = 0; i < bulletVector->size(); i++) {
			//Draw all bullets
			window.draw(bulletVector->at(i).getRenderer());
		}

		window.draw(playerSprite);
		window.display();
	}

	return 0;
}

void moveBullets(bool &playerBulletActive, sf::Sprite playerSprite, float scale) {
	//Iterate through all registered bullets
	for (int i = 0; i < bulletVector->size(); i++) {
		Bullet b = bulletVector->at(i);
		sf::RectangleShape bullet = b.getRenderer();
		b.move(bullet, -10*scale);

		b.setRenderer(bullet);
		bulletVector->at(i) = b;

		//Get the bullets bounding box
		sf::FloatRect bulletBoundingBox = bullet.getGlobalBounds();

		//Did a player fire this bullet?
		if (b.isPlayerOwned) {
			if (bullet.getPosition().y < 0) {
				//It's off screen, remove the bullet from the vector and let the player shoot again.
				bulletVector->erase(bulletVector->begin() + i);
				i--;
				playerBulletActive = false;
				return;
			} else {
				//THE LAGGY BIT!
				//Check each alien to see if they were shot by this bullet.
				for (int j = 0; j < alienVector->size(); j++) {
					Alien a = alienVector->at(j);
					sf::Sprite alien = a.getRenderer();
					sf::FloatRect alienBoundingBox = alien.getGlobalBounds();

					if (alienBoundingBox.intersects(bulletBoundingBox)) {
						//If they were shot, remove the alien and bullet from their respective vectors.
						alienVector->erase(alienVector->begin() + j);
						bulletVector->erase(bulletVector->begin() + i);
						j--; i--;
						playerBulletActive = false;
						return;
					}
				}
			}
		} else {
			//handle alien bullets
			if (bullet.getPosition().y > prop.getWindowYSize()) {
				//It's off screen, remove the bullet from the vector
				bulletVector->erase(bulletVector->begin() + i);
				i--;
			} else {
				sf::FloatRect playerBoundingBox = playerSprite.getGlobalBounds();
				if (bulletBoundingBox.intersects(playerBoundingBox)) {
					//TODO kill player
					bulletVector->erase(bulletVector->begin() + i);
					i--;
				}
			}
		}
	}
}

void moveAliens(sf::Clock timer, int &leftPos, int &rightPos, bool &moveRight, float scale) {
	sf::Time elapsedTime = timer.getElapsedTime(); // How much time has elapsed since last iteration
		//cout << "Current aliens: " << deadAliens << endl << " Move by " << (0.5f - (deadAliens / 50.0F)) << endl;
	if (elapsedTime.asSeconds() > (0.5f - ((55 - alienVector->size()) / 50.0F))) {
		cout << "Move tick. Move right: " << moveRight << " Total aliens: " << alienVector->size() << endl;
		int moveVertical = 0;

		//If the aliens at the edge of the screen, and are still set to move in that direction...
		if ((leftPos - (24 * scale) < 0 && !moveRight) || (rightPos + (24 * scale) > prop.getWindowXSize() && moveRight)) {
			//Set the amount to move by vertically
			moveVertical = 20 * scale;
			//Invert the direction of travel
			moveRight = !moveRight;
		}

		//Movement pass - actually move all aliens based on the results of check pass
		for (int i = 0; i < alienVector->size(); i++) {
			//Get the alien from the vector
			Alien a = alienVector->at(i);
			//Get the sprite of said alien
			sf::Sprite alien = a.getRenderer();

			int x = alien.getPosition().x;

			if (i == 0) {
				leftPos = x;
				rightPos = x;
			}
			else {
				if (x < leftPos) {
					leftPos = x;
				}
				if (x > rightPos) {
					rightPos = x;
				}
			}

			a.move(alien, moveRight, 5 * scale, moveVertical);

			//"Save our changes".
			a.toggleType();
			a.setRenderer(alien);
			alienVector->at(i) = a;
		}

		timer.restart(); // Restart the timer
	}
}