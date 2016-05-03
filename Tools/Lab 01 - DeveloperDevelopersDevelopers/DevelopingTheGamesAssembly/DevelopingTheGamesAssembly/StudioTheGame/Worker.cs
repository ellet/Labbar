using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DevelopingTheGamesAssembly.StudioTheGame
{
    public class Worker
    {

        public Worker()
        {
            RandomizeName();
            mySkill = 10;
            myProjectWorkingOn = null;
            string[] tempArray = new string[4];
            myRepresentation = new ListViewItem(tempArray);
            UpdateRepresentation();
            myRepresentation.Tag = this;

        }

        private void RandomizeName()
        {
            Random randomizer = new Random();
            int randomNumber = randomizer.Next(5);

            switch (randomNumber)
            {
                case 0:
                    myName = "Johan";
                    break;
                case 1:
                    myName = "Mattias";
                    break;
                case 2:
                    myName = "Marcus";
                    break;
                case 3:
                    myName = "Julia";
                    break;
                case 4:
                    myName = "Ida";
                    break;
            }
        }

        private void UpdateRepresentation()
        {
            myRepresentation.SubItems[0].Text = myName;
            myRepresentation.SubItems[1].Text = mySkill.ToString();
            myRepresentation.SubItems[2].Text = Salary.ToString();
            if (myProjectWorkingOn == null)
            {
                myRepresentation.SubItems[3].Text = "";
            }
            else
            {
                myRepresentation.SubItems[3].Text = myProjectWorkingOn.ProjectName;
            }
        }

        public ListViewItem Representation
        {
            get
            {
                return myRepresentation;
            }
        }

        public string Name
        {
            get
            {
                return myName;
            }
            set
            {
                myName = value;
                UpdateRepresentation();
            }
        }

        public int Skill
        {
            get
            {
                return mySkill;
            }
            set
            {
                mySkill += value;
                UpdateRepresentation();
            }
        }

        public int Salary
        {
            get
            {
                return mySkill * 7;
            }
        }

        public Project Work
        {
            set
            {
                myProjectWorkingOn = value;
                UpdateRepresentation();
            }
            get
            {
                return myProjectWorkingOn;
            }
        }

        public void ResetWork()
        {
            myProjectWorkingOn = null;
            UpdateRepresentation();
        }


        private ListViewItem myRepresentation;
        private string myName;
        private int mySkill;
        private Project myProjectWorkingOn;
    }
}