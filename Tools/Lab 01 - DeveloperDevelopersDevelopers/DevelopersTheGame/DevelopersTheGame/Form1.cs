using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DevelopersTheGame
{
    public partial class Form1 : Form
    {

        Studio myStudio;
        Worker myTempWorker;
        

        List<Worker> myCouldHireList;

        Worker tempWorker;


        public Form1()
        {
            InitializeComponent();

            myStudio = new Studio(MoneyLabel, IdleWorkers);
            myTempWorker = new Worker();

            myStudio.AddWorker();

            WorkersListView.View = View.Details;

            string[] tempStrings = new string[4];

            tempStrings[0] = "testName";
            tempStrings[1] = "300";
            tempStrings[2] = "3";

            ListViewItem tempItem = new ListViewItem(tempStrings);

            WorkersListView.Items.Add(tempItem);
        }

        private void HireWorkerButton_Click(object sender, EventArgs e)
        {
            myStudio.AddWorker();
        }

        private void FireWorkerButton_Click(object sender, EventArgs e)
        {
            myStudio.RemoveWorker();
        }

        private void WorkersListView_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}


/*
        
                FÖR ATT YLF GLÖMMER SAKER
        
        */

//foreach (Worker iWorker in myTestList)
//            {
                
//            }

//private void TestLabel_Click(object sender, EventArgs e)
//{

//}

//private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
//{
//    Worker tempWorker = (Worker)listBox1.SelectedItem;
//    TestLabel.Text = tempWorker.GetName;
//}