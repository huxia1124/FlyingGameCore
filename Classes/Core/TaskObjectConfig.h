#pragma once

#include "json/rapidjson.h"
#include "json/document.h"

class TaskObjectConfig
{
public:

protected:
	double _initialX;
	double _initialY;
	double _radius = 1.0;




public:
	void ParseConfig(rapidjson::Value &value);
};

