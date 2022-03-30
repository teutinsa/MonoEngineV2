using System.Runtime.CompilerServices;

namespace MonoEngineV2Lib
{
    public sealed class Scene : EngineObject
    {
        public extern string Name
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }

        public extern ColorF ClearColor
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        public extern ResourceManager ResourceManager
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern GameObject CreateObject(string name);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern GameObject FindObjectByName(string name);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void DestroyObject(GameObject go);
    }
}
