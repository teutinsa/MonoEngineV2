namespace MonoEngineV2Lib
{
    public abstract class EngineObject : Object
    {
        public EngineObject()
        {
            throw new NotContructibleException();
        }
    }
}
