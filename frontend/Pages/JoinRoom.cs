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
                int index = listBox1.SelectedIndex;
                listBox1.Items.Clear();
                string message = "30000";
                string binary = Utils.StringToBinary(message);
                byte[] bytes = ASCIIEncoding.ASCII.GetBytes(binary);

                Program.networkStream.Write(bytes, 0, bytes.Length);

                byte[] bytes1 = new byte[1024];
                Program.networkStream.Read(bytes1, 0, bytes1.Length);
                string answer = Utils.GetBytesFromBinaryString(Encoding.Default.GetString(bytes1));
                Console.WriteLine(answer);
                //"Rooms":{ "RoomData, RoomData"}
                RoomData roomData = JsonConvert.DeserializeObject<RoomData>(answer);

                foreach (var word in roomData.Rooms.Split(","))
                {
                    Console.WriteLine(word);
                    string[] strings = word.Split("|");
                    string text = $"{strings[name]} [{strings[id]}]";

                    listBox1.Items.Add(text);
                }
                listBox1.SelectedIndex = index;
                Thread.Sleep(3000);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string message = "5";
            var obj = listBox1.SelectedItem;
            string value = listBox1.GetItemText(obj);
            value = value.Substring(value.IndexOf("[") + 1, value.IndexOf("]") - value.IndexOf("[")-1);
            Console.WriteLine(value);
            RoomJoin room = new RoomJoin();
            room.roomId = int.Parse(value);

            string json = JsonConvert.SerializeObject(room);
            Console.WriteLine(json);
            string finalMsg = $"{message}{json.Length}{json}";
            string binary = Utils.StringToBinary(finalMsg);
            byte[] bytes = ASCIIEncoding.ASCII.GetBytes(binary);

            Thread.Sleep(100000);
            Program.networkStream.Write(bytes, 0, bytes.Length);

            byte[] bytes1 = new byte[1024];
            Program.networkStream.Read(bytes1, 0, bytes1.Length);
            string answer = Utils.GetBytesFromBinaryString(Encoding.Default.GetString(bytes1));

            if (answer.StartsWith("310"))
            {
                this.Hide();
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
            if (listBox1.SelectedIndex >= 0)
                listBox1.Items[listBox1.SelectedIndex] = "Error joining selected room. Please try again later!";
        }
        private void pictureBox2_Click(object sender, EventArgs e)
        {
            this.Hide();
            mainMenu mm = new mainMenu();
            mm.ShowDialog();
        }
    }
}
