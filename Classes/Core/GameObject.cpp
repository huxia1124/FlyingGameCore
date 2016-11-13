#include "GameObject.h"
#include <math.h>


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

double GameObject::GetDistance(const GameObject & obj)
{
	return sqrt((obj._x - _x) * (obj._x - _x) + (obj._y - _y) * (obj._y - _y));
}

void GameObject::SetPosition(double x, double y)
{
	_x = x;
	_y = y;
}


double GameObject::GetX()
{
	return _x;
}

double GameObject::GetY()
{
	return _y;
}

void GameObject::SetTag(int tag)
{
	_tag = tag;
}

int GameObject::GetTag()
{
	return _tag;
}
