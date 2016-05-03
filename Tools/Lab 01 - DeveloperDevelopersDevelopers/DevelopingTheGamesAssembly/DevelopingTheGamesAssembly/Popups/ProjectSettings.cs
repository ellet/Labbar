using DevelopingTheGamesAssembly.StudioTheGame;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DevelopingTheGamesAssembly.Popups
{
    public partial class ProjectSettings : Form
    {
        private Studio myStudio;
        private ErrorPopup myErrorPopup;

        public ProjectSettings(Studio aStudio)
        {
            InitializeComponent();
            myStudio = aStudio;

            KeyPreview = true;

            myErrorPopup = new ErrorPopup();
        }

        private void ButtonCreateProject_Click(object sender, EventArgs e)
        {
            CreateProject();
        }

        private void CreateProject()
        {
            Project tempProject = new Project();

            if (TextBoxProjectName.Text == "")
            {
                myErrorPopup.ShowError("Project Must have a project name", this);
                return;
            }

            tempProject.ProjectName = TextBoxProjectName.Text;
            tempProject.Difficulty = BarDifficulty.Value;


            myStudio.StartProject(tempProject);
            Hide();
        }

        private void ButtonCancel_Click(object sender, EventArgs e)
        {
            Hide();
        }
    }
}