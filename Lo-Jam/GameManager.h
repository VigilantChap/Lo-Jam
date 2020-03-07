#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H


class GameManager
{
private:
	class SFWindow * window;
	class Scene * scene;

public:
	GameManager();
	bool Initialize();
	~GameManager();
	void Destroy();

	void Run();
};


#endif // !GAMEMANAGER_H