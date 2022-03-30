using System;

namespace MonoEngineV2Lib
{
    public delegate void SceneCreateProc(Scene scene);

    public sealed class StartupData
    {
        public int StartSceneIndex { get; }
        public string ApplicationName { get; }
        public BufferType BufferType { get; }
        public CoordinateMode CoordinateMode { get; }
        public Vector2Int CustomBufferSize { get; }

        private readonly SceneCreateProc[] m_sceneDefinitions;
        
        public StartupData(string appName, int startIndex, SceneCreateProc[] scendeDefs, BufferType bufType = BufferType.Default, Vector2Int bufSize = default, CoordinateMode coordMode = CoordinateMode.Default)
        {
            m_sceneDefinitions = scendeDefs;

            ApplicationName = appName;
            StartSceneIndex = startIndex;
            BufferType = bufType;
            CoordinateMode = coordMode;
            CustomBufferSize = bufSize;
        }
    }
}
