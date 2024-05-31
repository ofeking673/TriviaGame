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
        public Thread closeThread;
        public RoomState rm;

        public InRoom(int id)
        {
            this.roomId = id;
            InitializeComponent();
        }

        public void loadPage(object sender, EventArgs e)
        {

            string message = "11|0000";
            string answer = Program.sendAndRecieve(message);

            rm = JsonConvert.DeserializeObject<RoomState>(answer);

            thread = new Thread(new ThreadStart(threadCall));
            thread.Start();

            closeThread = new Thread(new ThreadStart(processType));
            closeThread.Start();
        }

        public int update()
        {
            string message = "13|0000";
            if(stopThread) { return 2; }
            string answer = Program.sendAndRecieve(message);
            Console.WriteLine(answer + " Length = " + answer.Length);
            if(!string.IsNullOrEmpty(answer))
            {
                StatusOnly status = new StatusOnly();
                status.status = 2;

                if (JsonConvert.DeserializeObject<Error>(answer).message != "")
                    status = JsonConvert.DeserializeObject<StatusOnly>(answer);

                switch (status.status)
                {
                    case 0:
                        return 0;
                    case 1:
                        stopThread = true;
                        return 1;
                    case 2:
                        stopThread = true;
                        return 2;
                }
            }
            return 2;
        }

        public void threadCall()
        {
            while (!stopThread)
            {
 
                RoomId roomId = new RoomId();
                roomId.roomId = this.roomId;

                string json = JsonConvert.SerializeObject(roomId);
                string message = $"4|{json.Length.ToString().PadLeft(4, '0')}{json}";
                if (stopThread) { return; } //incase we close room while this one is running

                int what = update();
                Console.WriteLine(what);
                switch (what)
                {
                    case 0:
                        break; 
                    case 1:
                    case 2:
                        roomMethod = what;
                        return;
                }

                string answer = Program.sendAndRecieve(message);
                Console.WriteLine(answer);
                RoomPlayers roomPlayers = JsonConvert.DeserializeObject<RoomPlayers>(answer);

                if (string.IsNullOrEmpty(roomPlayers.PlayersInRoom)) { Thread.Sleep(3000); continue; }

                string[] players = roomPlayers.PlayersInRoom.Split(',');

                MethodInvoker upd = delegate { listBox1.Items.Clear(); };
                listBox1.Invoke(upd);

                foreach (var word in players)
                {
                    Console.WriteLine(word);
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
            stopThread = true;
            processType();
        }

        private void processType()
        {
            thread.Join();


            switch(roomMethod)
            {
                case 1:
                    this.Hide();
                    Game game = new Game(rm.answerTimeout, rm.questionsCount);
                    game.ShowDialog();
                    break;
                case 2:
                    this.Hide();
                    JoinRoom j = new JoinRoom();
                    j.ShowDialog();
                    break;
            }        
        }

        private int roomId;
        private int roomMethod;
        public static Mutex mutex = new Mutex();
    }
}
