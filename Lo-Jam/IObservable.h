#ifndef IOBSERVABLE_H
#define IOBSERVABLE_H
#include "IObserver.h"

class IObservable
{
public:
	virtual void AddObserver(IObserver * observer) = 0;
	virtual void Remove(IObserver * observer) = 0;
	virtual void Notify(GameEvent e) = 0;
};


#endif // !IOBSERVABLE_H
