#include "pch.h"
#include "Application.h"

#include "ILRuntime.h"
#include "Settings.h"
#include "Window.h"
#include "Renderer2D.h"
#include "SceneManager.h"

Application::Application()
	: m_runtime(nullptr), m_settigs(nullptr), m_wnd(nullptr), m_renderer(nullptr), m_scenes(nullptr)
{
	m_msg = T_CALLOC(MSG);
	m_initialized = false;
}

Application::~Application()
{
	Shut();

	T_FREE(m_msg);
}

_Success_(return != nullptr)
Application* Application::GetCurrent()
{
	return s_current;
}

void Application::Run()
{
	Init();

	float lastTime = GetTime();
	float currTime = 0.0f;
	float deltaTime = 0.0f;

	while (m_msg->message != WM_QUIT)
	{
		currTime = GetTime();
		deltaTime = currTime - lastTime;
		lastTime = currTime;

		DoEvents();

		Update();
		Render();

		m_runtime->GC();
	}

	Shut();
}

void Application::Quit()
{
	PostQuitMessage(0);
}

Application* Application::s_current;

constexpr float Application::GetTime()
{
	return std::chrono::duration<float>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

void Application::DoEvents()
{
	while (PeekMessageA(m_msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(m_msg);
		DispatchMessageA(m_msg);
	}
}

void Application::Init()
{
	if (m_initialized)
		return;

	m_runtime = new ILRuntime(PATH, "MonoEngine");
	m_runtime->LoadCoreLib();
	m_runtime->LoadEngineLib(PATH "\\MonoEngineV2Lib.dll");
	m_runtime->LoadUserLib(PATH "\\User-Assembly.dll");

	m_settigs = new Settings(PATH "\\Settings.dll");
	
	m_wnd = new Window();
	m_wnd->closeAction = WindowCloseAction::Quit;
	m_wnd->RemoveSyle(WS_THICKFRAME | WS_MAXIMIZEBOX);
	m_wnd->Show();

	m_renderer = new Renderer2D(m_wnd);

	m_scenes = new SceneManager();
	
	MonoMethod* mth = m_runtime->FetchUserEntryPoint();
	if (mth == nullptr)
		throw std::runtime_error("No entry point found in user assembly!");
	
	m_initialized = true;
}

void Application::Shut()
{
	if (!m_initialized)
		return;

	SafeDel(m_scenes);
	SafeDel(m_renderer);
	SafeDel(m_wnd);
	SafeDel(m_settigs);
	SafeDel(m_runtime);

	m_initialized = false;
}

void Application::Update()
{
	m_scenes->Update();
}

void Application::Render()
{
	m_renderer->Begin();

	m_scenes->Render();

	m_renderer->End();
}
