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

        private void button1_Click(object sender, EventArgs e)
        {
            //send server message to start room, whenever you do it (AHEM AHEM NESLI I HOPE YOU SEE THIS)
        }

        //open thread, send socket message and when getting back deque/whatever the fuck of users use listbox.items.add(user.username)
    }
}
