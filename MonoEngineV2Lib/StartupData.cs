using System;

namespace MonoEngineV2Lib
{
    public sealed class StartupData
    {
        public Action<Scene>[] SceneDefinitions { get; }
        public int StartSceneIndex { get; }
        public string ApplicationName { get; }
        public BufferType BufferType { get; }
        public CoordinateMode CoordinateMode { get; }
        public Vector2Int CustomBufferSize { get; }

        public StartupData(string appName, int startIndex, Action<Scene>[] scendeDefs, BufferType bufType = BufferType.Default, CoordinateMode coordMode = CoordinateMode.Default)
        {
            ApplicationName = appName;
            StartSceneIndex = startIndex;
            SceneDefinitions = scendeDefs;
        }
    }
}
