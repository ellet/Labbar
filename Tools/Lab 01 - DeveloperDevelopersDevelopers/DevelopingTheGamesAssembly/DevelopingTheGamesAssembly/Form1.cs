using DevelopingTheGamesAssembly.Popups;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DevelopingTheGamesAssembly
{
    public partial class Form1 : Form
    {
        private ProjectSettings myProjectPopup;


        public Form1()
        {
            InitializeComponent();
            ErrorPopup tempErrorpoup = new ErrorPopup();
            tempErrorpoup.SetParent(this);
            myStudio = new StudioTheGame.Studio(LabelStudioName, ListViewWorkers, ProjectList, ListBoxPublishedGames, LabelProjectInfo, LabelGameInfo, LabelCosts, LabelEconomy, LabelRooms, progressBarGameProgress, tempErrorpoup);
            ListViewWorkers.View = View.Details;
            myProjectPopup = new ProjectSettings(myStudio);
            AskStudioName tempGetName = new AskStudioName(myStudio);
            tempGetName.ShowDialog(this);
        }

        private void ButtonEndTurn_Click(object sender, EventArgs e)
        {
            myStudio.EndTurn();
            if (myStudio.Economy < 0)
            {
                YOULOSE tempLOSE = new YOULOSE(this);
                tempLOSE.ShowDialog(this);
            }
        }

        private void ButtonHire_Click(object sender, EventArgs e)
        {
            myStudio.HireWorker();
        }

        private void ButtonFire_Click(object sender, EventArgs e)
        {
            myStudio.FireWorker();
        }

        private StudioTheGame.Studio myStudio;

        private void ButtonCreateProject_Click(object sender, EventArgs e)
        {
            myProjectPopup.ShowDialog(this);
        }

        private void TEstTYbutton_Click(object sender, EventArgs e)
        {
            //if (myTestPoop.Visible == false)
            //{
            //    myTestPoop.Show(this);
            //}
        }

        private void ButtonRemoveFromProject_Click(object sender, EventArgs e)
        {
            myStudio.RemoveWorkersFromProjects();
        }

        private void assigntheworkybutton_Click(object sender, EventArgs e)
        {
            myStudio.AssignWorkers();
        }

        private void ProjectList_SelectedIndexChanged(object sender, EventArgs e)
        {
            myStudio.DisplayProjectInfo();
        }

        private void ListBoxPublishedGames_SelectedIndexChanged(object sender, EventArgs e)
        {
            myStudio.DisplayGameInfo();
        }

        private void ButtonTerminateProject_Click(object sender, EventArgs e)
        {
            myStudio.TerminateSelectedProject();
        }

        private void ButtonReleaseEarly_Click(object sender, EventArgs e)
        {
            myStudio.PublishSelectedEarly();
        }

        private void ButtonGetMoreRooms_Click(object sender, EventArgs e)
        {
            myStudio.BuildMoreRooms();
        }
    }
}
