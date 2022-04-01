#pragma once
#include "Core.h"

class ILRuntime;
class Settings;
class Window;
class Renderer;
class Sound;
class Input;
class SceneManager;

struct StartupInfo;

class Application
{
public:
	/// <summary>
	/// Default constructor.
	/// </summary>
	Application();
	~Application();

	/// <summary>
	/// Gets the current Application instance. 
	/// </summary>
	/// <returns>A pointer to the current Application instance.</returns>
	_Success_(return != nullptr) static Application* GetCurrent();
	/// <summary>
	/// Runs the application.
	/// </summary>
	void Run();
	/// <summary>
	/// Orders the application to quit,
	/// </summary>
	void Quit();

private:
	static Application* s_current;
	MSG* m_msg;
	bool m_initialized;
	ILRuntime* m_runtime;
	Settings* m_settigs;
	Window* m_wnd;
	Renderer* m_renderer;
	Sound* m_sound;
	Input* m_input;
	SceneManager* m_scenes;
	StartupInfo* m_startupInfo;
	float m_deltaTime;

	/// <summary>
	/// Gets the current time in seconds.
	/// </summary>
	/// <returns>The current time in seconds.</returns>
	static constexpr float GetTime();
	/// <summary>
	/// Handles the queued window events.
	/// </summary>
	void DoEvents();
	/// <summary>
	/// Initializes all required data.
	/// </summary>
	void Init();
	/// <summary>
	/// Shuts down all initialized data.
	/// </summary>
	void Shut();
	/// <summary>
	/// Update
	/// </summary>
	void Update();
	/// <summary>
	/// Render
	/// </summary>
	void Render();
	/// <summary>
	/// Registers the internal calls in the managed runtime.
	/// </summary>
	void RegisterIntCalls();
	/// <summary>
	/// Parse the startup info, provided by the user.
	/// </summary>
	void ParseStartupData(_In_ MonoMethod* mth);

	//Internal calls
	static void Mono_Quit();
	static float Mono_get_DeltaTime();
};