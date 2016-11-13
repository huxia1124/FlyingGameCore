#include "Game.h"
#include "PlayerObject.h"


Game::Game()
{
}


Game::~Game()
{
}

void Game::TriggerRouteReachEvent(int uid, double x, double y)
{
	if (_callback)
		_callback->OnRoutePointReached(uid, x, y);
}

void Game::SetFinalTarget(double x, double y)
{
	_finalTarget = std::make_shared<RoutePoint>();
	_finalTarget->SetPosition(x, y);
}

void Game::Start()
{
	_startTime = std::chrono::system_clock::now();
}

void Game::Step()
{
	auto now = std::chrono::system_clock::now();
	auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
	auto epoch = now_ms.time_since_epoch();
	auto epochms = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
	auto elapsed = now - _startTime;
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(elapsed);
	auto elapsedUnit = elapsed_ms.count();
	auto moveUnit = elapsedUnit / _designedUnitpms;
	
	moveUnit = 10.0;
	for (auto &obj : _movableObjects)
	{
		obj->Step(moveUnit);
	}
}

void Game::AddMovableObject(std::shared_ptr<MovableObject> obj)
{
	_movableObjects.push_back(obj);
}

void Game::AddPlayerObject(double x, double y)
{
	std::shared_ptr<MovableObject> player = std::make_shared<PlayerObject>();
	player->SetPosition(x, y);
	player->SetFinalTarget(_finalTarget);
	player->SetTarget(_finalTarget);
	player->_game = this;
	_movableObjects.push_back(player);
	_playerObject = player;
}

void Game::GetPlayerLocation(double &x, double &y)
{
	if (_playerObject) {
		x = _playerObject->GetX();
		y = _playerObject->GetY();
	}
}

void Game::AddRoutePoint(double x, double y)
{
	double dist = _playerObject->GetDistanceFromLastRoutePoint(x, y);
	int uid = _routePointUidBase++;
	_playerObject->AddRoutePoint(x, y, uid);
	if (_callback)
		_callback->OnRoutePointAdded(uid, x, y);

}

void Game::SetCallback(IGameCallback *callback)
{
	_callback = callback;
}

void Game::Initialize(TaskConfig *config)
{

	SetFinalTarget(config->_targetX, config->_targetY);
	if (_callback)
		_callback->OnDestinationSetup(config->_targetX, config->_targetY, config->_targetRadius);
	AddPlayerObject(config->_startX, config->_startY);
	if (_callback)
		_callback->OnPlayerSetup(config->_startX, config->_startY);

	for (auto &objConfig : config->_objectConfig)
	{
		std::shared_ptr<MovableObject> spObject(MovableObject::CreateObject(objConfig.get()));
		AddMovableObject(spObject);
		if (_callback)
			_callback->OnObjectSetup(spObject.get());
	}
}
