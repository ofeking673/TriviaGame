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
        private int chosenAns;
        private int AnswerTimeOut;
        private int questionAmt;
        private double elapsed;


        public Game(int answerTimeOut, int questionsCount)
        {
            questionAmt = 0;
            InitializeComponent();
            AnswerTimeOut = answerTimeOut;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            chosenAns = 1;
            processAns();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            chosenAns = 2;
            processAns();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            chosenAns = 3;
            processAns();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            chosenAns = 4;
            processAns();
        }

        public void processAns()
        {
            submitAnswer submit = new submitAnswer(chosenAns, elapsed);
            string json = JsonConvert.SerializeObject(submit);
            string message = $"16|{json.Length.ToString().PadLeft(4, '0')}{json}";
            string answer = Program.sendAndRecieve(message, true);

            /*status = 600
			correctAnswerId (unsigned int)
			score (current score of user) (unsigned int)
			new handler = game request handler
            */

            submitAnswerResponse resp = JsonConvert.DeserializeObject<submitAnswerResponse>(answer);
            highlightCorrect(resp.correctAnswerId);
            label3.Text = $"Score: {resp.score.ToString()}";
        }

        public void highlightCorrect(int id)
        {
            switch (id)
            {
                case 1:
                    button1.BackColor = Color.Green;
                    button2.BackColor = Color.Red;
                    button3.BackColor = Color.Red;
                    button4.BackColor = Color.Red;
                    break;
                case 2:
                    button1.BackColor = Color.Red;
                    button2.BackColor = Color.Green;
                    button3.BackColor = Color.Red;
                    button4.BackColor = Color.Red;
                    break;
                case 3:
                    button1.BackColor = Color.Red;
                    button2.BackColor = Color.Red;
                    button3.BackColor = Color.Green;
                    button4.BackColor = Color.Red;
                    break;
                case 4:
                    button1.BackColor = Color.Red;
                    button2.BackColor = Color.Red;
                    button3.BackColor = Color.Red;
                    button4.BackColor = Color.Green;
                    break;
            }
        }

        public static GameQuestion GetQuestion()
        {
            string message = "15|0000";
            string answer = Program.sendAndRecieve(message, true);

            GameQuestion q = JsonConvert.DeserializeObject<GameQuestion>(answer);
            return q;
        }

        private void timeEnd(object sender, EventArgs e)
        {
            button1.Hide();
            button2.Hide();
            button3.Hide();
            button4.Hide();
            label1.Text = "Getting next question.. Sit tight!";
            Thread.Sleep(1000);


            GameQuestion q = GetQuestion();
            if (!string.IsNullOrEmpty(q.question))
            {
                return;
            }

            label1.Text = q.question;
            button1.Text = q.answers["1"];
            button2.Text = q.answers["2"];
            button3.Text = q.answers["3"];
            button4.Text = q.answers["4"];

            System.Timers.Timer timer = new System.Timers.Timer();
            timer.Interval = 100; //timer for question timeout
            elapsed = AnswerTimeOut;
            timer.Elapsed += (sender, e) =>
            {
                elapsed -= 0.1;
                label2.Text = Math.Round(elapsed, 1).ToString();
                if (elapsed < 0)
                {
                    timeEnd(sender, e);
                    return;
                }
            };

            timer.Start();

            button1.Show();
            button2.Show();
            button3.Show();
            button4.Show();
        }
        private void Game_Load(object sender, EventArgs e)
        {
            timeEnd(sender, e);
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            string message = "14|0000";
            string answer = Program.sendAndRecieve(message, true);

            if (answer.Contains("680"))
            {
                this.Hide();
                mainMenu mm = new mainMenu();
                mm.ShowDialog();
            }
        }
    }
}
