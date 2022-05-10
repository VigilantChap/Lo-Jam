#ifndef IOBSERVER_H
#define IOBSERVER_H
#include "GameEvent.h"
class IObserver
{
public:

	virtual void ObservableEvent(GameEvent& e) = 0;
};

#endif // !IOBSERVER_H
