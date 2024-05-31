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

namespace frontend.Pages
{
    public partial class mainMenu : Form
    {
        public mainMenu()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Hide();
            CreateRoom createRoom = new CreateRoom();
            createRoom.ShowDialog();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            this.Hide();
            JoinRoom joinRoom = new JoinRoom();
            joinRoom.ShowDialog();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Hide();
            Statistics stats = new Statistics();
            stats.ShowDialog();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Thread.Sleep(1000);
            this.Close();
            //handle log out here

            string msg = "8|0000";
            Program.sendAndRecieve(msg);
        }

    }
}
