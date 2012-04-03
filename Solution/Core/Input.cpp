#include "Input.h"

namespace Core
{
	Input::Input()
	{
		ZeroMemory(&m_InputDevice, sizeof(RAWINPUTDEVICE));
	}


	Input::~Input()
	{
	}


	bool Input::Initialise()
	{
		return true;
	}


	void Input::Release()
	{
	}
}