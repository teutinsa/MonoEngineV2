using MonoEngineV2Lib;

namespace User_Assembly
{
    public sealed class TestScript : Script
    {
        void OnUpdate()
        {
            if(Input.GetKeyUp(KeyCode.Q))
                Application.Quit();
        }
    }

    public static class Programm
    {
        static StartupData Main()
        {
            return new StartupData("Test Game", 0, new SceneCreateProc[]
            {
                (Scene scene) =>
                {
                    scene.ClearColor = new ColorF(0.0f, 1.0f, 0.0f);

                    GameObject obj = scene.CreateObject("Test");
                    obj.AddComponent<TestScript>();
                }
            }, BufferType.Custom, new Vector2Int(256, 256), CoordinateMode.PixelPerfect);
        }
    }
}
