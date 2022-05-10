#ifndef DOORMACHINE_H
#define DOORMACHINE_H
#include "Door.h"
#include <iostream>

class closedDoorState : public DoorState {
public:
	Door * door;
	closedDoorState(Door* s);

	void Open();
	void Close();
	void Lock();
	void Unlock();
};

class openDoorState : public DoorState {
public:
	Door* door;
	openDoorState(Door* s);

	void Open();
	void Close();
	void Lock();
	void Unlock();
};

class lockedDoorState : public DoorState {
public:
	Door* door;
	lockedDoorState(Door* s);

	void Open();
	void Close();
	void Lock();
	void Unlock();
};

class unlockedDoorState : public DoorState {
public:
	Door* door;
	unlockedDoorState(Door* s);

	void Open();
	void Close();
	void Lock();
	void Unlock();

};

#endif // !DOORMACHINE_H


