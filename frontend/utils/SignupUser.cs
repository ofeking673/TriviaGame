using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace frontend.utils
{
    internal class SignupUser
    {
        public SignupUser(string username, string password, string email)
        {
            this.username = username;
            this.password = password;
            this.email = email;
        }
        public string username { get; set; }
        public string password { get; set; }
        public string email { get; set; }
    }
}
