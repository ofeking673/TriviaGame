using frontend.utils;
using System.Net.Sockets;

namespace frontend
{
    using Pages;
    using System.Text;

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

        public static string sendAndRecieve(string message, bool ok) {
            if (ok)
            {
                string binary = Utils.StringToBinary(message);
                byte[] bytes = ASCIIEncoding.ASCII.GetBytes(binary);

                Program.networkStream.Write(bytes, 0, bytes.Length);

                byte[] bytes1 = new byte[1024];
                Program.networkStream.Read(bytes1, 0, bytes1.Length);
                Console.WriteLine(Encoding.Default.GetString(bytes1));

                if (string.IsNullOrEmpty(Encoding.Default.GetString(bytes1))) { return ""; }

                string answer = Utils.GetBytesFromBinaryString(Encoding.Default.GetString(bytes1));
                return answer;
            }
            return "";
        }
    }
}