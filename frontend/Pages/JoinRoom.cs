using frontend.utils;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Security.Cryptography;
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

        private bool stopThread = false;
        private Thread thread;
        public JoinRoom()
        {
            InitializeComponent();

            this.thread = new Thread(new ThreadStart(threadCall));
            this.thread.Start();
        }

        private void threadCall()
        {
            while (!stopThread)
            {
                if(listBox1.InvokeRequired)
                {
                    int index = -1;
                    MethodInvoker methodInvoker = delegate { index = listBox1.SelectedIndex; };
                    listBox1.Invoke(methodInvoker);

                    methodInvoker = delegate { listBox1.Items.Clear(); };
                    listBox1.Invoke(methodInvoker);
                    string message = "3|0000";

                    string answer = Program.sendAndRecieve(message);
                    //"Rooms":{ "RoomData, RoomData"}
                    RoomData roomData = JsonConvert.DeserializeObject<RoomData>(answer);


                    if (!string.IsNullOrEmpty(roomData.Rooms))
                    {
                        foreach (var word in roomData.Rooms.Split(","))
                        {
                            Console.WriteLine(word);
                            string[] strings = word.Split("|");
                            string roomName = strings[name];
                            if(roomName != "matchmakingRoom")
                            {
                                string joinable = (strings[5] == "0") ? "yes" : "no";
                                string text = $"{strings[name]} [{strings[id]}] Is joinable: {joinable}";

                                MethodInvoker updateUI = delegate { listBox1.Items.Add(text); };
                                listBox1.Invoke(updateUI);
                            }
                        }
                        methodInvoker = delegate
                        {
                            listBox1.SelectedIndex = index;
                        };
                        listBox1.Invoke(methodInvoker);
                    }
                    Thread.Sleep(3000);
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string message = "5";
            var obj = listBox1.SelectedItem;
            string value = listBox1.GetItemText(obj);
            if(string.IsNullOrEmpty(value)) 
            {
                ErrorJoin(sender,e);
                return;
            }
            string joinable = value.Substring(value.IndexOf(": ") + 2, value.Length - value.IndexOf(": ")-2);
            Console.WriteLine(joinable);
            value = value.Substring(value.IndexOf("[") + 1, value.IndexOf("]") - value.IndexOf("[")-1);
            Console.WriteLine(value);
            RoomJoin room = new RoomJoin();
            room.roomId = int.Parse(value);

            if (joinable == "yes")
            {
                string json = JsonConvert.SerializeObject(room);
                string finalMsg = $"{message}|{json.Length.ToString().PadLeft(4, '0')}{json}";
                string answer = Program.sendAndRecieve(finalMsg);

                if (answer.Contains("310"))
                {
                    stopThread = true;
                    thread.Join();
                    this.Hide();
                    InRoom inRoom = new InRoom(int.Parse(value));
                    inRoom.ShowDialog();
                }
                else
                {
                    ErrorJoin(sender, e);
                }
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
            stopThread = true;
            thread.Join();
            this.Hide();
            mainMenu mm = new mainMenu();
            mm.ShowDialog();
        }
    }
}
