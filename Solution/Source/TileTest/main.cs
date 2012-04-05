using System;
namespace Main
{
    internal static class Program
    {
        [STAThread]
        private static void Main()
        {
            Core.CoreManager core = new Core.CoreManager();
            core.Initialise();
        }
    }
}