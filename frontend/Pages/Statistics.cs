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
    public partial class Statistics : Form
    {
        public Statistics()
        {
            InitializeComponent();
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            //user stats
            this.Hide();
            UserStats stats = new UserStats();
            stats.ShowDialog();
        }

        private void pictureBox3_Click(object sender, EventArgs e)
        {
            //high scores
            this.Hide();
            HighScores stats = new HighScores();
            stats.ShowDialog();
        }
    }
}
