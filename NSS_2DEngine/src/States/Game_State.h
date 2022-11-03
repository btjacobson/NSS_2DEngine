#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "../States/State.h"
#include "../Core/Map.h"
#include "../Core/Camera.h"
#include "../Network/Client.h"

class Game_State : public State
{
public:
	Game_State();
	~Game_State();

	virtual void Init() override;
	virtual void Cleanup() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow* window) override;

	virtual bool IsActive() override;

	void MoveRight();
	void MoveLeft();
	void Stop();

	void TestMouseP();
	void TestMouseR();

	void HandlePacket(const PacketID& id, sf::Packet& packet, Client* client);
	void ProcessCommand();
	void HandleServer();

private:
	Map map;
	Camera camera;
	Client* client;

	sf::Clock clock;
	sf::Thread* commandThread;
	sf::Thread* networkThread;
};

#endif
