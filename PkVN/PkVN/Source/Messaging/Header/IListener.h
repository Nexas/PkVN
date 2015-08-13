#ifndef ILISTENER_H_
#define ILISTENER_H_

#include "CEvent.h"

class IListener
{
public:
	IListener(void) {}
	virtual ~IListener(void) {}

	// HandleEvent MUST be defined in the derived class.
	// Function will proc when this object receives an event.
	virtual void HandleEvent(CEvent* pEvent) = 0;
};

#endif /*ILISTENER_H_*/