#pragma once
#include "GameObject.h"
#include "RoutePoint.h"
#include <memory>
#include <vector>
#include <deque>

class MovableObject : public GameObject
{
public:
	MovableObject();
	virtual ~MovableObject();

protected:

	std::shared_ptr<RoutePoint> _target;
	std::shared_ptr<RoutePoint> _currentRoute;
	std::deque<std::shared_ptr<RoutePoint>> _routes;
	double _speed = 0.20;

	double _dx;
	double _dy;
	double _d;

	double _moveStepsTotal = 0;
	double _moveStepsLeft = 0;

	double _speedX;
	double _speedY;

public:
	virtual double GetDistanceFromLastRoutePoint(double x, double y);

public:
	void SetFinalTarget(std::shared_ptr<RoutePoint> targetPoint);
	void SetTarget(std::shared_ptr<RoutePoint> targetPoint);
	void Step(double units);

	void CalculateMoveSpeed();
	void AddRoutePoint(double x, double y, int uid);
};

