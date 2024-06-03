using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace frontend.utils
{
    internal class newQuestion
    {
        public newQuestion(string question, string correctAnswer, string ans, string ans2, string ans3)
        {
            this.question = question;
            this.correctAnswer = correctAnswer;
            answer1 = ans;
            answer2 = ans2;
            answer3 = ans3;
        }

        public string question;
        public string correctAnswer;
        public string answer1;
        public string answer2;
        public string answer3;
    }
}
