/*****************************************************************
*		File: SeW_DirectInput.h
*
*		Author: Sean Welch
*
*		Purpose: To utilize and provide a wrapper for DirectInput.
*
*		Date Modified:		4/19/2015
*****************************************************************/
#ifndef SEW_DIRECTINPUT_H_
#define SEW_DIRECTINPUT_H_

#pragma once

//	The version of DirectInput to use.
#ifndef DIRECTINPUT_VERSION
	#define DIRECTINPUT_VERSION 0X800
#endif
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class SeW_DIKeyboard;
class SeW_DIMouse;

// Enums:
enum DeviceFlags { DI_KEYBOARD = 1, DI_MOUSE = 2, DI_JOYSTICKS = 4 };

enum Directions { DIR_LEFT = 0, DIR_RIGHT = 1, DIR_UP = 2, DIR_DOWN = 3, DIR_MAX };

enum MouseButtons { MOUSE_LEFT = 0, MOUSE_RIGHT = 1, MOUSE_MIDDLE = 2, MOUSE_MAX };

class CSeW_DirectInput
{
	LPDIRECTINPUT8 m_lpDIObject;
	SeW_DIKeyboard* m_pcKeyboard;
	SeW_DIMouse* m_pcMouse;

	struct setupInfo
	{
		HWND hWnd;
		bool bIsExclusive;
	};

	static CSeW_DirectInput m_pInstance;
	CSeW_DirectInput();
	~CSeW_DirectInput();
	CSeW_DirectInput(const CSeW_DirectInput& obj);
	CSeW_DirectInput& operator=(const CSeW_DirectInput& obj);

public:

	bool InitKeyboard(HWND hWnd, bool bIsExclusive = false);
	bool InitMouse(HWND hWnd, bool bIsExclusive = false);
	// TODO: Finish Joysticks
	bool InitJoysticks(HWND hWnd, bool bIsExclusive = false);
	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* lpdidi, VOID* pVoid);
	static CSeW_DirectInput* GetInstance(void);
	bool InitDirectInput(HWND hWnd, HINSTANCE hInstance, unsigned int initDevices, unsigned int exclusiveDevices = 0);
	void Shutdown(void);
	void ReadDevices(void);
	void ClearInput(void);
	void AcquireAll(void);
	void UnacquireAll(void);
	bool KeyDown(unsigned char KeyCode);
	bool KeyPressed(unsigned char KeyCode);
	bool KeyPressedEx(unsigned char KeyCode);
	bool KeyUp(unsigned char KeyCode);
	bool KeyReleased(unsigned char KeyCode);
	bool KeyReleasedEx(unsigned char KeyCode);
	char CheckKeys(void);
	char CheckBufferedKeysEx(void);
	unsigned char GetKeyCode(void);
	unsigned char GetBufferedKeyCodeEx(void);
	bool MouseButtonDown(unsigned char button);
	bool MouseButtonPressed(unsigned char button);
	bool MouseButtonPressedEx(unsigned char button);
	bool MouseButtonUp(unsigned char button);
	bool MouseButtonReleased(unsigned char button);
	bool MouseButtonReleasedEx(unsigned char button);
	int MouseCheckBufferedButtons(void);
	int MouseCheckBufferedButtonsEx(void);
	long MouseMovementX(void);
	long MouseMovementY(void);
	long MouseWheelMovement(void);
	int MouseGetNumButtons(void);
	int MouseGetPosX(void);
	int MouseGetPosY(void);
	void SetMousePosX(int posX);
	void SetMousePosY(int posY);

};


const int BUFFER_SIZE = 10;	//	Arbitrary number of elements for Buffered Input.

class ISeW_DirectInputDevice
{
public:
	virtual ~ISeW_DirectInputDevice(void) = 0 {};
	virtual bool ReadDevice(void) = 0;
	virtual bool ReadBufferedDevice(void) = 0;
	virtual bool Acquire(void) = 0;
	virtual bool Unacquire(void) = 0;
};

class SeW_DirectInputDevice : public ISeW_DirectInputDevice
{
protected:
	LPDIRECTINPUTDEVICE8	m_lpDevice;
	DIDEVICEOBJECTDATA		m_DIObjData[BUFFER_SIZE];
	DWORD					m_dwBufferElements;

	void ClearBufferedData(void)
	{
		memset(&m_DIObjData, 0, sizeof(m_DIObjData));
		m_dwBufferElements = BUFFER_SIZE;
	}

public:

	SeW_DirectInputDevice()
	{
		m_lpDevice = NULL;

		ClearBufferedData();
	}
	
	virtual ~SeW_DirectInputDevice()
	{
		if (m_lpDevice)
		{
			m_lpDevice->Unacquire();
			m_lpDevice->Release();
			m_lpDevice = NULL;
		}
	}

	virtual bool ReadBufferedDevice(void)
	{
		if (!m_lpDevice)
			return false;

		ClearBufferedData();

		// Try to read the device
		if (FAILED(m_lpDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_DIObjData, &m_dwBufferElements, 0)))
		{
			// If something goes wrong, we must attempt to reacquire
			if (FAILED(m_lpDevice->Acquire()))
				return false;

			ClearBufferedData();

			// And now we read the device!
			if (FAILED(m_lpDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_DIObjData, &m_dwBufferElements, 0)))
				return false;
		}
		
		return true;
	}


	virtual bool Acquire(void) {return m_lpDevice ? SUCCEEDED(m_lpDevice->Acquire()) : false;}
	virtual bool Unacquire(void) {return m_lpDevice ? SUCCEEDED(m_lpDevice->Unacquire()) : false;}
};

class SeW_DIKeyboard : public SeW_DirectInputDevice
{
	unsigned char		m_ucKeysPressed[256];			//	Holds Keyboard Data.
	unsigned char		m_ucPrevKeysPressed[256];		//	Used for BufferedKeyEx.

	unsigned char		m_ucAsciiVals[256];		
	HKL					m_keyLayout;			

public:

	SeW_DIKeyboard(LPDIRECTINPUT8 pDi, HWND hWnd, bool bIsExclusive = false);
	void ClearKeys(void);
	bool ReadDevice(void);
	bool ReadBufferedDevice(void);
	bool Acquire(void);
	bool Unacquire(void);
	bool KeyDown(unsigned char key);
	bool KeyPressed(unsigned char key);
	bool KeyPressedEx(unsigned char key);
	bool KeyUp(unsigned char key);
	bool KeyReleased(unsigned char key);
	bool KeyReleasedEx(unsigned char key);
	char CheckKeys(void);
	char CheckBufferedKeysEx(void);
	unsigned char GetKeyCode(void);
	unsigned char GetBufferedKeyCode(void);


};

class SeW_DIMouse : public SeW_DirectInputDevice
{
	DIMOUSESTATE2 m_diMouseState;
	DIMOUSESTATE2 m_diPrevMouseState;
	int m_nNumButtons;
	int m_nPosX;
	int m_nPosY;

public:

	SeW_DIMouse(LPDIRECTINPUT8 pDI, HWND hWnd, bool bIsExclusive = false);
	void ClearMouseButtons(void);
	bool ReadDevice(void);
	bool ReadBufferedDevice(void);
	bool ButtonDown(unsigned char button);
	bool ButtonPressed(unsigned char button);
	bool ButtonPressedEx(unsigned char button);
	bool ButtonUp(unsigned char button);
	bool ButtonReleased(unsigned char button);
	bool ButtonReleasedEx(unsigned char button);
	int CheckBufferedButtons(void);
	int CheckBufferedButtonsEx(void);
	long MovementX(void);
	long MovementY(void);
	long WheelMovement(void);
	int GetNumButtons(void);
	int GetPosX(void);
	int GetPosY(void);
	void SetPosX(int posX);
	void SetPosY(int posY);

};

/////////////////////////////////////////////////////////////////////////////////////////
//		Function:
//
//		Purpose:		An interface class for all DirectInput Devices.
//
//		Date Modified:		4/19/2015
//
//		Input:		
//
//		Returns:		
/////////////////////////////////////////////////////////////////////////////////////////










#endif /*SEW_DIRECTINPUT_H_*/
