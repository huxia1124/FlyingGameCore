
#include "TaskConfig.h"

#include "json/rapidjson.h"
#include "json/document.h"

#include <iostream>
#include <fstream>


void TaskConfig::LoadFromJson(const char* jsonFile)
{
	std::ifstream fs(jsonFile);
	if (!fs.is_open())
		return;

	std::string str((std::istreambuf_iterator<char>(fs)),
		std::istreambuf_iterator<char>());

	fs.close();

	if (str.size() == 0)
		return;

	// parse json from string.
	using rapidjson::Document;
	Document doc;
	doc.Parse<0>(str.c_str());

	if (doc.HasParseError()) {
		rapidjson::ParseErrorCode code = doc.GetParseError();
		//psln(code);
		return;
	}

	//Read basic configurations
	rapidjson::Value & mapWidth = doc["mapWidth"];
	rapidjson::Value & mapHeight = doc["mapHeight"];
	_mapWidth = mapWidth.GetDouble();
	_mapHeight = mapHeight.GetDouble();

	rapidjson::Value & startX = doc["startX"];
	rapidjson::Value & startY = doc["startY"];
	_startX = startX.GetDouble();
	_startY = startY.GetDouble();

	rapidjson::Value & targetX = doc["targetX"];
	rapidjson::Value & targetY = doc["targetY"];
	_targetX = targetX.GetDouble();
	_targetY = targetY.GetDouble();

	rapidjson::Value & targetRadius = doc["targetRadius"];
	_targetRadius = targetRadius.GetDouble();


	//Read objects
	rapidjson::Value & objectConfigArray = doc["objectConfig"];
	if (!objectConfigArray.IsArray())
		return;

	for (size_t i = 0; i < objectConfigArray.Size(); ++i) {
		rapidjson::Value & objectConfig = objectConfigArray[i];

		auto objData = std::make_shared<TaskObjectConfig>();
		objData->ParseConfig(objectConfig);
		_objectConfig.push_back(objData);
	}

	/*
	//Read Dimension
	_cols = doc["cols"].GetInt();
	_rows = doc["rows"].GetInt();

	//Read Combination
	rapidjson::Value & combine = doc["combine"];
	for (size_t i = 0; i < combine.Size(); ++i) {
		rapidjson::Value & c = combine[i];
		_validCombinition.insert(c.GetInt());
	}

	//Read StartPoint
	if (mode == 3)	//SingleLine
	{
		rapidjson::Value & startPoint = doc["startPoint"];
		_startPoint.first = startPoint[0].GetInt();
		_startPoint.second = startPoint[1].GetInt();
	}
	*/
}
