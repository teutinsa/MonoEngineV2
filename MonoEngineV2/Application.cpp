#include "pch.h"
#include "Application.h"

#include "ILRuntime.h"
#include "Settings.h"
#include "Window.h"
#include "Renderer2D.h"
#include "Sound.h"
#include "Input.h"
#include "SceneManager.h"
#include "ObjectHandle.h"

struct StartupInfo
{
	int startSceneIndex;
	std::string appName;
	BufferType bufferType;
	CoordinateMode coordinateMode;
	Vector2Int customBufferSize;
	std::vector<ObjectHandle> sceneDefinitions;
};

Application::Application()
	: m_runtime(nullptr), m_settigs(nullptr), m_wnd(nullptr), m_renderer(nullptr), m_scenes(nullptr), m_input(nullptr), m_sound(nullptr), m_startupInfo(nullptr)
{
	m_msg = T_CALLOC(MSG);
	m_initialized = false;

	s_current = this;
}

Application::~Application()
{
	Shut();

	T_FREE(m_startupInfo);
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
	m_deltaTime = 0.0f;
	float frameTime = 0.0f;
	unsigned frames = 0;

	while (m_msg->message != WM_QUIT)
	{
		currTime = GetTime();
		m_deltaTime = currTime - lastTime;
		lastTime = currTime;

		if (frameTime >= 1.0f)
		{
			DebugOut("FPS: %u\n", frames);
			frameTime = 0.0f;
			frames = 0;
		}
		else
		{
			frameTime += m_deltaTime;
			frames++;
		}

		DoEvents();
		
		m_input->Update();

		Update();
		Render();

		//m_runtime->GC();
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

	m_sound = new Sound(m_wnd);

	m_input = new Input();

	m_scenes = new SceneManager();

	MonoMethod* mth = m_runtime->FetchUserEntryPoint();
	if (mth == nullptr)
		throw std::runtime_error("No entry point found in user assembly!");

	RegisterIntCalls();

	ParseStartupData(mth);

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

void Application::RegisterIntCalls()
{
	ILRuntime::RegIntCall("MonoEngineV2Lib.Application::Quit", Mono_Quit);
	ILRuntime::RegIntCall("MonoEngineV2Lib.Time::get_DeltaTime", Mono_get_DeltaTime);

	Input::RegisterIntCalls();
	SceneManager::RegisterIntCalls();
}

void Application::ParseStartupData(_In_ MonoMethod* mth)
{
	MonoObject* startupDataObj;
	ThrowOnExc(m_runtime->Invoke(mth, nullptr, nullptr, &startupDataObj)); //Call entry point

	static MonoClass* startupDataCl;
	if (startupDataCl == nullptr)
		startupDataCl = m_runtime->GetLibClasByName("MonoEngineV2Lib", "StartupData");
	static MonoMethod* startSceneIndexGetMeth;
	if (startSceneIndexGetMeth == nullptr)
		startSceneIndexGetMeth = mono_property_get_get_method(mono_class_get_property_from_name(startupDataCl, "StartSceneIndex"));
	static MonoMethod* appNameGetMeth;
	if (appNameGetMeth == nullptr)
		appNameGetMeth = mono_property_get_get_method(mono_class_get_property_from_name(startupDataCl, "ApplicationName"));
	static MonoMethod* bufTypeGetMeth;
	if (bufTypeGetMeth == nullptr)
		bufTypeGetMeth = mono_property_get_get_method(mono_class_get_property_from_name(startupDataCl, "BufferType"));
	static MonoMethod* coordModeGetMeth;
	if (coordModeGetMeth == nullptr)
		coordModeGetMeth = mono_property_get_get_method(mono_class_get_property_from_name(startupDataCl, "CoordinateMode"));
	static MonoMethod* custBufSizGetMeth;
	if (custBufSizGetMeth == nullptr)
		custBufSizGetMeth = mono_property_get_get_method(mono_class_get_property_from_name(startupDataCl, "CustomBufferSize"));
	static MonoClassField* sceneDefFld;
	if (sceneDefFld == nullptr)
		sceneDefFld = mono_class_get_field_from_name(startupDataCl, "m_sceneDefinitions");

	m_startupInfo = T_CALLOC(StartupInfo);

	MonoObject* startSceneIndexObj;
	ThrowOnExc(m_runtime->Invoke(startSceneIndexGetMeth, startupDataObj, nullptr, &startSceneIndexObj));
	m_startupInfo->startSceneIndex = *(int*)mono_object_unbox(startSceneIndexObj);
	
	MonoString* appNameStr;
	ThrowOnExc(m_runtime->Invoke(appNameGetMeth, startupDataObj, nullptr, (MonoObject**)&appNameStr));
	m_startupInfo->appName = std::string(mono_string_to_utf8(appNameStr));
	
	MonoObject* bufTypeObj;
	ThrowOnExc(m_runtime->Invoke(bufTypeGetMeth, startupDataObj, nullptr, &bufTypeObj));
	m_startupInfo->bufferType = *(BufferType*)mono_object_unbox(bufTypeObj);
	
	MonoObject* coordModeObj;
	ThrowOnExc(m_runtime->Invoke(coordModeGetMeth, startupDataObj, nullptr, &coordModeObj));
	m_startupInfo->coordinateMode = *(CoordinateMode*)mono_object_unbox(coordModeObj);

	MonoObject* custBufSizeObj;
	ThrowOnExc(m_runtime->Invoke(custBufSizGetMeth, startupDataObj, nullptr, &custBufSizeObj));
	m_startupInfo->customBufferSize = *(Vector2Int*)mono_object_unbox(custBufSizeObj);

	MonoArray* sceneDefArr;
	mono_field_get_value(startupDataObj, sceneDefFld, &sceneDefArr);
	uintptr_t sceneDefLen = mono_array_length(sceneDefArr);
	m_startupInfo->sceneDefinitions = std::vector<ObjectHandle>();
	for (size_t i = 0; i < sceneDefLen; i++)
	{
		MonoDelegate* sceneDefDel = mono_array_get(sceneDefArr, MonoDelegate*, i);
		m_startupInfo->sceneDefinitions.push_back(ObjectHandle((MonoObject*)sceneDefDel));
	}

	//apply startup info
	m_wnd->SetText(m_startupInfo->appName.c_str());
	m_renderer->SetCoordinateMode(m_startupInfo->coordinateMode);
	m_renderer->SetBufferType(m_startupInfo->bufferType);
	m_renderer->SetPixelSize(m_startupInfo->customBufferSize);
	m_scenes->SetSceneDefs(&m_startupInfo->sceneDefinitions);

	m_scenes->LoadScene(m_startupInfo->startSceneIndex);
}

void Application::Mono_Quit()
{
	Application::GetCurrent()->Quit();
}

float Application::Mono_get_DeltaTime()
{
	return Application::GetCurrent()->m_deltaTime;
}
