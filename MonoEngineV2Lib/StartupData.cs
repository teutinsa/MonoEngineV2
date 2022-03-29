using System;

namespace MonoEngineV2Lib
{
    public sealed class StartupData
    {
        public Action<Scene>[] SceneDefinitions { get; }
        public int StartSceneIndex { get; }
        public string ApplicationName { get; }

        public StartupData(string appName, int startIndex, params Action<Scene>[] scendeDefs)
        {
            ApplicationName = appName;
            StartSceneIndex = startIndex;
            SceneDefinitions = scendeDefs;
        }
    }
}
