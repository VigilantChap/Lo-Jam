#ifndef GAMEEVENT_H
#define GAMEEVENT_H
#pragma warning (disable: 26812)

class GameEvent 
{	

public:

	enum EventType
	{
		HasDied,
		IsAttacking,
		IsInjured

	};

	EventType type;

	class GameObject* source;


	template <class T>
	GameEvent(EventType _type, T* ref) : type(_type) { source = ref; }
	~GameEvent() {}


};

#endif // !GAMEEVENT_H
