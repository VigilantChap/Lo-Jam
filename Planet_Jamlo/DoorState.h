#ifndef DOORSTATE_H
#define DOORSTATE_H
class DoorState {
public:

	virtual void Open() = 0;
	virtual void Close() = 0;
	virtual void Lock() = 0;
	virtual void Unlock() = 0;
};
#endif // DOORSTATE_H