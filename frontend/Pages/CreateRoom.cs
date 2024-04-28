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
            string message = "2";

            Room room = new Room(textBox1.Text, textBox2.Text, textBox3.Text, textBox4.Text);

            string json = JsonConvert.SerializeObject(room);
            string finalJson = $"{message}{json.Length.ToString().PadLeft(4, '0')}{json}";
            string binary = Utils.StringToBinary(finalJson);

            byte[] bytes = ASCIIEncoding.ASCII.GetBytes(binary);

            Program.networkStream.Write(bytes, 0, bytes.Length);

            byte[] bytes1 = new byte[1024];
            Program.networkStream.Read(bytes1, 0, bytes1.Length);
            string answer = Utils.GetBytesFromBinaryString(Encoding.Default.GetString(bytes1));

            if (!string.IsNullOrEmpty(answer))
            {
                this.Close();
                ManageRoom manageRoom = new ManageRoom();
                manageRoom.ShowDialog();
            }
            //send server message to start room, whenever you do it (AHEM AHEM NESLI I HOPE YOU SEE THIS)
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            this.Close();
            mainMenu mainMenu = new mainMenu();
            mainMenu.ShowDialog();
        }
    }
}
