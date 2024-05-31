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
            labels[0] = label1;
            labels[1] = label2;
            labels[2] = label3;
            labels[3] = label4;
            labels[4] = label5;


            string message = "6|0000";
            string answer = Program.sendAndRecieve(message);
            UserStatsData usd = JsonConvert.DeserializeObject<UserStatsData>(answer);
            var entries = usd.personalStats.Split(',');
            for (int i = 0; i < entries.Length; i++)
            {
                labels[i].Text += entries[i];
            }
        }

        private Label[] labels = new Label[5];
    }
}
