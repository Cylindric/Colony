namespace Core
{
    public class CoreManager
    {
        private Renderer m_Renderer;

        public void Initialise()
        {
            m_Renderer = new Renderer();
            m_Renderer.Initialise();
        }
    }
}
