#pragma once

#include <vector>
#include <map>
#include <memory>
#include "MovableObject.h"
#include <chrono>
#include "GameCallback.h"
#include "TaskConfig.h"

class Game
{
public:
	Game();
	virtual ~Game();

protected:
	std::vector<std::shared_ptr<MovableObject>> _movableObjects;
	std::chrono::time_point<std::chrono::system_clock> _startTime;

	long long _designedFPS = 60;
	double _designedUnitpms = 1000000 / 60.0;

	std::shared_ptr<RoutePoint> _finalTarget;
	std::shared_ptr<MovableObject> _playerObject;

	IGameCallback *_callback = nullptr;
	int _routePointUidBase = 0;

public:
	void TriggerRouteReachEvent(int uid, double x, double y);

	void SetFinalTarget(double x, double y);
	void Start();
	void Step();
	void AddMovableObject();
	void AddPlayerObject(double x, double y);
	void GetPlayerLocation(double &x, double &y);
	void AddRoutePoint(double x, double y);
	void SetCallback(IGameCallback *callback);
	void Initialize(TaskConfig *config);
};

