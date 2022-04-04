using MonoEngineV2Lib;
using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;

namespace User_Assembly
{
    public struct Rect
    {
        public float x, y, w, h;

        public Rect(Vector3f p, Vector3f s)
            : this(p.x, p.y, s.x, s.y)
        { }

        public Rect(float _x, float _y, float _w, float _h)
        {
            x = _x;
            y = _y;
            w = _w;
            h = _h;
        }

        public bool Collide(Rect rect)
        {
            float num = MathF.Max(x, rect.x);
            float num2 = MathF.Min(x + w, rect.x + rect.w);
            float num3 = MathF.Max(y, rect.y);
            float num4 = MathF.Min(y + h, rect.y + rect.h);
            return (num2 >= num && num4 >= num3);
        }

        public bool Contains(Vector3f point)
        {
            if (x <= point.x && point.y < x + w && y <= point.y)
                return point.y < y + h;
            return false;
        }
    }

    public class PlayerMove : Script
    {
        public Rect Rect
        {
            get
            {
                Vector3f pos = Transform.Position;
                return new Rect(pos.x, pos.y + 3, 16, 10);
            }
        }

        private Vector3f m_startPos;
        private ImageRenderer m_renderer;

        void OnStart()
        {
            m_startPos = Transform.Position;
            m_renderer = GetComponent<ImageRenderer>();
        }

        void OnUpdate()
        {
            int posX = (int)Transform.Position.x;
            int posY = (int)Transform.Position.y;

            if (Input.GetKeyDown(KeyCode.Left))
                posX -= 16;
            if (Input.GetKeyDown(KeyCode.Right))
                posX += 16;
            if (Input.GetKeyDown(KeyCode.Up))
                posY -= 16;
            //if (Input.GetKeyDown(KeyCode.Down))
            //    posY += 16;
            
            posX = (int)MathF.Clamp(posX, 8, 120);
            posY = (int)MathF.Clamp(posY, 8, 120);

            Transform.Position = new Vector3f(posX, posY);

            foreach (CarMove car in CarMove.cars)
            {
                if (Rect.Collide(car.Rect))
                {
                    Transform.Position = m_startPos;
                    return;
                }
            }

            if(posY >= 16 && posY <= 48 & !IsOnLog())
            {
                Transform.Position = m_startPos;
                return;
            }

            if (Transform.Position.y <= 8)
            {
                Transform.Position = m_startPos;
                return;
            }
        }

        private bool IsOnLog()
        {
            return false;
        }
    }

    public class CarMove : Script
    {
        public Rect Rect => new Rect(Transform.Position, size);

        public float speed;
        public static List<CarMove> cars;
        public Vector3f size;

        void OnCreate()
        {
            if(cars is null)
                cars = new List<CarMove>();

            size = new Vector3f(16, 16);

            speed = 5f;

            cars.Add(this);
        }

        void OnStart()
        {
        }

        void OnUpdate()
        {
            Transform.Position -= new Vector3f(speed * Time.DeltaTime, 0f);
            
            if (Transform.Position.x < -size.x / 2)
                Transform.Position = new Vector3f(136, Transform.Position.y);
            else if (Transform.Position.x > 128 + size.x / 2)
                Transform.Position = new Vector3f(-8, Transform.Position.y);
        }

        void OnDestroy()
        {
            cars.Remove(this);
        }
    }

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
            return new StartupData("Test Game", 0, new SceneCreateProc[]
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


                    //TODO: player
                    GameObject player = scene.CreateObject("player");
                    player.Transform.Position = new Vector3f(64 - 8, 120);
                    ImageRenderer drawer = player.AddComponent<ImageRenderer>();
                    drawer.Size = new Vector3f(16, 16);
                    drawer.Image = frogImage;
                    drawer.Interpolate = false;
                    player.AddComponent<PlayerMove>();

                    //TODO: cars
                    for (int i = 0; i < 3; i++)
                    {
                        GameObject car = scene.CreateObject("car1");
                        car.Transform.Position = new Vector3f(120 - 16 * 2.5f * i, 120 - 16);
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
                        mv.speed = -40f;
                    }

                    for (int i = 0; i < 4; i++)
                    {
                        GameObject car = scene.CreateObject("car1");
                        car.Transform.Position = new Vector3f(120 - 16 * 2 * i, 120 - 16 * 3);
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
                }
            }, BufferType.Custom, new Vector2Int(16 * 8, 16 * 8), CoordinateMode.PixelPerfect);
        }
    }
}
