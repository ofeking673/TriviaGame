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
            this.Close();
            CreateRoom createRoom = new CreateRoom();
            createRoom.ShowDialog();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            this.Close();
            JoinRoom joinRoom = new JoinRoom();
            joinRoom.ShowDialog();

        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
            Statistics stats = new Statistics();
            stats.ShowDialog();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            button3.Text = "Logging out...";
            Thread.Sleep(300);
            this.Close();
            //handle log out here
        }
    }
}
