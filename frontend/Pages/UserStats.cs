using frontend.utils;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace frontend.Pages
{
    public partial class UserStats : Form
    {
        public UserStats()
        {
            InitializeComponent();
        }

        private void UserStats_Load(object sender, EventArgs e)
        {
            string message = "6|0000";
            string answer = Program.sendAndRecieve(message);
            Console.WriteLine(answer);
            UserStatsData usd = JsonConvert.DeserializeObject<UserStatsData>(answer);
            var entries = usd.UserStatistics.Split(',');

            label1.Text += entries[0].ToString();
            label2.Text += entries[1].ToString();
            label3.Text += entries[2].ToString();
            label4.Text += entries[4].ToString();
            label5.Text += entries[3].ToString();
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            this.Hide();
            mainMenu mm = new mainMenu();
            mm.ShowDialog();
        }
    }
}
