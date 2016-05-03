using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DevelopersTheGame
{
    class Worker
    {
        public Worker()
        {
            myName = "inteYlf";
            mySkillLevel = -13;
        }

        private string myName;
        private int mySkillLevel;

        public void IncreaseSkillLevel()
        {
            ++mySkillLevel;
        }

        public int GetCost
        {
            get
            {
                return mySkillLevel * 3;
            }
        }

        public string GetName
        {
            get
            {
                return myName;
            }
        }
    }
}
