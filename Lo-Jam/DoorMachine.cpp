#include "DoorMachine.h"

closedDoorState::closedDoorState(Door* s) { door = s; }
void closedDoorState::Open() { printf("Changing door state to open.\n"); door->changeState(new openDoorState(door)); delete this; }
void closedDoorState::Close() { printf("Door is already closed.\n"); }
void closedDoorState::Lock() { printf("Changing door state to locked.\n"); door->changeState(new lockedDoorState(door)); delete this; }
void closedDoorState::Unlock() { printf("Door is already unlocked.\n"); }

openDoorState::openDoorState(Door* s) { door = s; }
void openDoorState::Open() { printf("Door is already open.\n"); }
void openDoorState::Close() { printf("Changing door state to closed.\n"); door->changeState(new closedDoorState(door)); delete this; }
void openDoorState::Lock() { printf("Door must be closed to lock.\n"); }
void openDoorState::Unlock() { printf("Door is not locked.\n"); }

lockedDoorState::lockedDoorState(Door* s) { door = s; }
void lockedDoorState::Open() { printf("Door is locked, cannot open.\n"); }
void lockedDoorState::Close() { printf("Door is already closed.\n"); }
void lockedDoorState::Lock() { printf("Door is already locked.\n"); }
void lockedDoorState::Unlock() { printf("Changing door to unlocked state.\n"); door->changeState(new unlockedDoorState(door)); delete this; }

unlockedDoorState::unlockedDoorState(Door* s) { door = s; }
void unlockedDoorState::Open() { printf("Changing door state to open.\n"); door->changeState(new openDoorState(door)); delete this; }
void unlockedDoorState::Close() { printf("Door is already closed.\n"); }
void unlockedDoorState::Lock() { printf("Changing door state to locked.\n"); door->changeState(new lockedDoorState(door)); delete this; }
void unlockedDoorState::Unlock() { printf("Door is already unlocked.\n"); }