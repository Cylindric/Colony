#pragma once

#include <Windows.h>

namespace Core
{
	class Input
	{
	public:
		Input(void);
		~Input(void);

		bool Initialise(void);
		void Release(void);

	private:
		RAWINPUTDEVICE m_InputDevice[2];

	};
}