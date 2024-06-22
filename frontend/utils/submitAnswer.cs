using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace frontend.utils
{
    internal class submitAnswer
    {
        //answerId (unsigned int) [1-4]
        //answerTime(double)
        public submitAnswer(int id, double time)
        {
            answerId = id;
            answerTime = time;
        }
        public int answerId;
        public double answerTime;
    }
}
