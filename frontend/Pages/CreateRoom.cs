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
    public partial class CreateRoom : Form
    {
        public CreateRoom()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e) //create room
        {
            if (!(Program.Valid(textBox1) && Program.Valid(textBox2) && Program.Valid(textBox3) && Program.Valid(textBox4)))
            {
                MessageBox.Show("Invalid input", "Please try again.", MessageBoxButtons.OK);
                return;
            }
            string message = "2";

            Room room = new Room(textBox1.Text, textBox2.Text, textBox3.Text, textBox4.Text);

            string json = JsonConvert.SerializeObject(room);
            string finalJson = $"{message}{json.Length.ToString().PadLeft(4, '0')}{json}";
            string answer = Program.sendAndRecieve(finalJson);

            Console.WriteLine(answer);
            
            CreateRoomResponse response = JsonConvert.DeserializeObject<CreateRoomResponse>(answer);

            if (answer.Contains("300"))
            {
                this.Hide();
                ManageRoom manageRoom = new ManageRoom(response.roomId);
                manageRoom.ShowDialog();
            }
            //send server message to start room, whenever you do it (AHEM AHEM NESLI I HOPE YOU SEE THIS)
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            this.Hide();
            mainMenu mainMenu = new mainMenu();
            mainMenu.ShowDialog();
        }
    }
}
