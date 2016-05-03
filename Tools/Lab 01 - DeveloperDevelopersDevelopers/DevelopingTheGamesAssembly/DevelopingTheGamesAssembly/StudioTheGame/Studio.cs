using DevelopingTheGamesAssembly.Popups;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DevelopingTheGamesAssembly.StudioTheGame
{
    public class Studio
    {
        public Studio(Label aNameLabel, ListView aListView, ListBox aProjectList, ListBox aGamesList, Label aProjectInfoLabel, Label aGameInfoLabel, Label aCostLabel, Label aEconomyLabel, Label aRoomAmountLabel, ProgressBar aProjectProgressBar, ErrorPopup aErrorPopup)
        {
            myStudioNameLabel = aNameLabel;
            Name = "DefaultName";
            myMoney = 10000;
            myRandomizer = new Random();
            myWorkers = new List<Worker>();
            myProjects = new List<Project>();
            myGames = new List<PublishedGame>();
            myWorkerList = aListView;
            myProjectBox = aProjectList;
            myGamesBox = aGamesList;
            myProjectInfo = aProjectInfoLabel;
            myGameInfo = aGameInfoLabel;
            myProjectProgressBar = aProjectProgressBar;
            myCostsLabel = aCostLabel;
            myEconomyLabel = aEconomyLabel;
            myRoomLabel = aRoomAmountLabel;

            Rooms = 5;
            myCostsLabel.Text = "Costs:\n" + "Rent: " + myRentCost.ToString();

            myErrorPopup = aErrorPopup;
        }

        public void EndTurn()
        {
            GainSomePayOuts();
            PayCosts();
            UpdateGamePopularities();
            UpdateProjectsProgresses();
            DisplayGameInfo();
            PublishGames();
            DisplayProjectInfo();
            UpdateCosts();
        }

        private void PayCosts()
        {
            Economy -= myRentCost;
            Economy -= WorkerExpenses();
        }

        private void UpdateCosts()
        {
            myCostsLabel.Text = "Costs:\n" + "Rent: " + myRentCost.ToString();
            myCostsLabel.Text += "\nSalaries: " + WorkerExpenses();
        }

        private void GainSomePayOuts()
        {
            foreach (PublishedGame iGame in myGames)
            {
                myMoney += iGame.PayOut;
            }
        }

        private void UpdateProjectsProgresses()
        {
            foreach (Project iProject in myProjects)
            {
                iProject.UpdateProgress();
            }
        }

        private void UpdateGamePopularities()
        {
            foreach (PublishedGame iGame in myGames)
            {
                iGame.DecreasePopularity();
            }
        }

        public void DisplayProjectInfo()
        {
            if (myProjectBox.SelectedItem != null)
            {
                Project tempProject = myProjectBox.SelectedItem as Project;
                myProjectInfo.Text = "Project Info:\n";
                myProjectInfo.Text += "Name: "+ tempProject.ProjectName + "\n";
                float Progress = tempProject.Progress * 100.0f;
                myProjectInfo.Text += "Progress: " + Progress.ToString() + " %\n";
                myProjectProgressBar.Value = (int)Progress;
            }
            else
            {
                myProjectInfo.Text = "Project Info:\n";
            }
        }

        public void DisplayGameInfo()
        {
            if (myGamesBox.SelectedItem != null)
            {
                PublishedGame tempGame = myGamesBox.SelectedItem as PublishedGame;
                myGameInfo.Text = "Game Info:\n";
                myGameInfo.Text += "Popularity: " + tempGame.Popularity.ToString() + "\n";
                myGameInfo.Text += "Monthly Payout: " + tempGame.PayOut.ToString() + "\n";
            }
            else
            {
                myGameInfo.Text = "Game Info:\n";
            }

        }

        private void UpdateRoomInformation()
        {
            myRoomLabel.Text = "Total Rooms: " + Rooms.ToString() + "\n"
                    + "Used Rooms: " + myWorkers.Count.ToString() + "\n"
                    + "Available Rooms: " + (Rooms - myWorkers.Count).ToString();
        }

        public void StartProject(Project aNewProject)
        {
            myProjects.Add(aNewProject);
            myProjectBox.Items.Add(aNewProject);
        }

        private void PublishGames()
        {
            for (int iProject = myProjects.Count -1; iProject >= 0; --iProject)
            {
                if (myProjects[iProject].IsDone() == true)
                {
                    PublishGame(myProjects[iProject]);
                }
            }
        }

        public void PublishSelectedEarly()
        {
            if (myProjectBox.SelectedItem != null)
            {
                Project tempProject = myProjectBox.SelectedItem as Project;
                PublishGame(tempProject);
            }
        }

        private void PublishGame(Project aDoneProject)
        {
            PublishedGame tempGame = new PublishedGame(aDoneProject);
            myGames.Add(tempGame);
            myGamesBox.Items.Add(tempGame);
            TerminateProject(aDoneProject);
        }

        public void TerminateSelectedProject()
        {
            if (myProjectBox.SelectedItem != null)
            {
                Project tempProject = myProjectBox.SelectedItem as Project;
                TerminateProject(tempProject);
            }
        }

        public void TerminateProject(Project aProject)
        {
            aProject.LevelUpWorkers();
            aProject.ResetWorkersWork();
            myProjectBox.Items.Remove(aProject);
            myProjects.Remove(aProject);
            DisplayProjectInfo();
            UpdateCosts();
        }

        public void AssignWorkers()
        {
            if (myProjectBox.SelectedItem != null)
            {
                Project tempProject = myProjectBox.SelectedItem as Project;
                foreach (ListViewItem iDerp in myWorkerList.SelectedItems)
                {
                    Worker tempWorker = iDerp.Tag as Worker;

                    tempProject.AssignWorker(tempWorker);
                }
            }
        }

        public void RemoveWorkersFromProjects()
        {
            if (myWorkerList.SelectedItems != null)
            {
                foreach (ListViewItem iWorker in myWorkerList.SelectedItems)
                {
                    Worker tempWorker = iWorker.Tag as Worker;
                    RemoveWorkerFromProject(tempWorker);
                }
            }
        }

        public int WorkerExpenses()
        {
            int salaries = 0;

            foreach (Worker iWorker in myWorkers)
            {
                salaries += iWorker.Salary;
            }

            return salaries;
        }

        public void HireWorker()
        {
            if (myWorkers.Count < Rooms)
            {
                myWorkers.Add(new Worker());
                myWorkerList.Items.Add(myWorkers[myWorkers.Count - 1].Representation);
                UpdateCosts();
                UpdateRoomInformation();
            }
            else
            {
                myErrorPopup.ShowError("Not enough room for new workers");
            }
        }

        public void BuildMoreRooms()
        {
            if (Economy > 50)
            {
                Economy += -50;
                Rooms += 5;
                UpdateCosts();
            }
            else
            {
                myErrorPopup.ShowError("Not enough money to build new rooms");
            }
        }

        public void FireWorker()
        {
            foreach (ListViewItem iWorker in myWorkerList.SelectedItems)
            {
                Worker tempWorker = iWorker.Tag as Worker;
                RemoveWorkerFromProject(tempWorker);
                myWorkerList.Items.Remove(iWorker);
                myWorkers.Remove(tempWorker);
            }
            UpdateCosts();
            UpdateRoomInformation();
        }

        private void RemoveWorkerFromProject(Worker aWorker)
        {
            if (aWorker.Work != null)
            {
                aWorker.Work.RemoveWorker(aWorker);
            }
        }
        
        private int Rooms
        {
            get
            {
                return myRoomAmount;
            }

            set
            {
                myRoomAmount = value;
                UpdateRoomInformation();
            }
        }

        public string Name
        {
            set
            {
                myName = value;
                myStudioNameLabel.Text = myName;
            }

            get
            {
                return myName;
            }
        }

        public int Economy
        {
            get
            {
                return myMoney;
            }
            set
            {
                myMoney = value;
                myEconomyLabel.Text = "Economy: " + Economy.ToString();
            }
        }

        private Random myRandomizer;

        private List<Worker> myWorkers;
        private ListView myWorkerList;

        private List<Project> myProjects;
        private ListBox myProjectBox;

        private List<PublishedGame> myGames;
        private ListBox myGamesBox;

        private Label myProjectInfo;
        private Label myGameInfo;
        private Label myStudioNameLabel;
        private Label myCostsLabel;
        private Label myEconomyLabel;
        private Label myRoomLabel;


        private ProgressBar myProjectProgressBar;

        private string myName;
        private int myMoney;
        private int myRoomAmount;

        ErrorPopup myErrorPopup;

        private int myRentCost
        {
            get
            {
                return myRoomAmount * 50;
            }
        }
    }
}
