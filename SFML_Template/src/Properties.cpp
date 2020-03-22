#include "../include/Properties.h"

int Properties::getWindowXSize() {
	return Properties::xSize * Properties::scale;
}

int Properties::getWindowYSize() {
	return Properties::ySize * Properties::scale;
}

float Properties::getScale() {
	return Properties::scale;
}
