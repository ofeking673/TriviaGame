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

            updateThread = new Thread(new ThreadStart(Update));
            updateThread.Start();
        }

        public void Update()
        {
            while(true && !stopThread)
            {
                Console.WriteLine("ITS THE UPDATE FUNCTION");
                mutex.WaitOne();
                string message = "13|0000";
                string answer = Program.sendAndRecieve(message);
                Console.WriteLine(answer);
                StatusOnly status = JsonConvert.DeserializeObject<StatusOnly>(answer);

                switch (status.status)
                {
                    case 0:
                        break;
                    case 1:
                        MessageBox.Show("yo game starting");
                        //handle game start here!!!
                        break;
                    case 2:
                        leaveRoom();
                        break;
                }
            }
        }

        public void threadCall()
        {
            while (true && !stopThread)
            {
                mutex.WaitOne();
                MethodInvoker update = delegate { listBox1.Items.Clear(); };
                listBox1.Invoke(update);
                RoomId roomId = new RoomId();
                roomId.roomId = this.roomId;

                string json = JsonConvert.SerializeObject(roomId);
                string message = $"4|{json.Length.ToString().PadLeft(4, '0')}{json}";
                string answer = Program.sendAndRecieve(message);
                Console.WriteLine(answer);
                mutex.ReleaseMutex();
                RoomPlayers roomPlayers = JsonConvert.DeserializeObject<RoomPlayers>(answer);

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
            this.Hide();
            stopThread = true;
            thread.Join();

            string message = "12|0000";
            string binary = Utils.StringToBinary(message);
            byte[] bytes = ASCIIEncoding.ASCII.GetBytes(binary);

            Program.networkStream.Write(bytes, 0, bytes.Length);

            byte[] bytes1 = new byte[1024];
            Program.networkStream.Read(bytes1, 0, bytes1.Length);
            string answer = ASCIIEncoding.ASCII.GetString(bytes1);
            if (answer.Contains("400"))
            {
                JoinRoom joinRoom = new JoinRoom();
                joinRoom.ShowDialog();
            }
        }

        private int roomId;
        public static Mutex mutex = new Mutex();
    }
}
