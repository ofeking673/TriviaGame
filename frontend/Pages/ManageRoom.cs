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
    public partial class ManageRoom : Form
    {
        public bool stopThread = false;
        public Thread thread;
        private int roomId;

        public ManageRoom(int id)
        {
            InitializeComponent();

            this.roomId = id;

            thread = new Thread(new ThreadStart(threadCall));
            thread.Start();
        }

        //open thread, send socket message and when getting back deque/whatever the fuck of users use listbox.items.add(user.username)
        public void threadCall()
        {
            while (true && !stopThread)
            {
                listBox1.Items.Clear();
                RoomId roomId = new RoomId();
                roomId.roomId = this.roomId;

                string json = JsonConvert.SerializeObject(roomId);
                string message = $"4{json.Length.ToString().PadLeft(4, '0')}{json}";
                string answer = Program.sendAndRecieve(message);
                Console.WriteLine(answer);

                RoomPlayers roomPlayers = JsonConvert.DeserializeObject<RoomPlayers>(answer);

                if (string.IsNullOrEmpty(roomPlayers.playersInRoom)) { Thread.Sleep(3000); continue; }

                string[] players = roomPlayers.playersInRoom.Split(',');

                foreach (var word in players)
                {
                    listBox1.Items.Add(word);
                }

                listBox1.Items[0] += " - Room owner";
                Thread.Sleep(3000);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //go to game page
            //this.Hide();
            //stopThread = true;
            //thread.Join();
            //mainMenu mm = new mainMenu();
            //mm.Show();

            string message = "100000";
            string answer = Program.sendAndRecieve(message);
            
            if (answer.Contains("420")) {
                MessageBox.Show("ok game started bruh", "Game notification!", MessageBoxButtons.OK);
            }
            
            //waht teh fuck did oyu do

        }
    }
}
