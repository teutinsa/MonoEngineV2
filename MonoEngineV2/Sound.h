#pragma once
#include "Core.h"

class Window;

class Sound
{
public:
	/// <summary>
	/// Default constructor.
	/// </summary>
	/// <param name="wnd">A pointer to the main window.</param>
	Sound(Window* wnd);
	~Sound();

	/// <summary>
	/// Gets the current Sound instance 
	/// </summary>
	/// <returns>A pointer to the current Sound instance.</returns>
	static Sound* GetCurrent();

private:
	static Sound* s_current;
	Window* m_wnd;
	IDirectSound8* m_sound;
	IDirectSoundBuffer* m_mainBuffer;
};

