﻿using System;
namespace Core
{
    class CoreManager : IDisposable
    {
        private Map m_Map;

        public void Initialise()
        {
            m_Map = new Map();
            m_Map.Initialise();
        }

        
        public void Update()
        {
            m_Map.Update();
        }


        public void Render()
        {
            m_Map.Render();
        }


        public void Dispose()
        {
            m_Map.Dispose();
        }
    }
}
