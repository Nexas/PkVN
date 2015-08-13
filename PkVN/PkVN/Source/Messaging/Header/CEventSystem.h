#ifndef CEVENTSYSTEM_H_
#define CEVENTSYSTEM_H_

#include <list>
#include <map>
using std::multimap;
using std::pair;
using std::list;

#include "CEvent.h"
#include "IListener.h"

class CEventSystem
{
	// The database that contains "clients" that listen for events.
	multimap<EVENTID, IListener*>	m_ClientDatabase;

	// Events waiting to be processed.
	list<CEvent>		m_CurrentEvents;

	// Finds the event in the database and then calls each registered client's HandleEvent functions.
	void DispatchEvent(CEvent* pEvent);
	bool AlreadyRegistered(EVENTID eventID, IListener* pClient);

	CEventSystem()	{}
	~CEventSystem() {}
	CEventSystem(const CEventSystem& obj);
	CEventSystem& operator=(const CEventSystem& obj);

public:

	static CEventSystem* GetInstance(void)
	{
		static CEventSystem instance;
		return &instance;
	}

	// This will register a client, and add them into the database.
	void RegisterClient(EVENTID eventID, IListener* pClient);

	// This will unregister a client for a specific event.
	void UnregisterClient(EVENTID eventID, IListener* pClient);

	// Unregisters the client from the databse.
	void UnregisterClientAll(IListener* pClient);

	// Sends an event to be processed.
	void SendEvent(EVENTID, void* pData = NULL);

	// Processes all events in the event list.
	void ProcessEvents(void);

	// Clears all pending events
	void ClearEvents(void);

	// Unregisters all objects.
	void ShutdownEventSystem(void);

};

#endif /*CEVENTSYSTEM_H_*/