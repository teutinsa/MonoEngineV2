#pragma once
#include "Core.h"

class GameObject;

class Component abstract
{
	friend class GameObject;

public:
	/// <summary>
	/// Default constructor.
	/// </summary>
	Component(_In_ MonoClass* klass);
	virtual ~Component();

	/// <summary>
	/// Gets the hash code for the provided template type.
	/// </summary>
	/// <typeparam name="T">The type for witch to get the hash code from. Must be derived from Component class.</typeparam>
	/// <returns>The hash code of the type.</returns>
	template<typename T>
	static size_t MakeHash();
	/// <summary>
	/// Update
	/// </summary>
	virtual void Update();
	/// <summary>
	/// Render
	/// </summary>
	virtual void Render();
	/// <summary>
	/// Gets a hash value that is unique for this components type.
	/// </summary>
	virtual size_t GetHash() const abstract;
	/// <summary>
	/// Registers the internal calls in the managed runtime.
	/// </summary>
	static void RegisterIntCalls();
	/// <summary>
	/// Gets the managed object of this component.
	/// </summary>
	_Ret_notnull_ MonoObject* GetManagedObject() const;

private:
	MonoObject* m_managed;
	uint32_t m_handle;
	GameObject* m_gameObject;
};

class ScriptComponent : public Component
{
public:
	/// <summary>
	/// Default constructor.
	/// </summary>
	/// <param name="klass">The class of the script component.</param>
	ScriptComponent(_In_ MonoClass* klass);
	~ScriptComponent() override;

	/// <summary>
	/// Makes a unique hash code by combining the hash codes of the type id of the ScriptComponent and the type hash of the managed class.
	/// </summary>
	/// <param name="klass">The managed class.</param>
	/// <returns>A unique hash code.</returns>
	static size_t MakeHash(_In_ MonoClass* klass);
	/// <summary>
	/// Update
	/// </summary>
	virtual void Update() override;
	/// <summary>
	/// Gets a hash value that is unique for this components type.
	/// </summary>
	virtual size_t GetHash() const;
	/// <summary>
	/// Gets the managed type of this script component.
	/// </summary>
	_Ret_notnull_ MonoType* GetType() const;
	/// <summary>
	/// Registers the internal calls in the managed runtime.
	/// </summary>
	static void RegisterIntCalls();

private:
	MonoClass* m_class;
	MonoMethod* m_onCreateMethod;
	MonoMethod* m_onDestroyMethod;
	MonoMethod* m_onStartMethod;
	MonoMethod* m_onUpdateMethod;
	bool m_firstUpdate;

	void InvokeOnCreate();
	void InvokeOnDestroy();
	void InvokeOnStart();
	void InvokeOnUpdate();
};

template<typename T>
inline size_t Component::MakeHash()
{
	static_assert(std::is_base_of_v(Component, T),  "T must be derived from Component!");
	return typeid(T).hash_code();
}

