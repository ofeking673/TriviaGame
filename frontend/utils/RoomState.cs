using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace frontend.utils
{
    public class RoomState
    { //		{answerTimeout, hasGameBegun, Players, questionsCount, status = 250}
        public int answerTimeout; //only need answerTimeOut for game page
        public int questionsCount;
    }
}
