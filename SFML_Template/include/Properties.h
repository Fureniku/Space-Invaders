#include <SFML/Graphics.hpp>
#pragma once

class Properties {
public:
	const int xSize = 512;
	const int ySize = 512;

	const int playerBulletSpeed = 10;
	const int alienBulletSpeed = 1;

	int getWindowXSize();
	int getWindowYSize();
};