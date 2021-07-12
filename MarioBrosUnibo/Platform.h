#pragma once
#include "Entity.h"
class Platform : public Entity
{
protected:
public:
	Platform(int x = 0, int y = 0, char symbol = '_');
};
