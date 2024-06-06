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
    public partial class Matchmaking : Form
    {
        private int TEMP_MATCHMAKING_RESPONSE_STATUS = 701;
        private int TEMP_MATCHMAKING_ROOM_CREATED_STATUS = 700;
        public Matchmaking()
        {
            InitializeComponent();
        }

        private void Matchmaking_Load(object sender, EventArgs e)
        {
            string message = "19|0000";
            string answer = Program.sendAndRecieve(message);
            Console.WriteLine(answer);
            matchmakingResponse response = JsonConvert.DeserializeObject<matchmakingResponse>(answer);
            Console.WriteLine(response.roomId);

            if(response.status == TEMP_MATCHMAKING_RESPONSE_STATUS)
            {
                this.Hide();
                InRoom inroom = new InRoom(response.roomId);
                inroom.ShowDialog();
            }
            else if (response.status == TEMP_MATCHMAKING_ROOM_CREATED_STATUS)
            {
                this.Hide();
                ManageRoom mr = new ManageRoom(response.roomId);
                mr.ShowDialog();
            }
            else
            {
                //what the fuck
            }
        }
    }
}
