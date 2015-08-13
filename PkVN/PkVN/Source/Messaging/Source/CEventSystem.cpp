#include "../Header/CEventSystem.h"

void CEventSystem::RegisterClient(EVENTID eventID, IListener* pClient)
{
	// Double check to make sure the client isn't already registered.
	if (!pClient || AlreadyRegistered(eventID, pClient))	return;

	// Register the database.
	m_ClientDatabase.insert(make_pair(eventID, pClient));
}

void CEventSystem::UnregisterClient(EVENTID eventID, IListener* pClient)
{
	// Make an iterator that will iterate through all of the clients recieving this event.]
	pair<multimap<EVENTID, IListener*>::iterator, multimap<EVENTID, IListener*>::iterator> range;

	// Find all clients to receieve this event.
	range = m_ClientDatabase.equal_range(eventID);

	// Go through the list of clients that are able to receive this event.
	for (multimap<EVENTID, IListener*>::iterator iter = range.first; iter != range.second; iter++)
	{
		// Check to see if it's the client we're looking for.
		if ((*iter).second == pClient)
		{
			// Remove the client from the list
			iter = m_ClientDatabase.erase(iter);
			break;
		}
	}
}

void CEventSystem::UnregisterClientAll(IListener* pClient)
{
	multimap<string, IListener*>::iterator iter = m_ClientDatabase.begin();

	while (iter != m_ClientDatabase.end())
	{
		if ((*iter).second == pClient)
		{
			iter = m_ClientDatabase.erase(iter);
		}
		else
			iter++;
	}
}

void CEventSystem::DispatchEvent(CEvent* pEvent)
{
	// Make an iterator and go through the database, seeing which clients should be receiving this event.
	pair<multimap<EVENTID, IListener*>::iterator, multimap<EVENTID, IListener*>::iterator> range;

	range = m_ClientDatabase.equal_range(pEvent->GetEventID());

	// Go through the list of clients able to receive this event.
	for (multimap<EVENTID, IListener*>::iterator iter = range.first; iter != range.second; iter++)
	{
		// Send the event out.
		(*iter).second->HandleEvent(pEvent);
	}
}

bool CEventSystem::AlreadyRegistered(EVENTID eventID, IListener* pClient)
{
	bool bIsAlreadyRegistered = false;

	// Iterate through all clients that should be receiving this event.
	pair<multimap<EVENTID, IListener*>::iterator, multimap<EVENTID, IListener*>::iterator> range;

	// Find all clients that are able to receive this event.
	range = m_ClientDatabase.equal_range(eventID);

	// Go through all clients able to receive this event.
	for (multimap<EVENTID, IListener*>::iterator iter = range.first; iter != range.second; iter++)
	{
		// Check if we found our client.
		if ((*iter).second == pClient)
		{
			bIsAlreadyRegistered = true;
			break;
		}
		
	}
	return bIsAlreadyRegistered;
}

void CEventSystem::SendEvent(EVENTID eventID, void* pData)
{
	// Push the event into the list.
	CEvent newEvent(eventID, pData);

	m_CurrentEvents.push_back(newEvent);
}

void CEventSystem::ProcessEvents(void)
{
	// Go through all events waiting to be processed.
	while (m_CurrentEvents.size())
	{
		DispatchEvent(&m_CurrentEvents.front());
		m_CurrentEvents.pop_front();
	}
}

void CEventSystem::ClearEvents(void)
{
	m_CurrentEvents.clear();
}

void CEventSystem::ShutdownEventSystem(void)
{
	m_ClientDatabase.clear();
}