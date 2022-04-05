using MonoEngineV2Lib;
using System;
using System.IO;
using System.Runtime.InteropServices;

namespace User_Assembly
{
    public static class Programm
    {
        [DllImport("User32.dll")]
        public static extern int MessageBoxW(IntPtr hwnd, [MarshalAs(UnmanagedType.LPWStr)] string msg, [MarshalAs(UnmanagedType.LPWStr)] string title = null, int style = 0);

        static StartupData Main()
        {
#if DEBUG
            string rscDir = Path.Combine(@"C:\Programming\Engines\MonoEngineV2\x64\Debug", "Resources");
#else
            string rscDir = Path.Combine(Environment.CurrentDirectory, "Resources");
#endif
            return new StartupData("Frogger", 0, new SceneCreateProc[]
            {
                (Scene scene) =>
                {
                    SolidColorBrush grassBrush = ResourceLoader2D.LoadSolidColorBrush(scene.ResourceManager, "grassBrush", new ColorF(0.5f, 0.5f, 0.5f));
                    SolidColorBrush streetBrush = ResourceLoader2D.LoadSolidColorBrush(scene.ResourceManager, "streetBrush", new ColorF(0.1f, 0.1f, 0.1f));
                    Image frogImage = ResourceLoader2D.LoadImage(scene.ResourceManager, "frogImage", Path.Combine(rscDir, "Frog.png"));
                    Image car1Image = ResourceLoader2D.LoadImage(scene.ResourceManager, "car1Image", Path.Combine(rscDir, "Car1.png"));
                    Image car2Image = ResourceLoader2D.LoadImage(scene.ResourceManager, "car2Image", Path.Combine(rscDir, "Car2.png"));
                    Image car3Image = ResourceLoader2D.LoadImage(scene.ResourceManager, "car3Image", Path.Combine(rscDir, "Car3.png"));
                    Image truckImage = ResourceLoader2D.LoadImage(scene.ResourceManager, "truckImage", Path.Combine(rscDir, "Truck.png"));
                    Image logImage = ResourceLoader2D.LoadImage(scene.ResourceManager, "logImage", Path.Combine(rscDir, "Log.png"));
                    
                    scene.ClearColor = new ColorF(0.1f, 0.5f, 1.0f);

                    GameObject obj = scene.CreateObject("grass1");
                    obj.Transform.Position = new Vector3f(64, 8);
                    ShapeRenderer renderer = obj.AddComponent<ShapeRenderer>();
                    renderer.Brush = grassBrush;
                    renderer.Size = new Vector3f(128, 16);

                    obj = scene.CreateObject("gress2");
                    obj.Transform.Position = new Vector3f(64, 120);
                    renderer = obj.AddComponent<ShapeRenderer>();
                    renderer.Brush = grassBrush;
                    renderer.Size = new Vector3f(128, 16);

                    obj = scene.CreateObject("street");
                    obj.Transform.Position = new Vector3f(64, 128 - 3 * 16);
                    renderer = obj.AddComponent<ShapeRenderer>();
                    renderer.Brush = streetBrush;
                    renderer.Size = new Vector3f(128, 16 * 4);

                    //TODO: logs
                    GameObject log1 = scene.CreateObject("log1");
                    log1.Transform.Position = new Vector3f(120 - 16, 120 - 16 * 6);
                    ImageRenderer drawer = log1.AddComponent<ImageRenderer>();
                    drawer.Size = new Vector3f(64, 16);
                    drawer.Image = logImage;
                    drawer.Interpolate = false;
                    log1.AddComponent<LogMove>();

                    GameObject log2 = scene.CreateObject("log2");
                    log2.Transform.Position = new Vector3f(120 - 16, 120 - 16 * 5);
                    drawer = log2.AddComponent<ImageRenderer>();
                    drawer.Size = new Vector3f(64, 16);
                    drawer.Image = logImage;
                    drawer.Interpolate = false;
                    LogMove lm = log2.AddComponent<LogMove>();
                    lm.speed = -lm.speed - 3;

                    //TODO: player
                    GameObject player = scene.CreateObject("player");
                    player.Transform.Position = new Vector3f(64 - 8, 120);
                    drawer = player.AddComponent<ImageRenderer>();
                    drawer.Size = new Vector3f(16, 16);
                    drawer.Image = frogImage;
                    drawer.Interpolate = false;
                    player.AddComponent<PlayerMove>();

#if true
                    //TODO: cars
                    for (int i = 0; i < 3; i++)
                    {
                        GameObject car = scene.CreateObject("car1");
                        car.Transform.Position = new Vector3f(120 - 16 * 3f * i, 120 - 16);
                        ImageRenderer imgDrawer = car.AddComponent<ImageRenderer>();
                        imgDrawer.Size = new Vector3f(16, 16);
                        imgDrawer.Image = car1Image;
                        imgDrawer.Interpolate = false;
                        car.AddComponent<CarMove>();
                    }

                    for (int i = 0; i < 2; i++)
                    {
                        GameObject car = scene.CreateObject("car1");
                        car.Transform.Position = new Vector3f(120 - 32 * 2 * i, 120 - 16 * 2);
                        ImageRenderer imgDrawer = car.AddComponent<ImageRenderer>();
                        imgDrawer.Size = new Vector3f(16, 16);
                        imgDrawer.Image = car2Image;
                        imgDrawer.Interpolate = false;
                        CarMove mv = car.AddComponent<CarMove>();
                        mv.speed = -30f;
                    }

                    for (int i = 0; i < 2; i++)
                    {
                        GameObject car = scene.CreateObject("car1");
                        car.Transform.Position = new Vector3f(120 - 20 * 2 * i, 120 - 16 * 3);
                        ImageRenderer imgDrawer = car.AddComponent<ImageRenderer>();
                        imgDrawer.Size = new Vector3f(16, 16);
                        imgDrawer.Image = car3Image;
                        imgDrawer.Interpolate = false;
                        CarMove mv = car.AddComponent<CarMove>();
                        mv.speed = 10f;
                    }

                    GameObject truck = scene.CreateObject("car1");
                    truck.Transform.Position = new Vector3f(120 - 16, 120 - 16 * 4);
                    drawer = truck.AddComponent<ImageRenderer>();
                    drawer.Size = new Vector3f(48, 16);
                    drawer.Image = truckImage;
                    drawer.Interpolate = false;
                    CarMove move = truck.AddComponent<CarMove>();
                    move.speed = 3f;
                    move.size = new Vector3f(48, 16);
#endif
                }
            }, BufferType.Custom, new Vector2Int(16 * 8, 16 * 8), CoordinateMode.PixelPerfect);
        }
    }
}
