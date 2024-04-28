using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace frontend.utils
{
    internal class RoomJoin
    {
        public RoomJoin(string name) { this.room = name; }
        public string room {  get; set; }
    }
}
