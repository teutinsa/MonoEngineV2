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
                    Image img = ResourceLoader2D.LoadImage(scene.ResourceManager, "img", @"C:\Users\Florian Schumacher\Desktop\UIBackground.png");

                    scene.ClearColor = new ColorF(0.0f, 1.0f, 0.0f);

                    GameObject obj = scene.CreateObject("Test");
                    obj.Transform.Position = new Vector2f(64, 64);
                    obj.AddComponent<TestScript>();
                    //ShapeRenderer shape = obj.AddComponent<ShapeRenderer>();
                    //shape.ShapeType = ShapeType.Rectangle;
                    //shape.Size = new Vector2f(5, 5);
                    //shape.Brush = brush;
                    ImageRenderer renderer = obj.AddComponent<ImageRenderer>();
                    renderer.Size = new Vector2f(16, 16);
                    renderer.Interpolate = false;
                    renderer.Image = img;
                }
            }, BufferType.Custom, new Vector2Int(128, 128), CoordinateMode.PixelPerfect);
        }
    }
}
