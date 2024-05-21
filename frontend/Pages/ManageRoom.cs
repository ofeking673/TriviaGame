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
            this.Load += loadForm;
            this.roomId = id;
        }

        public void loadForm(object sender, EventArgs e)
        {
            thread = new Thread(new ThreadStart(threadCall));
            thread.Start();
        }

        //open thread, send socket message and when getting back deque/whatever the fuck of users use listbox.items.add(user.username)
        public void threadCall()
        {
            while (!stopThread)
            {
                if (!listBox1.IsHandleCreated) continue;
                MethodInvoker updateUI = delegate
                {
                    listBox1.Items.Clear();
                };
                listBox1.Invoke(updateUI);

                RoomId roomId = new RoomId();
                roomId.roomId = this.roomId;

                string json = JsonConvert.SerializeObject(roomId);
                string message = $"4|{json.Length.ToString().PadLeft(4, '0')}{json}";
                string answer = Program.sendAndRecieve(message, !stopThread);
                Console.WriteLine(answer);

                RoomPlayers roomPlayers = JsonConvert.DeserializeObject<RoomPlayers>(answer);


                if (string.IsNullOrEmpty(roomPlayers.PlayersInRoom)) { Thread.Sleep(3000); continue; }

                string[] players = roomPlayers.PlayersInRoom.Split(',');

                foreach (var word in players)
                {
                    updateUI = delegate
                    {
                        listBox1.Items.Add(word);
                    };
                    listBox1.Invoke(updateUI);
                }

                updateUI = delegate
                {
                    listBox1.Items[0] += " - Room owner";
                };
                listBox1.Invoke(updateUI);
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

            string message = "10|0000";
            string answer = Program.sendAndRecieve(message, true);

            if (answer.Contains("420"))
            {
                MessageBox.Show("You started the game!", "Game notification!", MessageBoxButtons.OK);
            }

            //waht teh fuck did oyu do

        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            stopThread = true;
            thread.Join();

            string message = "9|0000";
            string answer = Program.sendAndRecieve(message, stopThread);

            if (answer.Contains("410"))
            {
                MessageBox.Show("Room closed!", "Going back to menu", MessageBoxButtons.OK);
            }

            this.Hide();
            mainMenu mm = new mainMenu();
            mm.ShowDialog();
        }
    }
}
