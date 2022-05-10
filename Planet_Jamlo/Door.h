#pragma once
#include "GameObject.h"
#include "DoorState.h"
class Door : public GameObject
{
public:
	Door();

	DoorState* state = nullptr;

	void changeState(DoorState* s) { state = s; }

	void tryOpen();
	void tryClose();
	void tryLock();
	void tryUnlock();
};

