#include "MovableObject.h"

#include <iostream>
#include <math.h>
#include "Game.h"

MovableObject::MovableObject()
{
}


MovableObject::~MovableObject()
{
}

double MovableObject::GetDistanceFromLastRoutePoint(double x, double y)
{
	if (_routes.size() == 0)
		return std::numeric_limits<double>::max();

	return 0.0;
}

std::shared_ptr<MovableObject> MovableObject::CreateObject(TaskObjectConfig *config)
{
	auto obj = std::make_shared<MovableObject>();
	obj->SetPosition(config->GetInitialX(), config->GetInitialY());

	return obj;
}

void MovableObject::SetFinalTarget(std::shared_ptr<RoutePoint> targetPoint)
{
	_target = targetPoint;
}

void MovableObject::SetTarget(std::shared_ptr<RoutePoint> targetPoint)
{
	_currentRoute = targetPoint;

	//Calculate Direction

	_dx = targetPoint->GetX() - _x;
	_dy = targetPoint->GetY() - _y;

	_d = sqrt(_dx * _dx + _dy * _dy);

	CalculateMoveSpeed();
}

void MovableObject::Step(double units)
{
	if (_currentRoute == nullptr)
		return;

	//if (_moveStepsLeft > 0.1)
	{
		double oldX = _x;
		double oldY = _y;

		double deltaX = _speedX * units;
		double deltaY = _speedY * units;

		double distanceToTarget = GetDistance(*_currentRoute.get());
		double toMove = sqrt(deltaX * deltaX + deltaY * deltaY);

		if (toMove > distanceToTarget)
		{
			if (_routes.size())
			{
				if (_currentRoute)
				{
					_game->TriggerRouteReachEvent(_currentRoute->GetTag(), _currentRoute->GetX(), _currentRoute->GetY());
				}
				_routes.pop_front();
				if (_routes.size())
				{
					SetTarget(_routes.front());
				}
				else
				{
					SetTarget(_target);
				}
			}
			else
			{
				_speed = 0;
				_speedX = 0;
				_speedY = 0;
				_x = _currentRoute->GetX();
				_y = _currentRoute->GetY();
				std::cout << _x << "," << _y << "\t\td = " << GetDistance(*_currentRoute.get()) << " -- reached target" << std::endl;
			}
		}

		_x += _speedX * units;
		_y += _speedY * units;

		std::cout << _x << "," << _y << "\t\td = "<< GetDistance(*_currentRoute.get()) << std::endl;

		//_moveStepsLeft--;

		double steps = _d / _speed;		//total steps needed to reach target
		//_moveStepsLeft = _moveStepsTotal = steps;
	}
}

void MovableObject::CalculateMoveSpeed()
{
	double cosVal = _dx / sqrt(_dx * _dx + _dy * _dy);
	double sinVal = _dy / sqrt(_dx * _dx + _dy * _dy);

	double spd = _speed;
	double steps = _d / spd;		//total steps needed to reach target
	_moveStepsLeft = _moveStepsTotal = steps;

	_speedX = spd * cosVal;
	_speedY = spd * sinVal;
}

void MovableObject::AddRoutePoint(double x, double y, int uid)
{
	auto routePoint = std::make_shared<RoutePoint>();
	routePoint->SetPosition(x, y);
	routePoint->SetTag(uid);
	_routes.push_back(routePoint);

	if (_currentRoute != _routes.front())
	{
		_currentRoute = _routes.front();

		_dx = _currentRoute->GetX() - _x;
		_dy = _currentRoute->GetY() - _y;
		_d = sqrt(_dx * _dx + _dy * _dy);

		CalculateMoveSpeed();
	}
}
