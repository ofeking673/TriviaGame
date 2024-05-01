using frontend.utils;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration;
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
        public const int id = 0;
        public const int name = 1;
        public const int maxPlayers = 2;
        public const int numOfQuestionsInGame = 3;
        public const int timePerQuestion = 4;
        public const int isActive = 5;

        public JoinRoom()
        {
            InitializeComponent();

            listBox1.DrawItem += ListBox1_DrawItem;

            Thread thread = new Thread(new ThreadStart(threadCall));
            thread.Start();
        }

        private void ListBox1_DrawItem(object sender, DrawItemEventArgs e)
        {
            e.DrawBackground();
            Brush brush = new SolidBrush(Color.FromArgb(20, 20, 44));

            if((e.State & DrawItemState.Selected)== DrawItemState.Selected) {
                brush = new SolidBrush(Color.FromArgb(50, 50, 97));
            }

            e.Graphics.DrawString(listBox1.Items[e.Index].ToString(), e.Font, brush, e.Bounds, StringFormat.GenericDefault);

            e.DrawFocusRectangle();
        }

        private void threadCall()
        {
            while (true)
            {
                listBox1.Items.Clear();
                string message = "300000";
                string binary = Utils.StringToBinary(message);
                byte[] bytes = ASCIIEncoding.ASCII.GetBytes(binary);

                Program.networkStream.Write(bytes, 0, bytes.Length);

                byte[] bytes1 = new byte[1024];
                Program.networkStream.Read(bytes1, 0, bytes1.Length);
                string answer = Utils.GetBytesFromBinaryString(Encoding.Default.GetString(bytes1));
                Console.WriteLine(answer);
                string[] roomData = answer.Split(',');
                foreach (var word in roomData)
                {
                    string[] strings = word.Split("|");
                    string text = $"{name} [{id}]";

                    Label lbl = new Label();
                    lbl.Text = text;
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
            value = value.Substring(value.IndexOf("["), value.IndexOf("]") - value.IndexOf("["));

            RoomJoin room = new RoomJoin(int.Parse(value));

            string json = JsonConvert.SerializeObject(room);
            string finalMsg = $"{message}{json.Length}{json}";
            string binary = Utils.StringToBinary(finalMsg);
            byte[] bytes = ASCIIEncoding.ASCII.GetBytes(binary);

            Program.networkStream.Write(bytes, 0, bytes.Length);

            byte[] bytes1 = new byte[1024];
            Program.networkStream.Read(bytes1, 0, bytes1.Length);
            string answer = Utils.GetBytesFromBinaryString(Encoding.Default.GetString(bytes1));

            if (answer.StartsWith("310"))
            {
                this.Close();
                InRoom inRoom = new InRoom(answer, value);
                inRoom.ShowDialog();
            }
            else
            {
                ErrorJoin(sender, e);
            }

        }

        private void ErrorJoin(object sender, EventArgs e)
        {
            if (listBox1.SelectedIndex < 0) return;
            Label lbl = new Label();
            lbl.Text = "Error joining selected room. Please try again later!";
            listBox1.Items[listBox1.SelectedIndex] = lbl;
        }
        private void pictureBox2_Click(object sender, EventArgs e)
        {
            this.Close();
            mainMenu mm = new mainMenu();
            mm.ShowDialog();
        }
    }
}
