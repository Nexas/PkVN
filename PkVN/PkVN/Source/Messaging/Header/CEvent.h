#ifndef CEVENT_H_
#define CEVENT_H_

#include <string>
using std::string;

typedef string EVENTID;

class CEvent
{
	EVENTID		m_EventID;	// The ID type of the Event.
	void*		m_pParam;	// Used to store any one variable type.

public:
	CEvent(EVENTID eventID, void* pParam = NULL)
	{
		m_EventID = eventID;
		m_pParam = pParam;
	}

	~CEvent()	{}

	//Accessors:
	inline EVENTID	GetEventID()	{return m_EventID;}
	inline void*	GetParam()		{return m_pParam;}

};

#endif /*CEVENT_H_*/