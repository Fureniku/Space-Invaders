#include <string>
#include "../include/GameManager.h"

void GameManager::setupGame(bool playerWin) {
	//Create all our aliens - 5 rows of 11 aliens
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 5; j++) {
			sf::Color col = sf::Color::Magenta;
			std::string texture = "Alien_1_";
			int pointValue = 30;
			//Set some properties depending on the row of aliens
			if (j == 1) {
				col = sf::Color::Blue;
			}
			if (j == 2) {
				col = sf::Color::Yellow;
				texture = "Alien_2_";
				pointValue = 20;
			}
			if (j == 3) {
				col = sf::Color::Green;
				texture = "Alien_2_";
				pointValue = 20;
			}
			if (j == 4) {
				col = sf::Color::Cyan;
				texture = "Alien_3_";
				pointValue = 10;
			}
			//Add this alien to the vector, setting its colour, and starting x/y position
			alienVector->push_back(Alien(col, (i * 32) + 32, (j * 32) + 94, texture, pointValue));
		}
	}
	if (!playerWin) {
		createBarrier(*barrier_vector_1, barrier_1_position);
		createBarrier(*barrier_vector_2, barrier_2_position);
		createBarrier(*barrier_vector_3, barrier_3_position);
		createBarrier(*barrier_vector_4, barrier_4_position);
	}
}

//Start a new game, either as a winner (cleared all aliens) or loser (lost all lives).
void GameManager::newGame(bool playerWin) {
	isGameOver = false; //Set back to false if this came from a loss

	moveRight = true; //Ensure aliens will move right again, as they start on the left of screen.
	
	//Clear all our vectors, then re-initialize them to ensure a clean slate
	alienVector->clear();
	bulletVector->clear();

	//If the player won that round, we'll give them a bonus life - but cap it at 5.
	if (playerWin && player.getLives() < 5) {
		player.addLives(1);

		//Each time the player has a consecutive win, the game gets a bit harder. After 10 wins its basically impossible :) 
		alienBaseSpeed -= 0.05f;
		alienSpeedModifier -= 0.04f; //By the fifth consecutive win, aliens will move at "max speed" when 5 or less remain.
		alienShootChance -= 5;
	}
	else {
		//The player lost, so set score to zero. They can only lose if their lives hit zero, so give them three fresh lives.
		score = 0;
		player.addLives(3);
		player.resetPosition();
		barrier_vector_1->clear();
		barrier_vector_2->clear();
		barrier_vector_3->clear();
		barrier_vector_4->clear();

		//Set the difficulty modifiers back to the originals
		alienBaseSpeed = alienDefaultSpeed;
		alienSpeedModifier = alienDefaultModifier;
		alienShootChance = alienDefaultShootChance;

		//If the player happened to be holding a key when they lose, it doesn't get correctly reset due to the new screen popping up.
		leftKeyPressed = false;
		rightKeyPressed = false;
		spaceKeyPressed = false;
	}

	setupGame(playerWin);
}

void GameManager::unpauseGame() {
	isGamePaused = false;
}

//Called every frame - the function that does basically everything!
void GameManager::gameTick() {
	if (score > hiscore) {
		//If the current score is better than high score, set the high score to current score.
		hiscore = score;
	}

	//Game over, the player is out of lives!
	if (player.getLives() <= 0) {
		//Remove the mothership, if it was there when we died. Do this before the gameover screen, else it'll play its SFX forever.
		mothership.toggleSFX(false);
		mothership = Mothership();
		mothershipCooldown = 500;
		mothershipActive = false;

		isGameOver = true;
	}

	//Attempt to spawn a mothership
	if (!mothershipActive) {
		if (mothershipCooldown > 0) {
			mothershipCooldown--;
		} else if (rand() % mothershipSpawnChance == 1) {
			mothership = Mothership(xSize + 40, 75);
			if (playSound()) {
				mothership.toggleSFX(true);
			}
			mothershipActive = true;
		}
	}
	else {
		//Handle an existing mothership
		mothership.move();
		if (mothership.getSprite().getPosition().x < -10) {
			if (playSound()) {
				mothership.toggleSFX(false);
			}
			mothershipCooldown = 500;
			mothershipActive = false;
		}
	}

	//Move bullets every 0.05 seconds
	if (bulletMovementTimer.getElapsedTime().asSeconds() > 0.05f) {
		movePlayerBullet(player);
		moveAlienBullet(player);
		bulletMovementTimer.restart();
	}

	//Handle the speed of the aliens movement. Aliens will speed up when less of them exist, and will also be generally faster for every consecutively won round.
	int deadAliens = maxAliens - livingAliens;
	if (alienMovementTimer.getElapsedTime().asSeconds() > (alienBaseSpeed - ((deadAliens / 100.f) * (deadAliens / alienSpeedModifier)))) {
		//Move the aliens
		moveAliens(moveRight, gameArea);
		alienMovementTimer.restart();
	}

	//Reset our known living alien number to zero before re-counting them
	livingAliens = 0;

	for (int i = 0; i < alienVector->size(); i++) {
		if (!alienVector->at(i).isDead()) {
			livingAliens++;
		}
	}

	if (livingAliens == 0) {
		//The last alien is removed, and as such there's no alien object left to play its death sound
		//So, fallback to the death sound used for the mothership as a workaround.
		sfx_dead.setBuffer(buffer_dead);
		sfx_dead.play();
		newGame(true);
	}
}

void GameManager::eventHandler(sf::RenderWindow &window) {
	// check all user events
	sf::Event event;
	while (window.pollEvent(event)) {
		// User has pressed the close button
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		//Check for left/right/space press
		if (event.type == sf::Event::KeyPressed) {
			//Toggle left bool for left/A key press
			if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
				leftKeyPressed = true;
			}
			//Toggle right bool for right/D key press
			if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
				rightKeyPressed = true;
			}
			//Fire when player presses space
			if (event.key.code == sf::Keyboard::Space) {
				spaceKeyPressed = true;
			}
			//Pause the game when player presses escape - will stop gameTick from being called and show an alternative screen
			if (event.key.code == sf::Keyboard::Escape) {
				isGamePaused = true;
			}
		}

		//Check for release
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
				leftKeyPressed = false;
			}

			if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
				rightKeyPressed = false;
			}
			
			if (event.key.code == sf::Keyboard::Space) {
				spaceKeyPressed = false;
			}
		}
	}
	//Only move left or right if one is pressed *and* the other is NOT pressed. Also ensure the player is within the screen bounds.
	if (leftKeyPressed && !rightKeyPressed && player.getSprite().getPosition().x > (0 + player.getSprite().getLocalBounds().width / 2)) {
		player.move(-5);
	}

	if (rightKeyPressed && !leftKeyPressed && player.getSprite().getPosition().x < (xSize - player.getSprite().getLocalBounds().width / 2)) {
		player.move(5);
	}

	//Attempt to fire a shot
	if (spaceKeyPressed && !player.isPlayerDead()) {
		player.shoot(*this);
	}
}

//Give the player some points - they earned it.
void GameManager::addToScore(int points) {
	score += points;
}

//Add the bullet passed into our bullet vector
void GameManager::addBulletToVector(Bullet bullet) {
	bulletVector->push_back(bullet);
}

//Draw the main game screen - handled in here instead of DisplayManager for access reasons.
void GameManager::drawGameObjects(sf::RenderWindow &window) {
	for (int i = 0; i < alienVector->size(); i++) {
		//Draw all aliens, but only if they're alive.
		if (!alienVector->at(i).isDead()) {
			window.draw(alienVector->at(i).getSprite());
		}
	}

	for (int i = 0; i < bulletVector->size(); i++) {
		//Draw all bullets
		window.draw(bulletVector->at(i).getSprite());
	}

	//Draw the player themselves
	window.draw(player.getSprite());
	//Call the function in player to draw however many lives they currently have
	player.drawLives(window);

	//Draw text objects
	dispMan.drawText(window, barrier_1_position, 20, "SCORE", true, 18);
	dispMan.drawText(window, barrier_1_position, 50, std::to_string(score), true, 18);

	dispMan.drawText(window, xSize / 2, 20, "HI-SCORE", true, 18);
	dispMan.drawText(window, xSize / 2, 50, std::to_string(hiscore), true, 18);

	if (mothershipActive) {
		window.draw(mothership.getSprite());
	}

	//Draw the barriers
	for (int i = 0; i < barrier_vector_1->size(); i++) {
		//All four vectors are the same size, draw them all in one loop to save processing time
		if (barrier_vector_1->at(i).getHealth() > 0) { window.draw(barrier_vector_1->at(i).getSprite()); }
		if (barrier_vector_2->at(i).getHealth() > 0) { window.draw(barrier_vector_2->at(i).getSprite()); }
		if (barrier_vector_3->at(i).getHealth() > 0) { window.draw(barrier_vector_3->at(i).getSprite()); }
		if (barrier_vector_4->at(i).getHealth() > 0) { window.draw(barrier_vector_4->at(i).getSprite()); }
	}
}

//See if a bullet has broken our barrier.
bool GameManager::checkBulletBarrierCollision(Bullet &bullet) {
	//Check if the bullet is vertically in the area for our barriers.
	if (bullet.getSprite().getPosition().y >= ySize - 120 && bullet.getSprite().getPosition().y <= ySize - 62) {
		sf::FloatRect bulletBoundingBox = bullet.getSprite().getGlobalBounds();

		//Within barrier 1's bounds
		if (bullet.getSprite().getPosition().x >= barrier_1_position - 36 && bullet.getSprite().getPosition().x <= barrier_1_position + 36) {
			for (int i = 0; i < barrier_vector_1->size(); i++) {
				Barrier &barrier = barrier_vector_1->at(i);

				sf::FloatRect barrierBoundingBox = barrier.getSprite().getGlobalBounds();

				if (bulletBoundingBox.intersects(barrierBoundingBox)) {
					if (barrier.getShot()) {
						return true;
					}
				}
			}
		}
		//Within barrier 2's bounds
		if (bullet.getSprite().getPosition().x >= barrier_2_position - 36 && bullet.getSprite().getPosition().x <= barrier_2_position + 36) {
			for (int i = 0; i < barrier_vector_2->size(); i++) {
				Barrier &barrier = barrier_vector_2->at(i);

				sf::FloatRect barrierBoundingBox = barrier.getSprite().getGlobalBounds();

				if (bulletBoundingBox.intersects(barrierBoundingBox)) {
					if (barrier.getShot()) {
						return true;
					}
				}
			}
		}
		//Within barrier 3's bounds
		if (bullet.getSprite().getPosition().x >= barrier_3_position - 36 && bullet.getSprite().getPosition().x <= barrier_3_position + 36) {
			for (int i = 0; i < barrier_vector_3->size(); i++) {
				Barrier &barrier = barrier_vector_3->at(i);

				sf::FloatRect barrierBoundingBox = barrier.getSprite().getGlobalBounds();

				if (bulletBoundingBox.intersects(barrierBoundingBox)) {
					if (barrier.getShot()) {
						return true;
					}
				}
			}
		}
		//Within barrier 4's bounds
		if (bullet.getSprite().getPosition().x >= barrier_4_position - 36 && bullet.getSprite().getPosition().x <= barrier_4_position + 36) {
			for (int i = 0; i < barrier_vector_4->size(); i++) {
				Barrier &barrier = barrier_vector_4->at(i);

				sf::FloatRect barrierBoundingBox = barrier.getSprite().getGlobalBounds();

				if (bulletBoundingBox.intersects(barrierBoundingBox)) {
					if (barrier.getShot()) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

//Move the bullet if it's owned by a player
//In hindsight, I could've handled the player/alien bullets in a single for loop and then called move player/alien bullet from in there, but I ran out of time to change it :( 
void GameManager::movePlayerBullet(Player &player) {
	//Iterate through all registered bullets
	for (int i = 0; i < bulletVector->size(); i++) {
		Bullet b = bulletVector->at(i);
		//Check if a player owns this bullet
		if (b.isPlayerOwned) {
			sf::RectangleShape bullet = b.getSprite();
			b.move(bullet, -playerBulletSpeed);

			b.setSprite(bullet);
			bulletVector->at(i) = b;

			//Check if the bullet hit a barrier
			if (checkBulletBarrierCollision(b)) {
				//Delete the bullet from existance 
				bulletVector->erase(bulletVector->begin() + i);
				i--;
				player.bulletActive = false;
				return;
			}

			//Get the bullets bounding box
			sf::FloatRect bulletBoundingBox = bullet.getGlobalBounds();

			//Only check if we can hit the mothership, if the mothership is active.
			if (mothershipActive) {
				if (bulletBoundingBox.intersects(mothership.getSprite().getGlobalBounds())) {
					sfx_dead.setBuffer(buffer_dead);
					sfx_dead.play();
					mothership = Mothership(); //Set back to default 
					mothershipCooldown = 500;
					mothershipActive = false;
					score += mothership.getPointValue();

					bulletVector->erase(bulletVector->begin() + i);
					i--;
					player.bulletActive = false;
				}
			}

			if (bullet.getPosition().y < 0) {
				//It's off screen, remove the bullet from the vector and let the player shoot again.
				bulletVector->erase(bulletVector->begin() + i);
				i--;
				player.bulletActive = false;
				return;
			}
			else {
				//Check each alien to see if they were shot by this bullet.
				for (int j = 0; j < alienVector->size(); j++) {
					Alien &a = alienVector->at(j);
					if (!a.isDead()) {
						sf::Sprite alien = a.getSprite();
						sf::FloatRect alienBoundingBox = alien.getGlobalBounds();

						if (alienBoundingBox.intersects(bulletBoundingBox)) {
							//If they were shot, remove the alien and bullet from their respective vectors.
							a.kill(*this);
							bulletVector->erase(bulletVector->begin() + i);
							i--;
							player.bulletActive = false;
							return;
						}
					}
				}
			}
		}
	}
}

void GameManager::moveAlienBullet(Player &player) {
	//Iterate through all registered bullets
	for (int i = 0; i < bulletVector->size(); i++) {
		Bullet b = bulletVector->at(i);
		if (!b.isPlayerOwned) {
			sf::RectangleShape bullet = b.getSprite();
			b.move(bullet, alienBulletSpeed);

			b.setSprite(bullet);
			bulletVector->at(i) = b;

			if (checkBulletBarrierCollision(b)) {
				bulletVector->erase(bulletVector->begin() + i);
				i--;
			}

			//handle alien bullets
			if (bullet.getPosition().y > ySize) {
				//It's off screen, remove the bullet from the vector
				bulletVector->erase(bulletVector->begin() + i);
				i--;
			}
			else {
				//Get the bullets bounding box
				sf::FloatRect bulletBoundingBox = bullet.getGlobalBounds();

				if (bullet.getPosition().y > ySize - 80 && bullet.getPosition().y < ySize - 40) {
					sf::FloatRect playerBoundingBox = player.getSprite().getGlobalBounds();
					if (bulletBoundingBox.intersects(playerBoundingBox)) {
						player.getShot(*this);
						bulletVector->erase(bulletVector->begin() + i);
						i--;
					}
				}
			}
		}
	}
}

int directionCooldown = 0; //A cooldown for changing directions, to stop it changing rapidly when aliens are technically still out of bounds.
//Move the aliens
void GameManager::moveAliens(bool &moveRight, sf::FloatRect gameArea) {
	if (playSound()) {
		sfx_move.setBuffer(buffer_move[moveSfxId]);
		sfx_move.play();
		moveSfxId++;
		if (moveSfxId > 3) {
			moveSfxId = 0;
		}
	}

	int moveVertical = 0;

	//If the aliens were out of bounds, this will be 5.
	if (directionCooldown == 5) {
		//Set the amount to move by vertically
		moveVertical = 12;
		//Invert the direction of travel
		moveRight = !moveRight;
	}
	//Decrease cooldown once per movement until we're back at zero.
	if (directionCooldown > 0) {
		directionCooldown--;
	}

	for (int i = 0; i < alienVector->size(); i++) {
		//Get the alien from the vector
		Alien &a = alienVector->at(i);

		//Get the sprite of said alien
		sf::Sprite alien = a.getSprite();
		sf::Vector2f alienLocation(alien.getPosition().x, alien.getPosition().y);

		//Set it back to 5 when we need to change direction
		if (!gameArea.contains(alienLocation) && directionCooldown == 0 && !a.isDead()) {
			directionCooldown = 5;
		}

		if (alien.getPosition().y > ySize) {
			//Player loses a life if an alien goes off screen...
			player.getShot(*this);
			//..but the alien dies in the process.
			a.kill(*this);
		}

		//Move the aliens, setting their new location into the vector.
		a.setRenderer(a.move(moveRight, 5, moveVertical));

		if (!a.isDead()) {
			//Attempt to fire a bullet (using RNG, most times this will not actually fire a bullet. But it might!)
			a.shoot(alienShootChance, *this->bulletVector);

			//Before we even bother checking if the alien is hitting a barrier, check that it's low enough in the screen to be able to hit a barrier.
			if (alien.getPosition().y > ySize - 110 && alien.getPosition().y < ySize - 63) {
				sf::FloatRect alienBoundingBox = alien.getGlobalBounds();
				//Check for alien-barrier collision
				if (alien.getPosition().x >= barrier_1_position - 32 && alien.getPosition().x <= barrier_1_position + 32) {
					for (int i = 0; i < barrier_vector_1->size(); i++) {
						Barrier &barrier = barrier_vector_1->at(i);

						sf::FloatRect barrierBoundingBox = barrier.getSprite().getGlobalBounds();

						if (alienBoundingBox.intersects(barrierBoundingBox)) {
							barrier.getShot();
						}
					}
				}
				//Within barrier 2's bounds
				if (alien.getPosition().x >= barrier_2_position - 32 && alien.getPosition().x <= barrier_2_position + 32) {
					for (int i = 0; i < barrier_vector_2->size(); i++) {
						Barrier &barrier = barrier_vector_2->at(i);

						sf::FloatRect barrierBoundingBox = barrier.getSprite().getGlobalBounds();

						if (alienBoundingBox.intersects(barrierBoundingBox)) {
							barrier.getShot();
						}
					}
				}
				//Within barrier 3's bounds
				if (alien.getPosition().x >= barrier_3_position - 32 && alien.getPosition().x <= barrier_3_position + 32) {
					for (int i = 0; i < barrier_vector_3->size(); i++) {
						Barrier &barrier = barrier_vector_3->at(i);

						sf::FloatRect barrierBoundingBox = barrier.getSprite().getGlobalBounds();

						if (alienBoundingBox.intersects(barrierBoundingBox)) {
							barrier.getShot();
						}
					}
				}
				//Within barrier 4's bounds
				if (alien.getPosition().x >= barrier_4_position - 32 && alien.getPosition().x <= barrier_4_position + 32) {
					for (int i = 0; i < barrier_vector_4->size(); i++) {
						Barrier &barrier = barrier_vector_4->at(i);

						sf::FloatRect barrierBoundingBox = barrier.getSprite().getGlobalBounds();

						if (alienBoundingBox.intersects(barrierBoundingBox)) {
							barrier.getShot();
						}
					}
				}
			}
		}
	}
}

//Mute/unmute the game
void GameManager::toggleSound() {
	playSFX = !playSFX;
	if (mothershipActive) {
		mothership.toggleSFX(playSFX);
	}
}

//Create one full barrier, centred at the defined X position.
void GameManager::createBarrier(std::vector<Barrier> &vec, int xPos) {
	//bottom row
	vec.push_back(Barrier(xPos - 30, ySize - 75, "Full_Barrier", 0));
	vec.push_back(Barrier(xPos + 18, ySize - 75, "Full_Barrier", 0));

	//middle row
	vec.push_back(Barrier(xPos - 30, ySize - 87, "Full_Barrier", 0));
	vec.push_back(Barrier(xPos - 18, ySize - 87, "Lower_Barrier_L", 0));
	vec.push_back(Barrier(xPos +  6, ySize - 87, "Lower_Barrier_R", 0));
	vec.push_back(Barrier(xPos + 18, ySize - 87, "Full_Barrier", 0));

	//top row
	vec.push_back(Barrier(xPos - 30, ySize - 99, "Corner_Barrier", 0));
	vec.push_back(Barrier(xPos - 18, ySize - 99, "Full_Barrier", 0));
	vec.push_back(Barrier(xPos -  6, ySize - 99, "Full_Barrier", 0));
	vec.push_back(Barrier(xPos +  6, ySize - 99, "Full_Barrier", 0));
	vec.push_back(Barrier(xPos + 18, ySize - 99, "Corner_Barrier", 90));
}