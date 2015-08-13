#include "../Header/CScriptingSystem.h"

CScriptingSystem::~CScriptingSystem()
{
	
}

int CScriptingSystem::LoadScriptText(string szFilename)
{
	ifstream fin;
	fin.open(szFilename.c_str());

	if (fin.is_open())
	{
		int numLines = 0;
		char symbol;			// The symbol determining what is happening in the scene.
		char characterName;		// The single-character representation of the NPC.
		string resourceName;	// Name of a resource to be sent out in an event.
		string eventName;		// Name of the event sent out (used to determine which character is performing the event).
		bool queueingPhase = false;

		fin >> numLines;
		fin.get();	// Ditch whitespace.

		while (!fin.eof())
		{
			// Reset our strings for resource or event names.
			resourceName = "";
			eventName = "";

			if (!queueingPhase)
			{
				symbol = fin.get();
				switch (symbol)
				{
				case '~':	// Background Texture
					{
						fin.get();	// Ditch whitespace.
						getline(fin, resourceName, '\n');
						CEventSystem::GetInstance()->SendEvent("texture.bg", (void*)resourceName.c_str());
						break;
					}
				case '#':	// Event
					{
						fin.get();	// Ditch whitespace.
						getline(fin, resourceName, '\n');
						CEventSystem::GetInstance()->SendEvent("game.event", (void*)resourceName.c_str());
						break;
					}

				case '!':	// Background Music
					{
						fin.get();	// Ditch whitespace.
						getline(fin, resourceName, '\n');
						CEventSystem::GetInstance()->SendEvent("sound.bg", (void*)resourceName.c_str());
						break;
					}

				case '*':	// SFX
					{
						fin.get();	// Ditch whitespace.
						getline(fin, resourceName, '\n');
						CEventSystem::GetInstance()->SendEvent("sound.sfx", (void*)resourceName.c_str());
						break;
					}

				case '@':	// Actor Texture Change
					{
						fin.get();	// Ditch whitespace.
						characterName = fin.get();	// Obtain the character name.
						fin.get();	// Ditch whitespace.
						eventName = "actor.texture.";
						eventName.append(1, characterName);
						getline(fin, resourceName, '\n');
						CEventSystem::GetInstance()->SendEvent(eventName, (void*)resourceName.c_str());
						break;
					}

				case ']':	// Actor Effect(Animations, i.e, bouncing, leaving, entering)
					{
						fin.get();	// Ditch whitespace.
						characterName = fin.get();	// Obtain the character name.
						fin.get();	// Ditch whitespace.
						eventName = "actor.texture.";
						eventName.append(1, characterName);
						getline(fin, resourceName, '\n');
						CEventSystem::GetInstance()->SendEvent(eventName, (void*)resourceName.c_str());
						break;
					}

				case '+':	// End initialization phase
					{
						queueingPhase = true;
						fin.get();
						break;
					}
					
				}
			}
			else
			{
				string temp = "";
				getline(fin, temp, '\n');
				if (temp != "")
					m_vLines.push_back(temp);
			}
		}

		fin.close();
		return 1;
	}
	return -1;
}

void CScriptingSystem::NextLine()
{
	if (m_nLinePos < m_vLines.size())
	{
		m_nLinePos += 1;
		ParseString();
	}
}

void CScriptingSystem::ChangeScript(string szFilename)
{
	ClearLines();
	ClearDecisions();
	LoadScriptText(szFilename);
}

void CScriptingSystem::ClearLines()
{
	m_vLines.clear();
}

void CScriptingSystem::ClearDecisions()
{
	for (unsigned int i = 0; i < m_vDecisions.size(); ++i)
	{
		if (m_vDecisions[i] != NULL)
		{
			delete m_vDecisions[i];
			m_vDecisions[i] = NULL;
		}
	}
	m_vDecisions.clear();
}

CScriptingSystem* CScriptingSystem::GetInstance()
{
	static CScriptingSystem instance;
	return &instance;
}

void CScriptingSystem::ParseString()
{
	int strPos = 0;		// Position in the temporary string (used for substr)
	const string temp = m_vLines[m_nLinePos];	// The string to parse through.
	string resourceName = "";	// Name of a resource to be sent out in an event.
	string eventName = "";		// Name of the event sent out (used to determine which character is performing the event).
	char characterName;			// The single-character representation of the NPC.
	char symbol = temp.front();	// The symbol determining what is happening in the scene.

	strPos +=2;	// Skip past the first symbol and the following whitespace.

	switch (symbol)
	{
		case '~':	// Background Texture
			{
				resourceName = temp.substr(strPos, temp.size() - strPos);
				CEventSystem::GetInstance()->SendEvent("texture.bg", (void*)resourceName.c_str());
				break;
			}
		case '#':	// Event
			{
				resourceName = temp.substr(strPos, temp.size() - strPos);
				CEventSystem::GetInstance()->SendEvent("game.event", (void*)resourceName.c_str());
				break;
			}

		case '!':	// Background Music
			{
				resourceName = temp.substr(strPos, temp.size() - strPos);
				CEventSystem::GetInstance()->SendEvent("sound.bg", (void*)resourceName.c_str());
				break;
			}

		case '*':	// SFX
			{
				resourceName = temp.substr(strPos, temp.size() - strPos);
				CEventSystem::GetInstance()->SendEvent("sound.sfx", (void*)resourceName.c_str());
				break;
			}

		case '@':	// Actor Texture Change
			{
				characterName = temp[strPos];	// Grab the character name.
				strPos +=2;	// Increase the string position by 2, skipping over whitespace in the process.
				eventName = "actor.texture.";
				eventName.append(1, characterName);
				resourceName = temp.substr(strPos, temp.size() - strPos);
				CEventSystem::GetInstance()->SendEvent(eventName, (void*)resourceName.c_str());
				break;
			}

		case ']':	// Actor Effect(Animations, i.e, bouncing, leaving, entering)
			{
				characterName = temp[strPos];	// Grab the character name.
				strPos += 2; // Increase the string position by 2, skipping over whitespace in the process.
				eventName = "actor.effect.";
				eventName.append(1, characterName);
				resourceName = temp.substr(strPos, temp.size() - strPos);
				CEventSystem::GetInstance()->SendEvent(eventName, (void*)resourceName.c_str());
				break;
			}

		case '-':	// Text
			{
				characterName = temp[strPos];	// Grab the cahracter name.
				strPos += 2;	// Increase the string position by 2, skipping over whitespace in the process.
				eventName = "text.";
				eventName.append(1, characterName);
				resourceName = temp.substr(strPos, temp.size() - strPos);
				CEventSystem::GetInstance()->SendEvent(eventName, (void*)resourceName.c_str());
				break;
			}

		case '|':	// Decision
			{
				CDecision* decision = new CDecision();
				int textLength = temp.find_last_of('\"') - strPos;
				string textToDisplay = temp.substr(strPos, textLength);
				strPos += textLength;
				resourceName = temp.substr(strPos, temp.size() - strPos);
				decision->SetTextToDisplay(textToDisplay);
				decision->SetFilename(resourceName);
				m_vDecisions.push_back(decision);
				break;
			}

		case '$':	// Script End
			{
				if (temp.size() == 2)
				{
					CEventSystem::GetInstance()->SendEvent("display.decisions");
				}
				else
				{
					strPos += 2;	// Increase the string position by 2, skipping over whitespace in the process.
					resourceName = temp.substr(strPos, temp.size() - strPos);
					CEventSystem::GetInstance()->SendEvent("load.script", (void*)resourceName.c_str());
				}
			}
	}
}