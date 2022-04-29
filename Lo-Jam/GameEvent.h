#ifndef GAMEEVENT_H
#define GAMEEVENT_H
#pragma warning (disable: 26812)

class GameEvent 
{	

public:

	enum EventType
	{
		Thing1,
		Thing2
	};

	EventType type;

	class GameObject* source;


	
	GameEvent(EventType t) : type(t) { source = nullptr; }
	template <class T>
	GameEvent &makeWithSource(T* ref) { source = ref; return *this; }
	~GameEvent() {}


};

#endif // !GAMEEVENT_H
