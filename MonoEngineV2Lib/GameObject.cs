using System;
using System.Runtime.CompilerServices;

namespace MonoEngineV2Lib
{
    public sealed class GameObject : EngineObject
    {
        public extern string Name
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        public extern bool Active
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        public extern Transform Transform
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern Component GetComponent(Type type);

        public T GetComponent<T>() where T : Component
        {
            return GetComponent(typeof(T)) as T;
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern Component AddComponent(Type type);

        public T AddComponent<T>() where T : Component
        {
            return AddComponent(typeof(T)) as T;
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void RemoveComponent(Component comp);
    }
}