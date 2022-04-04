using MonoEngineV2Lib;
using System;
using System.Runtime.InteropServices;

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
        [DllImport("user32.dll")]
        public static extern int MessageBoxW(IntPtr hwnd, [MarshalAs(UnmanagedType.LPWStr)] string message, [MarshalAs(UnmanagedType.LPWStr)] string title, int style);

        static StartupData Main()
        {
            return new StartupData("Test Game", 0, new SceneCreateProc[]
            {
                (Scene scene) =>
                {
                    SolidColorBrush brush = ResourceLoader2D.LoadSolidColorBrush(scene.ResourceManager, "redBrush", new ColorF(1.0f, 0.0f, 0.0f));
                    Image img = ResourceLoader2D.LoadImage(scene.ResourceManager, "img", @"C:\Users\Florian Schumacher\Desktop\UIBackground.png");

                    scene.ClearColor = new ColorF(0.0f, 1.0f, 0.0f);
                    MessageBoxW(IntPtr.Zero, scene.ClearColor.ToString(), "Test C", 0);

                    GameObject obj = scene.CreateObject("Test");
                    obj.Transform.Position = new Vector3f(128, 128);
                    //obj.Transform.Scale = new Vector2f(1.5f, 1.5f);
                    MessageBoxW(IntPtr.Zero, obj.Transform.Position.ToString(), "Test P", 0);
                    obj.AddComponent<TestScript>();
                    ImageRenderer renderer = obj.AddComponent<ImageRenderer>();
                    renderer.Size = new Vector3f(16, 16);
                    renderer.Interpolate = false;
                    renderer.Image = img;
                }
            }, BufferType.Custom, new Vector2Int(16 * 16, 16 * 16), CoordinateMode.PixelPerfect);
        }
    }
}
