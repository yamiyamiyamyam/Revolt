#pragma once
#include "GameNode.h"

class Map;
class Lobby;

class LobbyScene :
	public GameNode
{
private:
	Map* m_pMap;
	Lobby* m_pLobby;

	bool m_isPlayBGM;

public:
	LobbyScene();
	~LobbyScene();

	void Setup();
	void Update();
	void Render();
	void Destroy();
	void SetupLight();
};

