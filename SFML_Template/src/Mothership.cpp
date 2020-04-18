#include "../include/Alien.h"
#include "../include/Mothership.h"

void Mothership::move() {
	sprite.move(-1, 0);

	//Switch between A texture and B texture
	this->toggleType();
}

//Loop the sound effect for a mothership being on-screen.
//This avoids the sound starting over every frame
void Mothership::toggleSFX(bool play) {
	sfx_move.setBuffer(buffer_move);
	if (play) {
		sfx_move.play();
	}
	else {
		sfx_move.stop();
	}
}