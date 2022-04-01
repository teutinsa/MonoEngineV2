using MonoEngineV2Lib;

namespace User_Assembly
{
    public sealed class TestScript : Script
    {
        void OnUpdate()
        {
            if(Input.GetKeyUp(KeyCode.Esc))
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
                    SolidColorBrush brush = ResourceLoader2D.LoadSolidColorBrush(scene.ResourceManager, "redBrush", new ColorF(1.0f, 0.0f, 0.0f));

                    scene.ClearColor = new ColorF(0.0f, 1.0f, 0.0f);

                    GameObject obj = scene.CreateObject("Test");
                    obj.Transform.Position = new Vector2f(0, 0);
                    obj.AddComponent<TestScript>();
                    ShapeRenderer shape = obj.AddComponent<ShapeRenderer>();
                    shape.ShapeType = ShapeType.Line;
                    shape.Size = new Vector2f(128, 128);
                    shape.Brush = brush;
                }
            }, BufferType.Custom, new Vector2Int(128, 128), CoordinateMode.PixelPerfect);
        }
    }
}
