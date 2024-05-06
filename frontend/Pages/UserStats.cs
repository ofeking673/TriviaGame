﻿using frontend.utils;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace frontend.Pages
{
    public partial class UserStats : Form
    {
        public UserStats()
        {
            InitializeComponent();
            //{label1, label2, label3, label4, label5 }
            labels[0] = label1;
            labels[1] = label2;
            labels[2] = label3;
            labels[3] = label4;
            labels[4] = label5;

        }

        private void UserStats_Load(object sender, EventArgs e)
        {
            string message = "60000";
            string binary = Utils.StringToBinary(message);
            byte[] bytes = ASCIIEncoding.ASCII.GetBytes(binary);

            Program.networkStream.Write(bytes, 0, bytes.Length);

            byte[] bytes1 = new byte[1024];
            Program.networkStream.Read(bytes1, 0, bytes1.Length);
            string answer = Utils.GetBytesFromBinaryString(Encoding.Default.GetString(bytes1));
            Console.WriteLine(answer);
            UserStatsData usd = JsonConvert.DeserializeObject<UserStatsData>(answer);
            var entries = usd.personalStats.Split(',');
            for (int i = 0; i < entries.Length; i++)
            {
                labels[i].Text += entries[i];
            }
        }

        private Label[] labels = new Label[5];
    }
}
