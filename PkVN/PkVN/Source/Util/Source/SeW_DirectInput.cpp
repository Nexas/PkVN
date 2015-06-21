#include "../Header/SeW_DirectInput.h"

//	MessageBox for Errors that occur within DirectInput.
#ifndef DIERRBOX
	#define DIERRBOX(hWnd, errorText)	{ MessageBox(hWnd, errorText, "CSeW_DirectInput Error", MB_OK | MB_ICONEXCLAMATION); }
#endif

CSeW_DirectInput CSeW_DirectInput::m_pInstance;

///////////////////////////////////////////////////////////////
// DIRECT INPUT FUNCTIONS
///////////////////////////////////////////////////////////////
CSeW_DirectInput::CSeW_DirectInput()
{
	m_lpDIObject	=	NULL;
	m_pcKeyboard	=	NULL;
	m_pcMouse		=	NULL;
}

CSeW_DirectInput::~CSeW_DirectInput()
{
	Shutdown();
}


CSeW_DirectInput* CSeW_DirectInput::GetInstance(void)
{
	return &m_pInstance;
}

bool CSeW_DirectInput::InitDirectInput(HWND hWnd, HINSTANCE hInstance, unsigned int initDevices, unsigned int exclusiveDevices)
{
	// Create the DirectInput Object.
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_lpDIObject, NULL)))
	{
		return false;
	}

	// Initialize the keyboard if the Keyboard flag is on.
	if (initDevices & DI_KEYBOARD)
	{
		if (!InitKeyboard(hWnd, (exclusiveDevices & DI_KEYBOARD) ? true : false))
			return false;
	}

	// Initialize the mouse if the mouse flag is on.
	if (initDevices & DI_MOUSE)
	{
		if (!InitMouse(hWnd, (exclusiveDevices & DI_MOUSE) ? true : false))
			return false;
	}

	// TODO: Initialize Joysticks if the joystick flag is on.
	if (initDevices & DI_JOYSTICKS)
	{
	}

	// If nothing broke at this point, success!
	return true;
}

void CSeW_DirectInput::Shutdown(void)
{
	UnacquireAll();

	if (m_pcKeyboard)
	{
		delete m_pcKeyboard;
		m_pcKeyboard = NULL;
	}

	if (m_pcMouse)
	{
		delete m_pcMouse;
		m_pcMouse = NULL;
	}

	// TODO: Safely delete all Joysticks.
}

void CSeW_DirectInput::ReadDevices(void)
{
	if (m_pcKeyboard)
	{
		m_pcKeyboard->ReadDevice();
		m_pcKeyboard->ReadBufferedDevice();
	}

	if (m_pcMouse)
	{
		m_pcMouse->ReadDevice();
		m_pcMouse->ReadBufferedDevice();
	}

	// TODO: Loop through and Read device data for all joysticks.
}

void CSeW_DirectInput::ClearInput(void)
{
	if (m_pcKeyboard)
	{
		m_pcKeyboard->ClearKeys();
	}

	if (m_pcMouse)
	{
		m_pcMouse->ClearMouseButtons();
	}

	// TODO: Loop through and clear all joystick buttons.

}

void CSeW_DirectInput::AcquireAll(void)
{
	if (m_pcKeyboard)
		m_pcKeyboard->Acquire();

	if (m_pcMouse)
		m_pcMouse->Acquire();

	// TODO: Loop through and acquire all joysticks.
}

void CSeW_DirectInput::UnacquireAll(void)
{
	if (m_pcKeyboard)
		m_pcKeyboard->Unacquire();

	if (m_pcMouse)
		m_pcMouse->Unacquire();

	// TODO: Loop through and unacquire all joysticks.
}

bool CSeW_DirectInput::InitKeyboard(HWND hWnd, bool bIsExclusive)
{
	// Make sure the keyboard hasn't already been initialized.
	if (m_pcKeyboard)
	{
		DIERRBOX(hWnd, "Keyboard has already been initialized.")
		return false;
	}

	m_pcKeyboard = new SeW_DIKeyboard(m_lpDIObject, hWnd, bIsExclusive);

	if (m_pcKeyboard == NULL)
		return false;

	return true;
}

bool CSeW_DirectInput::KeyDown(unsigned char KeyCode)
{
	return (m_pcKeyboard && m_pcKeyboard->KeyDown(KeyCode));
}

bool CSeW_DirectInput::KeyPressed(unsigned char KeyCode)
{
	return (m_pcKeyboard && m_pcKeyboard->KeyPressed(KeyCode));
}

bool CSeW_DirectInput::KeyPressedEx(unsigned char KeyCode)
{
	return (m_pcKeyboard && m_pcKeyboard->KeyPressedEx(KeyCode));
}

bool CSeW_DirectInput::KeyUp(unsigned char KeyCode)
{
	return (m_pcKeyboard && m_pcKeyboard->KeyUp(KeyCode));
}

bool CSeW_DirectInput::KeyReleased(unsigned char KeyCode)
{
	return (m_pcKeyboard && m_pcKeyboard->KeyReleased(KeyCode));
}

bool CSeW_DirectInput::KeyReleasedEx(unsigned char KeyCode)
{
	return (m_pcKeyboard && m_pcKeyboard->KeyReleasedEx(KeyCode));
}

char CSeW_DirectInput::CheckKeys(void)
{
	return (m_pcKeyboard) ? m_pcKeyboard->CheckKeys() : 0;
}

char CSeW_DirectInput::CheckBufferedKeysEx(void)
{
	return (m_pcKeyboard) ? m_pcKeyboard->CheckBufferedKeysEx() : 0;
}

unsigned char CSeW_DirectInput::GetKeyCode(void)
{
	return (m_pcKeyboard) ? m_pcKeyboard->GetKeyCode() : 0;
}

unsigned char CSeW_DirectInput::GetBufferedKeyCodeEx(void)
{
	return (m_pcKeyboard) ? m_pcKeyboard->GetBufferedKeyCode() : 0;
}

bool CSeW_DirectInput::InitMouse(HWND hWnd, bool bIsExclusive)
{
	// Make sure not to make a second mouse.
	if (m_pcMouse)
	{
		DIERRBOX(hWnd, "Mouse has already been initialized.")
		return false;
	}

	m_pcMouse = new SeW_DIMouse(m_lpDIObject, hWnd, bIsExclusive);

	if (m_pcMouse == NULL)
		return false;

	return true;
}

bool CSeW_DirectInput::MouseButtonDown(unsigned char button)
{
	return (m_pcMouse && m_pcMouse->ButtonDown(button));
}

bool CSeW_DirectInput::MouseButtonPressed(unsigned char button)
{
	return (m_pcMouse && m_pcMouse->ButtonPressed(button));
}

bool CSeW_DirectInput::MouseButtonPressedEx(unsigned char button)
{
	return (m_pcMouse && m_pcMouse->ButtonPressedEx(button));
}

bool CSeW_DirectInput::MouseButtonUp(unsigned char button)
{
	return (m_pcMouse && m_pcMouse->ButtonUp(button));
}

bool CSeW_DirectInput::MouseButtonReleased(unsigned char button)
{
	return (m_pcMouse && m_pcMouse->ButtonReleased(button));
}

bool CSeW_DirectInput::MouseButtonReleasedEx(unsigned char button)
{
	return (m_pcMouse && m_pcMouse->ButtonReleasedEx(button));
}

int CSeW_DirectInput::MouseCheckBufferedButtons(void)
{
	return (m_pcMouse) ? m_pcMouse->CheckBufferedButtons() : -1;
}

int CSeW_DirectInput::MouseCheckBufferedButtonsEx(void)
{
	return (m_pcMouse) ? m_pcMouse->CheckBufferedButtonsEx() : -1;
}

long CSeW_DirectInput::MouseMovementX(void)
{
	return (m_pcMouse) ? m_pcMouse->MovementX() : 0;
}

long CSeW_DirectInput::MouseMovementY(void)
{
	return (m_pcMouse) ? m_pcMouse->MovementY() : 0;
}

long CSeW_DirectInput::MouseWheelMovement(void)
{
	return (m_pcMouse) ? m_pcMouse->WheelMovement() : 0;
}

int CSeW_DirectInput::MouseGetNumButtons(void)
{
	return (m_pcMouse) ? m_pcMouse->GetNumButtons() : 0;
}

int CSeW_DirectInput::MouseGetPosX(void)
{
	return (m_pcMouse) ? m_pcMouse->GetPosX() : 0;
}

int CSeW_DirectInput::MouseGetPosY(void)
{
	return (m_pcMouse) ? m_pcMouse->GetPosY() : 0;
}

void CSeW_DirectInput::SetMousePosX(int posX)
{
	if (m_pcMouse)
		m_pcMouse->SetPosX(posX);
}

void CSeW_DirectInput::SetMousePosY(int posY)
{
	if (m_pcMouse)
		m_pcMouse->SetPosY(posY);
}

// TODO: Finish Joysticks
bool CSeW_DirectInput::InitJoysticks(HWND hWnd, bool bIsExclusive){return false; }

BOOL CALLBACK CSeW_DirectInput::EnumJoysticksCallback(const DIDEVICEINSTANCE* lpdidi, VOID* pVoid){ return false;}


///////////////////////////////////////////////////////////////
// KEYBOARD FUNCTIONS
///////////////////////////////////////////////////////////////
SeW_DIKeyboard::SeW_DIKeyboard(LPDIRECTINPUT8 pDi, HWND hWnd, bool bIsExclusive)
{
	// Create the Keyboard device.
	if (FAILED(pDi->CreateDevice(GUID_SysKeyboard, &m_lpDevice, NULL)))
	{
		DIERRBOX(hWnd, "Failed to create keyobard device.")
	}

	// Set the data format for the Keyboard.
	if (FAILED(m_lpDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		DIERRBOX(hWnd, "Failed to set data format on Keyboard.")
	}

	//	Set the Cooperative level for the keyboard.
	DWORD dwFlags = DISCL_FOREGROUND;

	if (bIsExclusive)
		dwFlags |= DISCL_EXCLUSIVE;
	else
		dwFlags |= DISCL_NONEXCLUSIVE | DISCL_NOWINKEY;

	if (FAILED( m_lpDevice->SetCooperativeLevel(hWnd, dwFlags) ))
	{
		DIERRBOX(hWnd, "Failed to set cooperative level on Keyboard.")
	}

	//	Set up the device to use buffered input
	//	For Use With Buffered Input.
	DIPROPDWORD dipdw;

	//	Clear the structure to all zeroes.
	memset(&dipdw, 0, sizeof(dipdw));

	dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj        = 0;
	dipdw.diph.dwHow        = DIPH_DEVICE;
	dipdw.dwData            = BUFFER_SIZE;	//	Arbitrary buffer size

	//	Set the buffer size on the device.
	if (FAILED( m_lpDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph) ))
		DIERRBOX(hWnd, "Properties for Buffered Input for Keyboard unable to be set.");

	//	Acquire the Keyboard.
	if (FAILED( m_lpDevice->Acquire() ))
	{
		DIERRBOX(hWnd, "Failed to acquire Keyboard.")
	}	

	ClearKeys();

	//	Get the Keyboard Layout.
	m_keyLayout = GetKeyboardLayout(0);
}

void SeW_DIKeyboard::ClearKeys(void)
{
	memset(m_ucKeysPressed, 0, 256 * sizeof(unsigned char));
	memset(m_ucPrevKeysPressed, 0, 256 * sizeof(unsigned char));
}

bool SeW_DIKeyboard::ReadDevice(void)
{
	// We can't do anything if the device isn't made.
	if (!m_lpDevice)
		return false;

	// Copy over previously pressed keys
	memcpy(m_ucPrevKeysPressed, m_ucKeysPressed, sizeof(m_ucKeysPressed));

	// Reading the Keyboard
	if (FAILED(m_lpDevice->GetDeviceState(sizeof(m_ucKeysPressed), (LPVOID)m_ucKeysPressed) ))
	{
		// If  we couldn't, we must acquire the Keyboard.
		if (FAILED(m_lpDevice->Acquire()))
			return false;	// Couldn't acquire the Keyboard.

		// Now we read the Keyboard.
		if (FAILED(m_lpDevice->GetDeviceState(sizeof(m_ucKeysPressed), (LPVOID)m_ucKeysPressed)))
			return false;
	}

	// Reading Successful.
	return true;
}

bool SeW_DIKeyboard::ReadBufferedDevice(void)
{
	// We can't do anything if the device isn't made.
	if (!m_lpDevice)
		return false;

	ClearBufferedData();

	// Let's try to read the device.
	if (FAILED(m_lpDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_DIObjData, &m_dwBufferElements, 0)))
	{
		// If we couldn't re must acquire the device.
		if (FAILED(m_lpDevice->Acquire()))
			return false;	// Failed to acquire the device.

		ClearBufferedData();

		// Now we'll try reading it again.
		if (FAILED(m_lpDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_DIObjData, &m_dwBufferElements, 0)))
			return false;
	}

	// Reading Successful.
	return true;
}

bool SeW_DIKeyboard::Acquire(void)
{
	ClearKeys();
	return SeW_DirectInputDevice::Acquire();
}

bool SeW_DIKeyboard::Unacquire(void)
{
	ClearKeys();
	return SeW_DirectInputDevice::Unacquire();
}

bool SeW_DIKeyboard::KeyDown(unsigned char key)
{
	return (m_ucKeysPressed[key] & 0x80) ? true : false;
}

bool SeW_DIKeyboard::KeyPressed(unsigned char key)
{
	return KeyDown(key) && !(m_ucPrevKeysPressed[key] & 0x80);
}

bool SeW_DIKeyboard::KeyPressedEx(unsigned char key)
{
	// Loop through the buffer.
	for (DWORD i = 0; i < m_dwBufferElements; ++i)
	{
		// If the offset matches and the high bit is on, it's pressed.
		if ((m_DIObjData[i].dwOfs == key) && (m_DIObjData[i].dwData & 0x80))
			return true;
	}
	// If not, it wasn't pressed.
	return false;
}

bool SeW_DIKeyboard::KeyUp(unsigned char key)
{
	return !KeyDown(key);
}

bool SeW_DIKeyboard::KeyReleased(unsigned char key)
{
	return KeyUp(key) && (m_ucPrevKeysPressed[key] & 0x80);
}

bool SeW_DIKeyboard::KeyReleasedEx(unsigned char key)
{
	// Loop through the buffer.
	for (DWORD i = 0; i < m_dwBufferElements; ++i)
	{
		// If the offset matches and the high bit is off, it's been released.
		if ((m_DIObjData[i].dwOfs == key) && !(m_DIObjData[i].dwData & 0x80))
			return true;
	}

	// If not, hasn't been released.
	return false;
}

char SeW_DIKeyboard::CheckKeys(void)
{
	// Get the Keyboard state.
	if (!GetKeyboardState(m_ucAsciiVals))
		return 0;	// We couldn't get the keyboard state.

	unsigned short Num = 0;
	unsigned int VKCode = 0;

	// Go through each keyboard key.
	for (int i = 0; i < 256; ++i)
	{
		// If the high bit is on, it's being pressed.
		if (KeyDown((unsigned char)i))
		{
			// Map the Scan code from DirectInput to a Virtual Key value.
			VKCode = MapVirtualKeyEx(i, 1, m_keyLayout);

			// Now translate the virtual Key into an Ascii value.
			ToAsciiEx(VKCode, i, m_ucAsciiVals, &Num, 0, m_keyLayout);
		}
	}

	// Return the Ascii value.
	return (char)Num;
}

char SeW_DIKeyboard::CheckBufferedKeysEx(void)
{
	//	Get the Keyboard State.
	if (!(GetKeyboardState(m_ucAsciiVals)))
		return 0; // We couldn't get the keyboard state.

	unsigned short Num	= 0;
	unsigned int VKCode	= 0;

	//	Loop through each element in the Buffer.
	for (DWORD i = 0; i < m_dwBufferElements; i++)
	{
		//	Loop through all keys on the keyboard
		for (unsigned int j = 0; j < 256; j++)
		{
			//	If the offset matches the key we are looking for and the high bit is on, it is pressed.
			if ((m_DIObjData[i].dwOfs == j) && (m_DIObjData[i].dwData & 0x80))
			{
				//	Map the Scan Code from DirectInput to a Virtual Key value...
				VKCode = MapVirtualKeyEx(m_DIObjData[i].dwOfs, 1, m_keyLayout);
				//	...and translate that Virtual Key into an Ascii Value.
				ToAsciiEx(VKCode, m_DIObjData[i].dwOfs, m_ucAsciiVals, &Num, 0, m_keyLayout);
			}
		}
	}

	//	Return the Ascii Value.
	return (char)Num;	
}

unsigned char SeW_DIKeyboard::GetKeyCode(void)
{
	unsigned char Num = 0;

	// Loop through each Keyboard key.
	for (int i = 0; i < 256; ++i)
	{
		// Fine the first one that is pressed.
		if (KeyDown((unsigned char)i))
		{
			Num = (unsigned char)i;
			break;
		}
	}

	// Return the Code.
	return Num;
}

unsigned char SeW_DIKeyboard::GetBufferedKeyCode(void)
{
	unsigned char Num = 0;

	//	Loop through each element in the Buffer.
	for (DWORD i = 0; i < m_dwBufferElements; i++)
	{
		//	Loop through all keys on the keyboard.
		for (unsigned int j = 0; j < 256; j++)
		{
			//	If the offset matches the key and the high bit is on, it is pressed.
			if ((m_DIObjData[i].dwOfs == j) && (m_DIObjData[i].dwData & 0x80))
			{
				Num = (unsigned char)j;
				break;
			}
		}
	}

	//	Return the Code.
	return Num;	
}

///////////////////////////////////////////////////////////////
// MOUSE FUNCTIONS
///////////////////////////////////////////////////////////////
SeW_DIMouse::SeW_DIMouse(LPDIRECTINPUT8 pDI, HWND hWnd, bool bIsExclusive)
{
	// Create the Mouse Device.
	if (FAILED(pDI->CreateDevice(GUID_SysMouse, &m_lpDevice, NULL)))
	{
		DIERRBOX(hWnd, "Failed to create Mouse Device.")
	}

	// Set the Data Format.
	if (FAILED(m_lpDevice->SetDataFormat(&c_dfDIMouse2)))
	{
		DIERRBOX(hWnd, "Failed to set data format for the Mouse.")
	}

	// Set the Cooperative Level.
	DWORD dwFlags = DISCL_FOREGROUND;

	if (bIsExclusive)
		dwFlags |= DISCL_EXCLUSIVE;
	else
		dwFlags |= DISCL_NONEXCLUSIVE;

	if (FAILED(m_lpDevice->SetCooperativeLevel(hWnd, dwFlags)))
	{
		DIERRBOX(hWnd, "Failed to set Cooperative Level on the Mouse.")
	}

	// Set up the device to use buffered input
	DIPROPDWORD dipdw;

	// Clear the Structure.
	memset(&dipdw, 0, sizeof(dipdw));

	dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj        = 0;
	dipdw.diph.dwHow        = DIPH_DEVICE;
	dipdw.dwData            = BUFFER_SIZE;	//	Arbitrary buffer size

	// Set the buffer size.
	if (FAILED(m_lpDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph)))
	{
		DIERRBOX(hWnd, "Could not set the Properties for Buffered Input for Mouse.")
	}

	// Acquire the Mouse.
	if (FAILED(m_lpDevice->Acquire()))
	{
		DIERRBOX(hWnd, "Could not Acquire the Mouse.")
	}

	DIDEVCAPS didCaps;

	// Clear out the Structure.
	memset(&didCaps, 0, sizeof(didCaps));
	didCaps.dwSize = sizeof(didCaps);

	m_lpDevice->GetCapabilities(&didCaps);
	{
		if (didCaps.dwFlags & DIDC_POLLEDDATAFORMAT)
			int y = 4;
		if (didCaps.dwFlags & DIDC_POLLEDDEVICE)
			int y = 5;
	}

	// Will be zero if failed because the struct was cleared out.
	m_nNumButtons = didCaps.dwButtons;

	// Clear out current state.
	memset(&m_diMouseState, 0, sizeof(m_diMouseState));

	// Clear out the previous state.
	memset(&m_diPrevMouseState, 0, sizeof(m_diPrevMouseState));

	// Set Psuedo position of mouse.
	SetPosX(0);
	SetPosY(0);
}

void SeW_DIMouse::ClearMouseButtons(void)
{
	// Clear the current and previously pressed buttons
	memset(m_diMouseState.rgbButtons, 0, 8 * sizeof(BYTE));

	memset(m_diPrevMouseState.rgbButtons, 0, 8 * sizeof(BYTE));
}

bool SeW_DIMouse::ReadDevice(void)
{
	// We can't do anything if the device isn't made.
	if (!m_lpDevice)
		return false;

	// Remember our previous state.
	memcpy(& m_diPrevMouseState, &m_diMouseState, sizeof(m_diPrevMouseState));

	// Attempt to read the mouse.
	if (FAILED(m_lpDevice->GetDeviceState(sizeof(m_diMouseState), (LPVOID)&m_diMouseState)))
	{
		// If not, attempt to re-acquire.
		if (FAILED(m_lpDevice->Acquire()))
			return false;	// Failed to re-acquire.

		// Now try to read it again.
		if (FAILED(m_lpDevice->GetDeviceState(sizeof(m_diMouseState), (LPVOID)&m_diMouseState)))
			return false;
	}

	// Update "psuedo" position of mouse.
	SetPosX(GetPosX() + MovementX());
	SetPosY(GetPosY() + MovementY());

	// We are successful!
	return true;
}

bool SeW_DIMouse::ReadBufferedDevice(void)
{
	// We can't do anything if the device isn't made.
	if (!m_lpDevice)
		return false;

	ClearBufferedData();

	// Attempt to read the Device.
	if (FAILED(m_lpDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_DIObjData, &m_dwBufferElements, 0)))
	{
		// If not, attempt to re-acquire.
		if (FAILED(m_lpDevice->Acquire()))
		{
			return false;
		}

		ClearBufferedData();

		// Now try reading it again.
		if (FAILED(m_lpDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_DIObjData, &m_dwBufferElements, 0)))
		{
			return false;
		}
	}

	// We are successful!
	return true;
}

bool SeW_DIMouse::ButtonDown(unsigned char button)
{
	// If the high bit is on, it's pressed.
	return (m_diMouseState.rgbButtons[button] & 0x80) ? true : false;
}

bool SeW_DIMouse::ButtonPressed(unsigned char button)
{
	// If the button is down currently and wasn't pressed previously.
	return ButtonDown(button) && !(m_diPrevMouseState.rgbButtons[button] & 0x80);
}

bool SeW_DIMouse::ButtonPressedEx(unsigned char button)
{
	//	Loop through each element in the Buffer.
	for (DWORD i = 0; i < m_dwBufferElements; i++)
	{
		//	If the offset matches and the high bit is on, it is pressed.
		if ((m_DIObjData[i].dwOfs == (DWORD)(DIMOFS_BUTTON0 + button)) && (m_DIObjData[i].dwData & 0x80))
			return true;
	}

	//	wasn't pressed.
	return false;
}

bool SeW_DIMouse::ButtonUp(unsigned char button)
{
	// If the high bit is off, it's not pressed.
	return !ButtonDown(button);
}

bool SeW_DIMouse::ButtonReleased(unsigned char button)
{
	// If the button is up and was pressed previously.
	return ButtonUp(button) && (m_diPrevMouseState.rgbButtons[button] & 0x80);
}

bool SeW_DIMouse::ButtonReleasedEx(unsigned char button)
{
	//	Loop through each element in the Buffer.
	for (DWORD i = 0; i < m_dwBufferElements; i++)
	{
		//	If the offset matches  and the high bit is off, it was released.
		if ((m_DIObjData[i].dwOfs == (DWORD)(DIMOFS_BUTTON0 + button)) && !(m_DIObjData[i].dwData & 0x80))
			return true;
	}

	//	wasn't pressed.
	return false;
}

int SeW_DIMouse::CheckBufferedButtons(void)
{
	int Button = -1;

	//	Loop through all mouse buttons.
	for (int j = 0; j < GetNumButtons(); j++)
	{
		//	Find the first button that was pressed
		if (ButtonPressed(j))
		{
			//	Return the first one that was found to be pressed.
			Button = j;
			break;
		}
	}

	//	return the button.
	return Button;
}

int SeW_DIMouse::CheckBufferedButtonsEx(void)
{
	int Button = -1;

	//	Loop through each element in the Buffer.
	for (DWORD i = 0; i < m_dwBufferElements; i++)
	{
		//	Loop through all mouse buttons.
		for (int j = 0; j < GetNumButtons(); j++)
		{
			//	If the offset matches and the high bit is on, it is pressed.
			if ((m_DIObjData[i].dwOfs == (DWORD)(DIMOFS_BUTTON0 + j)) && (m_DIObjData[i].dwData & 0x80))
			{
				//	Return the first one that was found to be pressed.
				Button = j;
				break;
			}
		}
	}

	//	return the button.
	return Button;
}

long SeW_DIMouse::MovementX(void)
{
	return m_diMouseState.lX;
}

long SeW_DIMouse::MovementY(void)
{
	return m_diMouseState.lY;
}

long SeW_DIMouse::WheelMovement(void)
{
	return m_diMouseState.lZ;
}

int SeW_DIMouse::GetNumButtons(void)
{
	return m_nNumButtons;
}

int SeW_DIMouse::GetPosX(void)
{
	return m_nPosX;
}

int SeW_DIMouse::GetPosY(void)
{
	return m_nPosY;
}

void SeW_DIMouse::SetPosX(int posX)
{
	m_nPosX = posX;
}

void SeW_DIMouse::SetPosY(int posY)
{
	m_nPosY = posY;
}


///////////////////////////////////////////////////////////////
// JOYSTICK FUNCTIONS
///////////////////////////////////////////////////////////////


