#include "pch.h"
#include "Sound.h"

#include "Window.h"

Sound::Sound(Window* wnd)
	: m_wnd(wnd)
{
	s_current = this;

	ThrowOnFail(DirectSoundCreate8(nullptr, &m_sound, nullptr), "Sound device creation failed!");
	m_sound->SetCooperativeLevel(wnd->GetHandle(), DSSCL_PRIORITY);

	DSBUFFERDESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.dwSize = sizeof(desc);
	desc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	desc.guid3DAlgorithm = GUID_NULL;

	ThrowOnFail(m_sound->CreateSoundBuffer(&desc, &m_mainBuffer, nullptr), "Primary sound buffer creation failed!");

	WAVEFORMATEX waveFormat;
	ZeroMemory(&waveFormat, sizeof(waveFormat));
	waveFormat.cbSize = sizeof(waveFormat);
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;

	ThrowOnFail(m_mainBuffer->SetFormat(&waveFormat), "Formating of primary sound buffer failed!");
}

Sound::~Sound()
{
	SafeRelease(m_mainBuffer);
	SafeRelease(m_sound);
}

Sound* Sound::GetCurrent()
{
	return s_current;
}

Sound* Sound::s_current;