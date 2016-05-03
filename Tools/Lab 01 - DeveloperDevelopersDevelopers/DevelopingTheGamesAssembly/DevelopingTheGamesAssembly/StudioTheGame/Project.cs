using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DevelopingTheGamesAssembly.StudioTheGame
{
    public class Project
    {

        public Project()
        {
            RandomizeName();
            myDifficulty = 10;
            myCurrentProgress = 0;
            myAssignedWorkers = new List<Worker>();
        }

        public void AssignWorker(Worker aWorker)
        {
            if (aWorker.Work != null)
            {
                aWorker.Work.RemoveWorker(aWorker);
            }
            aWorker.Work = this;
            myAssignedWorkers.Add(aWorker);

        }

        public void RemoveWorker(Worker aWorker)
        {
            aWorker.ResetWork();
            myAssignedWorkers.Remove(aWorker);
        }

        public void ResetWorkersWork()
        {
            foreach (Worker iWorker in myAssignedWorkers)
            {
                iWorker.ResetWork();
            }
        }

        public void UpdateProgress()
        {
            foreach (Worker iWorker in myAssignedWorkers)
            {
                IncreaseProgress(iWorker.Skill);
            }
        }

        public void LevelUpWorkers()
        {
            foreach (Worker iWorker in myAssignedWorkers)
            {
                iWorker.Skill = (int)((float)myCurrentProgress / 5.0f);
            }
        }

        public bool IsDone()
        {
            return (myCurrentProgress >= myRecquiredProgress);
        }

        public float Progress
        {
            get
            {
                return ((float)myCurrentProgress / (float)myRecquiredProgress);
            }
        }

        private void IncreaseProgress(int aValue)
        {
            myCurrentProgress += aValue;
        }

        private void RandomizeName()
        {
            Random randomizer = new Random();
            int randomNumber = randomizer.Next(5);

            switch (randomNumber)
            {
                case 0:
                    myName = "Name 0";
                    break;
                case 1:
                    myName = "Name 1";
                    break;
                case 2:
                    myName = "Name 2";
                    break;
                case 3:
                    myName = "Name 3";
                    break;
                case 4:
                    myName = "Name 4";
                    break;
            }
        }

        public string ProjectName
        {
            set
            {
                myName = value;
            }
            get
            {
                return myName;
            }
        }

        public int Difficulty
        {
            set
            {
                myDifficulty = value;
            }

            get
            {
                return myDifficulty;
            }
        }

        public int myRecquiredProgress
        {
            get
            {
                return myDifficulty * 5;
            }
        }

        private List<Worker> myAssignedWorkers;
        private string myName;
        private int myDifficulty;
        private int myCurrentProgress;
    }
}
