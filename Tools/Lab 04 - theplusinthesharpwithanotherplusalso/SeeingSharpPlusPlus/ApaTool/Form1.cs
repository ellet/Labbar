using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ApaTool
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            myCard = new WrapperClass();
        }

        private void buttonAssign_Click(object sender, EventArgs e)
        {
            myCard.SetApaToCard((int)numericUpDownApa.Value);
            labelValue.Text = myCard.GetApaFromCard().ToString();
        }

        private void buttonAssignName_Click(object sender, EventArgs e)
        {
            myCard.SetTextyToCard(textBoxApaName.Text);
            labelApaName.Text = myCard.GetTextyFromCard();
        }

        private WrapperClass myCard;
    }
}
