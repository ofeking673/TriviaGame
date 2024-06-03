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
    using System.Reflection.Emit;
    using utils;
    public partial class Game : Form
    {
        private int chosenAns;
        private int AnswerTimeOut;
        private int questionAmt;
        private double elapsed;
        private bool Clicked;
        System.Timers.Timer timer;
        private bool Continue;


        public Game(int answerTimeOut, int questionsCount)
        {
            questionAmt = 0;
            InitializeComponent();
            AnswerTimeOut = answerTimeOut;

        }

        private void button1_Click(object sender, EventArgs e)
        {
            chosenAns = 0;
            if (!Clicked)
            {
                Clicked= true;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            chosenAns = 1;
            if (!Clicked)
            {
                Clicked = true;
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            chosenAns = 2;
            if (!Clicked)
            {
                Clicked = true;
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            chosenAns = 3;
            if (!Clicked)
            {
                Clicked = true;
            }
        }

        private void setButtonUse(bool use)
        {
            resetButton();
            MethodInvoker upd = delegate
            {
                button1.Enabled = use;
            };
            button1.Invoke(upd);

            upd = delegate
            {
                button2.Enabled = use; 
            };
            button2.Invoke(upd);

            upd = delegate
            {
                button3.Enabled = use;
            };
            button3.Invoke(upd);

            upd = delegate
            {
                button4.Enabled = use;
            };
            button4.Invoke(upd);

        }

        public void processAns()
        {
            submitAnswer submit = new submitAnswer(chosenAns, AnswerTimeOut - elapsed);
            string json = JsonConvert.SerializeObject(submit);
            string message = $"16|{json.Length.ToString().PadLeft(4, '0')}{json}";
            string answer = Program.sendAndRecieve(message);
            Console.WriteLine(answer);

            /*status = 600
			correctAnswerId (unsigned int)
			score (current score of user) (unsigned int)
			new handler = game request handler
            */

            submitAnswerResponse resp = JsonConvert.DeserializeObject<submitAnswerResponse>(answer);
            if (resp.correctAnswerId == 999)
            {
                gameEnded();
            }
            highlightCorrect(resp.correctAnswerId);
            //label3.Text = $"Score: {resp.score.ToString()}";
            label3.Invoke(delegate
            {
                label3.Text = $"Score: {resp.score.ToString()}";
            });
            Thread.Sleep(3000);
        }

        public void highlightCorrect(int id)
        {
            switch (id)
            {
                case 0:
                    button1.BackColor = Color.Green;
                    button2.BackColor = Color.Red;
                    button3.BackColor = Color.Red;
                    button4.BackColor = Color.Red;
                    break;
                case 1:
                    button1.BackColor = Color.Red;
                    button2.BackColor = Color.Green;
                    button3.BackColor = Color.Red;
                    button4.BackColor = Color.Red;
                    break;
                case 2:
                    button1.BackColor = Color.Red;
                    button2.BackColor = Color.Red;
                    button3.BackColor = Color.Green;
                    button4.BackColor = Color.Red;
                    break;
                case 3:
                    button1.BackColor = Color.Red;
                    button2.BackColor = Color.Red;
                    button3.BackColor = Color.Red;
                    button4.BackColor = Color.Green;
                    break;
            }
        }

        public void resetButton()
        {
            button1.BackColor = Color.Transparent;
            button2.BackColor = Color.Transparent;
            button3.BackColor = Color.Transparent;
            button4.BackColor = Color.Transparent;
        }

        public static GameQuestion GetQuestion()
        {
            string message = "15|0000";
            string answer = Program.sendAndRecieve(message);

            Console.WriteLine(answer);

            GameQuestion q = JsonConvert.DeserializeObject<GameQuestion>(answer);
            return q;
        }

        private void timeEnd()
        {
            setButtonUse(false);
            label1.Invoke(delegate { label1.Text = "Getting next question.. Sit tight!"; });
            Thread.Sleep(2000);


            GameQuestion q = GetQuestion();
            if (q.question == "")
            {
                gameEnded();
            }

            label1.Invoke(delegate { label1.Text = q.question; });
            button1.Invoke(delegate { button1.Text = q.answers[0]; });
            button2.Invoke(delegate { button2.Text = q.answers[1]; });
            button3.Invoke(delegate { button3.Text = q.answers[2]; });
            button4.Invoke(delegate { button4.Text = q.answers[3]; });
            Clicked = false;

            timer = new System.Timers.Timer();
            timer.Interval = 100; //timer for question timeout
            elapsed = AnswerTimeOut;
            timer.Elapsed += (sender, e) =>
            {
                elapsed -= 0.1;
                // MethodInvoker upd = delegate { listBox1.Items.Clear(); };
                //listBox1.Invoke(upd);

                MethodInvoker upd = delegate
                {
                    label2.Text = Math.Round(elapsed, 1).ToString();
                };
                label2.Invoke(upd);

                if (elapsed < 0 || Clicked)
                {
                    timer.Stop();
                    setButtonUse(false);
                    processAns();
                    timeEnd();
                    return;
                }
            };

            timer.Start();


            setButtonUse(true);
        }

        private void Game_Load(object sender, EventArgs e)
        {
            timeEnd();
        }

        private void gameEnded()
        {
            if(!this.Visible) return;
            this.Hide();
            timer.Stop();
            timer.Dispose();

            PostGame pg = new PostGame();
            pg.ShowDialog();
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            string message = "14|0000";
            string answer = Program.sendAndRecieve(message);
            Console.Write(answer);
            if (answer.Contains("680"))
            {
                this.Hide();
                mainMenu mm = new mainMenu();
                mm.ShowDialog();
            }
        }
    }
}
