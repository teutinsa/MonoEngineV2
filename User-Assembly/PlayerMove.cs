using MonoEngineV2Lib;
using System;

namespace User_Assembly
{
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

            if(posY >= 16 && posY <= 48 && !IsOnLog())
            {
                Transform.Position = m_startPos;
                return;
            }

            if (Transform.Position.y <= 8)
            {
                //TODO: add score system
                Transform.Position = m_startPos;
                return;
            }
        }

        private bool IsOnLog()
        {
            foreach (LogMove lm in LogMove.logs)
            {
                if (lm.Rect.Contains(Transform.Position))
                    return true;
            }
            return false;
        }
    }
}
