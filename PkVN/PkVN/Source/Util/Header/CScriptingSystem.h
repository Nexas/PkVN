#ifndef CSCRIPTINGSYSTEM_H_
#define CSCRIPTINGSYSTEM_H_

#include <string>
#include <vector>
#include <fstream>
#include <iterator>

using namespace std;

#include "../../Messaging/Header/CEventSystem.h"

class CDecision;

class CScriptingSystem
{
	vector<CDecision*>	m_vDecisions;
	vector<string> m_vLines;
	int m_nLinePos;

	CScriptingSystem() : m_nLinePos(0) {};
	~CScriptingSystem();
	CScriptingSystem(const CScriptingSystem& obj) {}
	CScriptingSystem& operator=(CScriptingSystem& obj) {}

public:
	friend class CGameplayState;

	int LoadScriptText(string szFilename);
	void NextLine();
	void ChangeScript(string szFilename);
	void ClearLines();
	void ClearDecisions();
	static CScriptingSystem* GetInstance();
	void ParseString();
	vector<CDecision*>	GetDecisions()	{return m_vDecisions;}


};

class CDecision
{
	string m_szTextToDisplay;
	string m_szFilename;

public:

	CDecision() {}
	~CDecision() {}
	
	// Accessors
	string	GetTextToDisplay()	{return m_szTextToDisplay;}
	string	GetFilename()		{return m_szFilename;}

	// Mutators
	void	SetTextToDisplay(string szTextToDisplay)	{m_szTextToDisplay = szTextToDisplay;}
	void	SetFilename(string szFilename)				{m_szFilename = szFilename;}
};

#endif /*CSCRIPTINGSYSTEM_H_*/