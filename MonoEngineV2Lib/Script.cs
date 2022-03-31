namespace MonoEngineV2Lib
{
    public class Script : Component
    {
        public Transform Transform => GameObject.Transform;

        public T GetComponent<T>() where T : Component
        {
            return GameObject.GetComponent<T>();
        }

        public T AddComponent<T>() where T : Component
        {
            return GameObject.AddComponent<T>();
        }
    }
}