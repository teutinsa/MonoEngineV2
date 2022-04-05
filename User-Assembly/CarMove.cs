using MonoEngineV2Lib;
using System.Collections.Generic;

namespace User_Assembly
{
    public class CarMove : Script
    {
        public Rect Rect => new Rect(Transform.Position, size);

        public float speed;
        public Vector3f size;
        public static List<CarMove> cars = new List<CarMove>();

        void OnCreate()
        {
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
                Transform.Position = new Vector3f(128 + size.x / 2, Transform.Position.y);
            else if (Transform.Position.x > 128 + size.x / 2)
                Transform.Position = new Vector3f(-size.x / 2, Transform.Position.y);
        }

        void OnDestroy()
        {
            cars.Remove(this);
        }
    }
}
