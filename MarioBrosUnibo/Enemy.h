#pragma once
#include "Entity.h"
class Enemy : public Entity
{
protected:
public:
	Enemy(int x = 0, int y = 0, char symbol = '&');
};

