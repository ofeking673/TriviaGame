using frontend.utils;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace frontend.Pages
{
    public partial class Signup : Form
    {
        public Signup()
        {
            InitializeComponent();
        }

        private void Signup_Load(object sender, EventArgs e)
        {
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Hide();
            Login login = new Login();
            login.ShowDialog();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Console.WriteLine(this.textBox1.Text + this.textBox2.Text + this.textBox4.Text);
            SignupUser user = new SignupUser(this.textBox1.Text, this.textBox2.Text, this.textBox4.Text);
            string json = JsonConvert.SerializeObject(user);
            Console.WriteLine(json);
            string finalJson = $"1{json.Length.ToString().PadLeft(4, '0')}{json}";
            byte[] bytes = ASCIIEncoding.ASCII.GetBytes(Utils.StringToBinary(finalJson));

            Program.networkStream.Write(bytes, 0, bytes.Length);

            byte[] bytes1 = new byte[1024];
            Program.networkStream.Read(bytes1, 0, bytes1.Length);
            string answer = Utils.GetBytesFromBinaryString(Encoding.Default.GetString(bytes1));
            Console.WriteLine(answer);
            if (answer.Contains("110")) { this.Close(); }
        }
    }
}
