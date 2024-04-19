using frontend.utils;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Newtonsoft.Json;
using System.Net.Sockets;
using Newtonsoft.Json.Linq;

namespace frontend.Pages
{
    public partial class Login : Form
    {
        public Login()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            LoginUser user = new LoginUser(this.textBox1.Text, this.textBox2.Text);
            string json = JsonConvert.SerializeObject(user);
            string finalJson = $"0{json.Length.ToString().PadLeft(4, '0')}{json}";
            Console.WriteLine(finalJson);
            string binary = Utils.StringToBinary(finalJson);
            Console.WriteLine(binary);
            byte[] bytes = ASCIIEncoding.ASCII.GetBytes(binary);

            Program.networkStream.Write(bytes, 0, bytes.Length);

            byte[] bytes1 = new byte[1024];
            Program.networkStream.Read(bytes1, 0, bytes1.Length);
            string answer = Utils.GetBytesFromBinaryString(Encoding.Default.GetString(bytes1));
            if (!string.IsNullOrEmpty(answer)) { this.Close(); }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Hide();
            Signup signup = new Signup();
            signup.ShowDialog();
        }
    }
}
