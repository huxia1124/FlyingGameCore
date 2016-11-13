#pragma once

class Game;

class GameObject
{
	friend class Game;
public:
	GameObject();
	virtual ~GameObject();

protected:
	double _x;
	double _y;
	void *_userData = nullptr;
	Game *_game = nullptr;
	int _tag = 0;

public:
	double GetX();
	double GetY();
	void SetTag(int tag);
	int GetTag();

	double GetDistance(const GameObject& obj);
	void SetPosition(double x, double y);
};

