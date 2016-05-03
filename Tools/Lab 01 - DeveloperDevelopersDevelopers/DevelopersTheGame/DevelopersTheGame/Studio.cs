using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DevelopersTheGame
{
    class Studio
    {
        public Studio(Label aMoneyLabel, ListBox aIdleBox)
        {
            myMoneyLabel = aMoneyLabel;
            myIdleWorkersBox = aIdleBox;


            AccessMoney = 1500;
            myWorkers = new List<Worker>();
        }
        #region Variables
        private int myMoney;
        private List<Worker> myWorkers;
        private Label myMoneyLabel;
        private ListBox myIdleWorkersBox;
        #endregion

        #region Functions

        public void AddWorker()
        {
            myWorkers.Add(new Worker());
            myIdleWorkersBox.Items.Add(myWorkers[myWorkers.Count - 1]);
        }

        public void RemoveWorker()
        {
            myWorkers.Remove(myIdleWorkersBox.SelectedItem as Worker);
            myIdleWorkersBox.Items.Remove(myIdleWorkersBox.SelectedItem);
        }

        #endregion


        #region Accessors
        public int AccessMoney
        {
            get
            {
                return myMoney;
            }

            set
            {
                myMoney = value;
                myMoneyLabel.Text = "Money: " + myMoney;
            }
        }
        #endregion
    }
}
