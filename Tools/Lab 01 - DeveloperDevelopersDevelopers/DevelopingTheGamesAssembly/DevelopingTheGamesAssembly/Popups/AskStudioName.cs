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
    public partial class AskStudioName : Form
    {
        private Studio myStudio;
        private ErrorPopup myErrorPopup;

        public AskStudioName(Studio aStudio)
        {
            InitializeComponent();
            myStudio = aStudio;
            myErrorPopup = new ErrorPopup();
        }

        private void ButtonNameStudio_Click(object sender, EventArgs e)
        {
            if (textBoxStudioName.Text == "")
            {
                myErrorPopup.ShowError("Studio must have a name", this);
                return;
            }

            myStudio.Name = textBoxStudioName.Text;
            Hide();
        }
    }
}
