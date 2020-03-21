#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/Player.h"
#include "../include/Alien.h"

//using namespace std;
using namespace std;
extern int xSize = 1000;//224;
extern int ySize = 1000;// 256;

int main()
{
	bool moveRight = true;

	// Create a window with the constructor
	sf::RenderWindow window(sf::VideoMode(xSize, ySize), "Spacey Bois", sf::Style::Default);

	Player player;
	vector<Alien> alienVector;
	Alien alien(sf::Color::Blue, 24, 16);

	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 5; j++) {
			sf::Color col = sf::Color::Magenta;
			if (j == 1) { col = sf::Color::Blue; }
			if (j == 2) { col = sf::Color::Yellow; }
			if (j == 3) { col = sf::Color::Green; }
			if (j == 4) { col = sf::Color::Cyan; }
			alienVector.push_back(Alien(col, i*48 + 8, j*32 + 16));
		}
	}

	sf::RectangleShape playerRender = player.getRenderer();
	sf::RectangleShape bulletRender;

	bulletRender.setSize(sf::Vector2f(4.0F, 20.0F));
	bulletRender.setOrigin(bulletRender.getSize().x / 2.0F, bulletRender.getSize().y / 2.0F);
	bulletRender.setPosition(xSize / 2, ySize - (ySize + bulletRender.getSize().y));
	bulletRender.setFillColor(sf::Color::White);

	window.setPosition(sf::Vector2i(100, 100)); // Set the position of the window to 100,100 relative to the desktop.

	window.setFramerateLimit(60); // Set the limit of the the number of frames per second

	bool bIsLeftPressed  = false;
	bool bIsRightPressed = false;
	bool bIsSpacePressed = false;

	bool moveDown = false;

	int deadAliens = 0;

	sf::Clock timer; // A timer object
	int iCounter = 0; // An interger for counting

					  // Run until the user closes the window
	while (window.isOpen()) {
		if (bulletRender.getPosition().y > 0) {
			bulletRender.move(0, -10);
		}

		sf::FloatRect bulletBoundingBox = bulletRender.getGlobalBounds();

		for (int i = 0; i < alienVector.size(); i++) {
			Alien a = alienVector.at(i);
			sf::RectangleShape alien = a.getRenderer();
			sf::FloatRect alienBoundingBox = alien.getGlobalBounds();

			if (alienBoundingBox.intersects(bulletBoundingBox)) {
				bulletRender.setPosition(-50, -50);
				a.setDead();
				alien.setPosition(-50, -50);
			}

			a.setRenderer(alien);
			alienVector.at(i) = a;
		}

		// check all user events
		sf::Event event;
		while (window.pollEvent(event)) {
			// User has pressed the close button
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			// Process any keypresses
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Left)  bIsLeftPressed  = true;
				if (event.key.code == sf::Keyboard::Right) bIsRightPressed = true;
				if (event.key.code == sf::Keyboard::Space) bIsSpacePressed = true;
			}

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Left)  bIsLeftPressed  = false;
				if (event.key.code == sf::Keyboard::Right) bIsRightPressed = false;
				if (event.key.code == sf::Keyboard::Space) bIsSpacePressed = false;
			}

			if (bIsLeftPressed && !bIsRightPressed) {
				player.move(playerRender, -15);
			}

			if (bIsRightPressed && !bIsLeftPressed) {
				player.move(playerRender, 15);
			}

			if (bIsSpacePressed) {
				if (bulletRender.getPosition().y < 0) {
					bulletRender.setPosition(playerRender.getPosition().x, playerRender.getPosition().y);
					player.shoot();
				}
			}

		}

		// TIme elapsed?
		sf::Time elapsedTime = timer.getElapsedTime(); // How much time has elapsed since last iteration
		cout << "Current aliens: " << deadAliens << endl << " Move by " << (0.5f - (deadAliens / 50.0F)) << endl;
		if (elapsedTime.asSeconds() > (0.5f - (deadAliens/50.0F))) // Has one second passed?
		{
			deadAliens = 0;
			int moveHori = 20;
			int moveVert = 0;
			if (!moveRight) { moveHori = -20; }
			if (moveDown) { moveVert = 50; }

			for (int i = 0; i < alienVector.size(); i++) {
				Alien a = alienVector.at(i);
				sf::RectangleShape alien = a.getRenderer();
				if (!a.isDead()) {
					alien.move(moveHori, moveVert);
					if (alien.getPosition().y > 0) {
						if (alien.getPosition().x > xSize || alien.getPosition().x < 0) {
							cout << "Moving alien down" << alien.getPosition().x << " " << xSize << endl;
							moveRight = !moveRight;
							moveDown = true;
						}
						a.setRenderer(alien);

						alienVector.at(i) = a;
					}
				}
				else {
					cout << "Alien is dead. DONT MOVE!" << endl;
					deadAliens++;
				}
			}

			if (moveVert == 50) {
				moveDown = false;
			}

			cout << iCounter << endl; // print out the counter
			iCounter++; // Increment the counter
			if (iCounter == 100) iCounter = 0; // keep the counter in bounds

			timer.restart(); // Restart the timer
		}

		window.clear();
		for (int i = 0; i < alienVector.size(); i++) {
			if (!alienVector.at(i).isDead()) {
				window.draw(alienVector.at(i).getRenderer());
			}
		}
		window.draw(bulletRender);
		window.draw(playerRender);
		window.display();
	}

	return 0;
}