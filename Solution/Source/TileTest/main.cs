using System;
namespace Main
{
    internal static class Program
    {
        [STAThread]
        private static void Main()
        {
            Core.Game game = new Core.Game();
            game.Initialise();
            game.Run();
        }
    }
}