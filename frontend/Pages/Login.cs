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
using System.Net;

namespace frontend.Pages
{
    public partial class Login : Form
    {
        public Login()
        {
            InitializeComponent();

            IPEndPoint iPEnd = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 8826);

            Program.Client.Connect(iPEnd);

            Program.networkStream = Program.Client.GetStream();
        }

        private void button1_Click(object sender, EventArgs e) //sign in
        {
            if (!(Program.Valid(textBox1) && Program.Valid(textBox2)))
            {
                MessageBox.Show("Invalid input", "Please try again.", MessageBoxButtons.OK);
                return;
            }
            LoginUser user = new LoginUser(this.textBox1.Text, this.textBox2.Text);
            string json = JsonConvert.SerializeObject(user); //"{"username": "username", "password":"password"}"
            string finalJson = $"0|{json.Length.ToString().PadLeft(4, '0')}{json}"; //code | json len | json
            //5 -> 0005
            string answer = Program.sendAndRecieve(finalJson);

            Console.WriteLine(answer);
            if (answer.Contains("100"))
            {
                this.Hide();
                mainMenu mm = new mainMenu();
                mm.ShowDialog();
            }
            else
            {
                MessageBox.Show("Incorrect password.", "Login failed", MessageBoxButtons.OK);
            }
        }

        private void button2_Click(object sender, EventArgs e) //go to signup
        {
            this.Hide();
            Signup signup = new Signup();
            signup.ShowDialog();
        }
    }
}
