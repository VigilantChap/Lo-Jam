#include "Door.h"
#include "DoorMachine.h"


Door::Door() : GameObject("door") {
	state = new closedDoorState(this);
}

void Door::tryOpen() { printf("Attempting to open door.\n"); state->Open(); }
void Door::tryClose() { printf("Attempting to close door.\n"); state->Close(); }
void Door::tryLock() { printf("Attempting to lock door.\n"); state->Lock(); }
void Door::tryUnlock() { printf("Attempting to unlock door.\n"); state->Unlock(); }