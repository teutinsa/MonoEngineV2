using System;

namespace MonoEngineV2Lib
{
    public sealed class NotContructibleException : Exception
    {
        public NotContructibleException()
            : base("Object is not constructible!")
        { }
    }
}
