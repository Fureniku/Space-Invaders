#include <SFML/Graphics.hpp>
#pragma once

class Properties {
public:
	const int xSize = 512;
	const int ySize = 512;
	const float scale = 1.0F;

	int getWindowXSize();
	int getWindowYSize();
	float getScale();
};