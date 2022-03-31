using System.Runtime.CompilerServices;

namespace MonoEngineV2Lib
{
    public sealed class ResourceManager : EngineObject
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern Resource GetResource(string name);
    }
}
