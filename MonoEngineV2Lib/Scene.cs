using System.Runtime.CompilerServices;

namespace MonoEngineV2Lib
{
    public sealed class Scene : EngineObject
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern GameObject CreateObject(string name);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern GameObject FindObjectByName(string name);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void DestroyObject(GameObject go);
    }
}
