using frontend.utils;
using Newtonsoft.Json;
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
    public partial class HighScores : Form
    {
        public HighScores()
        {
            InitializeComponent();
        }

        private void HighScores_Load(object sender, EventArgs e)
        {
            string message = "7|0000";
            string answer = Program.sendAndRecieve(message);

            HighScoreResponse highScoreResponse = JsonConvert.DeserializeObject<HighScoreResponse>(answer);
            var entries = highScoreResponse.HighScores.Split(",");
            foreach (var entry in entries)
            {
                var nameScore = entry.Split("|");
                string text = $"{nameScore[0]}: {nameScore[1]}";
                listBox1.Items.Add(text);
            }
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            this.Hide();
            mainMenu mm = new mainMenu();
            mm.ShowDialog();
        }
    }
}
