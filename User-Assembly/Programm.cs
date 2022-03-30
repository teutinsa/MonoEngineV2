using MonoEngineV2Lib;

namespace User_Assembly
{
    public static class Programm
    {
        static StartupData Main()
        {
            return new StartupData("Test Game", 0, new SceneCreateProc[]
            {
                (Scene scene) =>
                {
                    GameObject obj = scene.CreateObject("Test");
                    
                }
            }, BufferType.Custom, new Vector2Int(256, 256), CoordinateMode.PixelPerfect);
        }
    }
}
