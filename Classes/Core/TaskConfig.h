#pragma once

#include <vector>
#include <memory>
#include "TaskObjectConfig.h"

class TaskConfig
{
	friend class Game;
public:

protected:
	double _targetX;
	double _targetY;
	double _targetRadius = 1.0;

	double _startX;
	double _startY;

	double _mapWidth;
	double _mapHeight;

	std::vector<std::shared_ptr<TaskObjectConfig>> _objectConfig;

public:
	void LoadFromJson(const char* jsonFile);
};

