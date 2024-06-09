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
    public partial class addQuestion : Form
    {
        private int id;
        private string[] answers = new string[4];
        public addQuestion()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            button1.Enabled = false;

            if (Program.Valid(textBox1) && Program.Valid(textBox2) && Program.Valid(textBox3) && Program.Valid(textBox4) && Program.Valid(textBox5) && Program.Valid(textBox6))
            {

                try
                {
                    id = int.Parse(textBox6.Text);
                    if (!(1 <= id && id <= 4))
                    {
                        throw new Exception();
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show("You have not chosen a correct answer (1-4)", "Question creation", MessageBoxButtons.OK);
                }

                answers[0] = textBox2.Text;
                answers[1] = textBox3.Text;
                answers[2] = textBox4.Text;
                answers[3] = textBox5.Text;


                // Rearrange the array so that the chosen element is first
                int chosenIndex = id - 1;
                string[] rearrangedAnswers = new string[4];
                rearrangedAnswers[0] = answers[chosenIndex];

                int index = 1;
                for (int i = 0; i < answers.Length; i++)
                {
                    if (i != chosenIndex)
                    {
                        rearrangedAnswers[index++] = answers[i];
                    }
                }

                newQuestion q = new newQuestion(textBox1.Text, rearrangedAnswers[0], rearrangedAnswers[1], rearrangedAnswers[2], rearrangedAnswers[3]);
                string json = JsonConvert.SerializeObject(q);
                string message = $"18|{json.Length.ToString().PadLeft(4, '0')}{json}";
                Console.WriteLine(message);
                string answer = Program.sendAndRecieve(message);
                Console.WriteLine(answer);

                this.Hide();
                mainMenu mm = new mainMenu();
                mm.ShowDialog();
            }
            else
            {
                MessageBox.Show("One or more fields are missing.", "Question creation", MessageBoxButtons.OK);
            }
            button1.Enabled = true;
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            this.Hide();
            mainMenu mm = new mainMenu();
            mm.ShowDialog();
        }
    }
}
