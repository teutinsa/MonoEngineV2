#include "pch.h"
#include "Scene.h"

#include "Renderer.h"
#include "Renderer2D.h"
#include "ILRuntime.h"

Scene::Scene(_In_ const std::string& name)
	: m_name(name), m_clearColor(0.0f, 0.0f, 0.0f)
{
	static MonoClass* sceneCl;
	if (sceneCl == nullptr)
		sceneCl = ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Scene");
	
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");
	
	m_managed = ILRuntime::GetCurrent()->New(sceneCl);
	m_handle = mono_gchandle_new(m_managed, false);

	void* ptr = this;
	mono_field_set_value(m_managed, nativeFld, &ptr);
}

Scene::~Scene()
{
	for (GameObject* obj : m_objects)
		delete obj;

	mono_gchandle_free(m_handle);
}

std::string Scene::GetName() const
{
	return m_name;
}

void Scene::Update()
{
	for (GameObject* obj : m_objects)
		if(obj->GetActive())
			obj->Update();
}

void Scene::Render()
{
	Renderer* r = Renderer::GetCurrent();
	if (r->GetRenderType() == RenderType::D2D)
		reinterpret_cast<Renderer2D*>(r)->GetTarget()->Clear(m_clearColor);

	ID2D1RenderTarget* t = ((Renderer2D*)r->GetCurrent())->GetTarget();
	
	for (GameObject* obj : m_objects)
		if (obj->GetActive())
		{
			D2D1_MATRIX_3X2_F m;
			t->GetTransform(&m);
			t->SetTransform(m * obj->transform->GetMatrix());
			
			obj->transform->GetMatrix();
			obj->Render();

			t->SetTransform(m);
		}
}

_Success_(return != nullptr) _Check_return_
GameObject* Scene::CreateObject(_In_ const std::string& name)
{
	GameObject* obj = new GameObject(name);
	obj->m_scene = this;
	m_objects.push_back(obj);
	return obj;
}

void Scene::DestroyObject(_In_opt_ GameObject* obj)
{
	if (obj == nullptr)
		return;

	for (auto it = m_objects.cbegin(); it != m_objects.cend(); it++)
		if (*it == obj)
		{
			m_objects.erase(it);
			obj->m_scene = nullptr;
			delete obj;
			return;
		}
}

_Success_(return != nullptr) _Check_return_
GameObject* Scene::FindObjectByName(_In_ const std::string& name) const
{
	for (GameObject* obj : m_objects)
		if (obj->GetName() == name)
			return obj;
	return nullptr;
}

void Scene::SetClearColor(_In_ const ColorF& value)
{
	m_clearColor = value;
}

ColorF Scene::GetClearColor() const
{
	return m_clearColor;
}

_Ret_notnull_
MonoObject* Scene::GetManagedObject() const
{
	return m_managed;
}

void Scene::RegisterIntCalls()
{
	ILRuntime::RegIntCall("MonoEngineV2Lib.Scene::get_Name", Mono_get_Name);
	ILRuntime::RegIntCall("MonoEngineV2Lib.Scene::get_ClearColor", Mono_get_ClearColor);
	ILRuntime::RegIntCall("MonoEngineV2Lib.Scene::set_ClearColor", Mono_set_ClearColor);
	ILRuntime::RegIntCall("MonoEngineV2Lib.Scene::get_ResourceManager", Mono_get_ResourceManager);
	ILRuntime::RegIntCall("MonoEngineV2Lib.Scene::CreateObject", Mono_CreateObject);
	ILRuntime::RegIntCall("MonoEngineV2Lib.Scene::FindObjectByName", Mono_FindObjectByName);
	ILRuntime::RegIntCall("MonoEngineV2Lib.Scene::DestroyObject", Mono_DestroyObject);

	ResourceManager::RegisterIntCalls();
	GameObject::RegisterIntCalls();
}

MonoString* Scene::Mono_get_Name(MonoObject* obj)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	Scene* scene = nullptr;
	mono_field_get_value(obj, nativeFld, &scene);

	return mono_string_new_wrapper(scene->m_name.c_str());
}

ColorF Scene::Mono_get_ClearColor(MonoObject* obj)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	Scene* scene = nullptr;
	mono_field_get_value(obj, nativeFld, &scene);

	return scene->m_clearColor;
}

void Scene::Mono_set_ClearColor(MonoObject* obj, ColorF* value)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	Scene* scene = nullptr;
	mono_field_get_value(obj, nativeFld, &scene);

	scene->m_clearColor = *value;
}

MonoObject* Scene::Mono_get_ResourceManager(MonoObject* obj)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	Scene* scene = nullptr;
	mono_field_get_value(obj, nativeFld, &scene);

	return scene->m_resources.GetManagedObject();
}

MonoObject* Scene::Mono_CreateObject(MonoObject* obj, MonoString* name)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	Scene* scene = nullptr;
	mono_field_get_value(obj, nativeFld, &scene);
	
	return scene->CreateObject(mono_string_to_utf8(name))->GetManagedObject();
}

MonoObject* Scene::Mono_FindObjectByName(MonoObject* obj, MonoString* name)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	Scene* scene = nullptr;
	mono_field_get_value(obj, nativeFld, &scene);

	return scene->FindObjectByName(mono_string_to_utf8(name))->GetManagedObject();
}

void Scene::Mono_DestroyObject(MonoObject* obj, MonoObject* object)
{
	static MonoClassField* nativeFld;
	if (nativeFld == nullptr)
		nativeFld = mono_class_get_field_from_name(ILRuntime::GetCurrent()->GetLibClasByName("MonoEngineV2Lib", "Object"), "m_native");

	Scene* scene = nullptr;
	mono_field_get_value(obj, nativeFld, &scene);

	GameObject* go = nullptr;
	mono_field_get_value(object, nativeFld, &go);

	scene->DestroyObject(go);
}
