namespace frontend
{
    using Pages;
    using System.Net;

    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            IPEndPoint iPEnd = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 8826);
            Program.Client.Connect(iPEnd);

            Program.networkStream = Program.Client.GetStream();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Login login = new Login();
            login.ShowDialog();

            mainMenu mm = new mainMenu();
            mm.ShowDialog();
        }
    }
}