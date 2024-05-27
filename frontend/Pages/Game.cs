using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using System.Windows.Forms;

namespace frontend.Pages
{
    using Newtonsoft.Json;
    using utils;
    public partial class Game : Form
    {
        private int correctAns;
        private int chosenAns;
        private int roomId;
        private int questionAmt;
        public Game(int id)
        {
            questionAmt = 0;
            InitializeComponent();
            roomId = id;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            chosenAns = 1;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            chosenAns = 2;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            chosenAns = 3;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            chosenAns = 4;
        }

        public void processAns()
        {
            if (chosenAns == correctAns)
            {

            }
        }

        public void getQuestion()
        {

        }

        private void timeEnd(object sender, EventArgs e)
        {

        }
        private void Game_Load(object sender, EventArgs e)
        {
            button1.Hide();
            button2.Hide();
            button3.Hide();
            button4.Hide();
            Thread.Sleep(1000);

            string message = "11|0000";
            string answer = Program.sendAndRecieve(message, true);

            Room room = JsonConvert.DeserializeObject<Room>(answer);



            System.Timers.Timer timer = new System.Timers.Timer();
            timer.Interval = room.answerTimeout; //timer for question timeout
            int elapsed = room.answerTimeout;
            timer.Elapsed += (sender, e) =>
            {
                elapsed--;
                label2.Text = elapsed.ToString();
            };

            timer.Start();

            button1.Show();
            button2.Show();
            button3.Show();
            button4.Show();
        }
    }
}
