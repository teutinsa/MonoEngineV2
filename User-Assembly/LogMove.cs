using MonoEngineV2Lib;
using System.Collections.Generic;

namespace User_Assembly
{
    public class LogMove : Script
    {
        public Rect Rect => new Rect(Transform.Position - new Vector3f(size.x / 2, size.y / 2), size);

        public float speed;
        public Vector3f size;
        public static List<LogMove> logs = new List<LogMove>();

        void OnCreate()
        {
            size = new Vector3f(64, 16);

            speed = 15f;

            logs.Add(this);
        }

        void OnUpdate()
        {
            Transform.Position += new Vector3f(speed * Time.DeltaTime, 0f);

            if (Transform.Position.x < -size.x / 2)
                Transform.Position = new Vector3f(128 + size.x / 2, Transform.Position.y);
            else if (Transform.Position.x > 128 + size.x / 2)
                Transform.Position = new Vector3f(-size.x / 2, Transform.Position.y);
        }

        void OnDestroy()
        {
            logs.Remove(this);
        }
    }
}
