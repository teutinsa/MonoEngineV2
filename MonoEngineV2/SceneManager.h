#pragma once
#include "Core.h"

#include "Scene.h"
#include "ObjectHandle.h"

class SceneManager
{
public:
	/// <summary>
	/// Default constructor.
	/// </summary>
	SceneManager();
	~SceneManager();

	/// <summary>
	/// Gets the current SceneManager instance.
	/// </summary>
	/// <returns>A pointer to the current SceneManager instance.</returns>
	_Success_(return != nullptr) static SceneManager* GetCurrent();
	/// <summary>
	/// Gets the current scene.
	/// </summary>
	/// <returns>A pointer to the current scene.</returns>
	_Ret_maybenull_ Scene* GetCurrentScene() const;
	/// <summary>
	/// Creates a new scene with the given name. If the name if already in use no scene will be created.
	/// </summary>
	/// <param name="name">The name of the new scene.</param>
	/// <returns>A pointer to the newly created scene, null if the name if already in use.</returns>
	_Success_(return != nullptr) _Check_return_ Scene* CreateScene(_In_ const std::string& name);
	/// <summary>
	/// Checks if a scene with a given name exists.
	/// </summary>
	/// <param name="name">The name to search for.</param>
	/// <returns>True if a scene with the given name exists, otherwise false.</returns>
	bool SceneWithNameExists(_In_ const std::string& name) const;
	/// <summary>
	/// Gets a scene with a given name if it exists.
	/// </summary>
	/// <param name="name">The name to search for.</param>
	/// <returns>A pointer to the found scene, otherwise null.</returns>
	_Success_(return != nullptr) _Check_return_ Scene* GetSceneByName(_In_ const std::string& name) const;
	/// <summary>
	/// Sets a given scene as the current scene.
	/// </summary>
	/// <param name="scene">The target scene.</param>
	void SetCurrentScene(_In_ Scene* scene);
	/// <summary>
	/// Destroys a given scene.
	/// </summary>
	/// <param name="scene">A pointer to the scene to be detroyed.</param>
	void DestroyScene(_In_ Scene* scene);
	/// <summary>
	/// Update
	/// </summary>
	void Update();
	/// <summary>
	/// Render
	/// </summary>
	void Render();
	/// <summary>
	/// Sets the scene definitions of the scene manager.
	/// </summary>
	void SetSceneDefs(_In_ const std::vector<ObjectHandle>* sceneDefs);
	/// <summary>
	/// Loads a scene from the definitions at a given index.
	/// </summary>
	/// <param name="index">The index in the definitions.</param>
	void LoadScene(_In_ int index);
	/// <summary>
	/// Registers the internal calls in the managed runtime.
	/// </summary>
	static void RegisterIntCalls();

private:
	static SceneManager* s_current;
	Scene* m_currentScene;
	std::vector<Scene*> m_scenes;
	const std::vector<ObjectHandle>* m_sceneDefs;
};