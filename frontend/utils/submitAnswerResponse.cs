using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace frontend.utils
{
    internal class submitAnswerResponse
    {
        /*status = 600
           correctAnswerId (unsigned int)
           score (current score of user) (unsigned int)
           new handler = game request handler
           */

        public int correctAnswerId;
        public int score;
    }
}
