#include "../include/Alien.h"
#include "../include/Mothership.h"

void Mothership::move() {

	sprite.move(-1, 0);

	//Switch between A texture and B texture
	this->toggleType();
}