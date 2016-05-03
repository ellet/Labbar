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
    public partial class ErrorPopup : Form
    {
        Form myParent;

        public ErrorPopup()
        {
            InitializeComponent();
            myParent = null;
        }

        public void SetParent(Form aParent)
        {
            myParent = aParent;
        }

        public void ShowError(string aErrorMessage)
        {
            labelErrorText.Text = aErrorMessage;
            ShowDialog(myParent);
        }

        public void ShowError(string aErrorMessage, Form aParentForm)
        {
            labelErrorText.Text = aErrorMessage;
            ShowDialog(aParentForm);
        }

        private void ButtonOk_Click(object sender, EventArgs e)
        {
            Hide();
        }
    }
}
