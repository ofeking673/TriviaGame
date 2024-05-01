using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace frontend.utils
{
    internal class Room
    {
        public Room(string roomName, string maxUsers, string questionsCount, string answersTimeout)
        {
            this.roomName = roomName;
            this.maxUsers = int.Parse(maxUsers);
            this.questionsCount = int.Parse(questionsCount);
            this.answerTimeout = int.Parse(answersTimeout);
        }

        /*
         *     request.roomName = j.at("roomName").get<std::string>();
         *     request.maxUsers = j.at("maxUsers").get<unsigned int>();
         *     request.questionsCount = j.at("questionsCount").get<unsigned int>();
         *     request.answerTimeout = j.at("answerTimeout").get<unsigned int>();
         */
        public string roomName { get; set; }
        public int maxUsers { get; set; }
        public int questionsCount { get; set; }
        public int answerTimeout { get; set; }
    }
}
