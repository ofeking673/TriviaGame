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
    public partial class InRoom : Form
    {
        public InRoom(string roomJoinData, string name)
        {
            this.roomJoinData = roomJoinData;
            this.roomName = name;
            InitializeComponent();

            
        }

        public void threadCall()
        {
            while (true)
            {
                listBox1.Items.Clear();
                string message = "4";
                string binary = Utils.StringToBinary(message);
                byte[] bytes = ASCIIEncoding.ASCII.GetBytes(binary);

                Program.networkStream.Write(bytes, 0, bytes.Length);

                byte[] bytes1 = new byte[1024];
                Program.networkStream.Read(bytes1, 0, bytes1.Length);
                string answer = Utils.GetBytesFromBinaryString(Encoding.Default.GetString(bytes1));

                string[] players = answer.Split(',');

                foreach (var word in players)
                {
                    Label lbl = new Label();
                    lbl.Text = word;
                    listBox1.Items.Add(lbl);
                }

                Thread.Sleep(3000);
            }
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            this.Close();
            JoinRoom joinRoom = new JoinRoom();
            joinRoom.ShowDialog();
        }
        private string roomJoinData { get; set; }
        private string roomName { get; set; }
    }
}
