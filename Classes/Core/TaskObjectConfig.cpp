
#include "TaskObjectConfig.h"

#include "json/rapidjson.h"
#include "json/document.h"

void TaskObjectConfig::ParseConfig(rapidjson::Value &value)
{
	rapidjson::Value & initialX = value["initialX"];
	rapidjson::Value & initialY = value["initialY"];
	_initialX = initialX.GetDouble();
	_initialY = initialY.GetDouble();

	rapidjson::Value & radius = value["radius"];
	_radius = radius.GetDouble();



}

double TaskObjectConfig::GetInitialX() const
{
	return _initialX;
}

double TaskObjectConfig::GetInitialY() const
{
	return _initialY;
}
