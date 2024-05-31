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
using System.Windows.Forms.VisualStyles;
using static System.Net.Mime.MediaTypeNames;

namespace frontend.Pages
{
    public partial class PostGame : Form
    {
        private Thread thread;
        private bool stopThread;
        public PostGame()
        {
            InitializeComponent();
        }

        private void PostGame_Load(object sender, EventArgs e)
        {
            stopThread = false;
            thread = new Thread(new ThreadStart(threadCall));
            thread.Start();
        }

        private void threadCall()
        {
            while (!stopThread)
            {
                int index = -1;
                MethodInvoker methodInvoker = delegate
                {
                    index = listBox1.SelectedIndex;
                };
                listBox1.Invoke(methodInvoker);

                string message = "17|0000";
                string answer = Program.sendAndRecieve(message);

                getRoomInfo gri = JsonConvert.DeserializeObject<getRoomInfo>(answer);

                MethodInvoker updateUI = delegate { listBox1.Items.Clear(); };
                listBox1.Invoke(updateUI);

                foreach (var item in gri.results.Split(","))
                {
                    string[] data = item.Split("|");
                    string userData = $"{data[0]}: {int.Parse(data[1])} - {int.Parse(data[2]) - 1}, AVG: {data[3]}, Score: {data[4]}";

                    updateUI = delegate { listBox1.Items.Add(userData); };
                    listBox1.Invoke(updateUI);
                }

                methodInvoker = delegate
                {
                    listBox1.SelectedIndex = index;
                };
                listBox1.Invoke(methodInvoker);
                Thread.Sleep(3000);
            }
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            stopThread = true;
            thread.Join();

            string message = "14|0000";
            Program.sendAndRecieve(message);


            this.Hide();
            mainMenu mm = new mainMenu();
            mm.ShowDialog();
        }
    }
}
