#pragma once

#include <cstdint>
#include "GameObject.h"

struct IGameCallback
{
	virtual void OnRoutePointAdded(int uid, double x, double y) {};
	virtual void OnRoutePointReached(int uid, double x, double y) {};
	virtual void OnDestinationReached() {};
	virtual void OnObjectLocationChanged(GameObject *obj) {};
	virtual void OnDestinationSetup(double x, double y, double radius) {};
	virtual void OnPlayerSetup(double x, double y) {};

};

