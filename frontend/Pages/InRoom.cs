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
using static System.Net.Mime.MediaTypeNames;

namespace frontend.Pages
{
    public partial class InRoom : Form
    {
        public bool stopThread = false;
        public Thread thread;
        public Thread updateThread;
        public InRoom(int id)
        {
            this.roomId = id;
            InitializeComponent();
        }

        public void loadPage(object sender, EventArgs e)
        {
            thread = new Thread(new ThreadStart(threadCall));
            thread.Start();

            updateThread = new Thread(new ThreadStart(update));
            updateThread.Start();
        }

        public void update()
        {
            while(!stopThread)
            {
                string message = "13|0000";
                if(stopThread) { return; }
                mutex.WaitOne();
                string answer = Program.sendAndRecieve(message, !stopThread);
                Console.WriteLine(answer);

                if(!string.IsNullOrEmpty(answer))
                {
                    StatusOnly status = JsonConvert.DeserializeObject<StatusOnly>(answer);
                    mutex.ReleaseMutex();

                    switch (status.status)
                    {
                        case 0:
                            break;
                        case 1:
                            MessageBox.Show("yo game starting");
                            stopThread = true;
                            //handle game start here
                            return;
                        case 2:
                            MessageBox.Show("Room was closed!");
                            stopThread = true;
                            leaveRoom();
                            return;
                    }
                }

                Thread.Sleep(3000);
            }
        }

        public void threadCall()
        {
            while (true && !stopThread)
            {
                MethodInvoker update = delegate { listBox1.Items.Clear(); };
                listBox1.Invoke(update);
                RoomId roomId = new RoomId();
                roomId.roomId = this.roomId;

                string json = JsonConvert.SerializeObject(roomId);
                string message = $"4|{json.Length.ToString().PadLeft(4, '0')}{json}";
                if (stopThread) { return; } //incase we close room while this one is running
                mutex.WaitOne();
                string answer = Program.sendAndRecieve(message, !stopThread);
                Console.WriteLine(answer);
                RoomPlayers roomPlayers = JsonConvert.DeserializeObject<RoomPlayers>(answer);
                mutex.ReleaseMutex();

                if (string.IsNullOrEmpty(roomPlayers.PlayersInRoom)) { Thread.Sleep(3000); continue; }

                string[] players = roomPlayers.PlayersInRoom.Split(',');

                Console.WriteLine(players);
                foreach (var word in players)
                {
                    Console.WriteLine(word);
                    Thread.Sleep(1000);
                    MethodInvoker updateUI = delegate { listBox1.Items.Add(word); };
                    listBox1.Invoke(updateUI);
                }
                MethodInvoker updateUi = delegate { listBox1.Items[0] += " - Room owner"; };
                listBox1.Invoke(updateUi);

                Thread.Sleep(3000);
            }
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            leaveRoom();
        }

        private void leaveRoom()
        {
            thread.Join();
            updateThread.Join();

            this.Hide();
            JoinRoom j = new JoinRoom();
            j.ShowDialog();            
        }

        private int roomId;
        public static Mutex mutex = new Mutex();
    }
}
