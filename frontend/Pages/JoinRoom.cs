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
    public partial class JoinRoom : Form
    {
        public JoinRoom()
        {
            InitializeComponent();

            Thread thread = new Thread(new ThreadStart(threadCall));
            thread.Start();
        }

        private void threadCall()
        {
            while (true)
            {
                listBox1.Items.Clear();
                string message = "3";
                string binary = Utils.StringToBinary(message);
                byte[] bytes = ASCIIEncoding.ASCII.GetBytes(binary);

                Program.networkStream.Write(bytes, 0, bytes.Length);

                byte[] bytes1 = new byte[1024];
                Program.networkStream.Read(bytes1, 0, bytes1.Length);
                string answer = Utils.GetBytesFromBinaryString(Encoding.Default.GetString(bytes1));

                string[] rooms = answer.Split(',');

                foreach (var word in rooms)
                {
                    Label lbl = new Label();
                    lbl.Text = word;
                    listBox1.Items.Add(lbl);
                }
                Thread.Sleep(3000);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string message = "5";
            var obj = listBox1.SelectedItem;
            string value = listBox1.GetItemText(obj);

            RoomJoin room = new RoomJoin(value);

            string json = JsonConvert.SerializeObject(room);
            string finalMsg = $"{message}{json.Length}{json}";
            string binary = Utils.StringToBinary(finalMsg);
            byte[] bytes = ASCIIEncoding.ASCII.GetBytes(binary);

            Program.networkStream.Write(bytes, 0, bytes.Length);

            byte[] bytes1 = new byte[1024];
            Program.networkStream.Read(bytes1, 0, bytes1.Length);
            string answer = Utils.GetBytesFromBinaryString(Encoding.Default.GetString(bytes1));

            if (!string.IsNullOrEmpty(answer))
            {
                this.Close();
                InRoom inRoom = new InRoom(answer, value);
                inRoom.ShowDialog();
            }

        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            this.Close();
            mainMenu mm = new mainMenu();
            mm.ShowDialog();
        }
    }
}
