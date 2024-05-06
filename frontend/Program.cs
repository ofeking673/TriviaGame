using frontend.utils;
using System.Net.Sockets;

namespace frontend
{
    using Pages;
    internal static class Program
    {
        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            // To customize application configuration such as set high DPI settings or default font,
            // see https://aka.ms/applicationconfiguration.
            ApplicationConfiguration.Initialize();
            Application.Run(new Login());
            
            Client.SendBufferSize = 1024;
            Client.ReceiveBufferSize = 1024;
        }

        public static TcpClient Client = new TcpClient();
        public static NetworkStream networkStream; //communicating through here
        public static LoginUser loginUser;

        public static bool Valid(TextBox obj)
        {
            return obj != null && obj.Text != null && obj.Text.Length > 0;
        }
    }
}