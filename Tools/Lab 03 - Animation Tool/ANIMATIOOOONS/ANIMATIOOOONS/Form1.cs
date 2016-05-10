using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ANIMATIOOOONS
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            SpriteViewerSpritesheet.SetImage("..\\Sprites\\wut.png");

            SpriteViewerSpritesheet.AnimationTimer = timer1;
        }

        protected override void OnPaint(PaintEventArgs e)
        {            
            base.OnPaint(e);
            //SpriteViewerSpritesheet.testDrawStuff();
        }

        private void testDrawing(object sender, PaintEventArgs e)
        {

        }

        private void NumericUpDownRows_ValueChanged(object sender, EventArgs e)
        {

            SpriteViewerSpritesheet.testDrawStuff();
            SpriteViewerSpritesheet.Rows = (int)NumericUpDownRows.Value;
            
        }

        private void NumericUpDownColumns_ValueChanged(object sender, EventArgs e)
        {
            SpriteViewerSpritesheet.Columns = (int)NumericUpDownColumns.Value;
            SpriteViewerSpritesheet.testDrawStuff();
        }

        private void SpriteViewerSpritesheet_Click(object sender, EventArgs e)
        {
            SpriteViewerSpritesheet.SetActiveFrame(SpriteViewerSpritesheet.PointToClient(Cursor.Position));
        }

        private void ButtonPlayAnimation_Click(object sender, EventArgs e)
        {
            SpriteViewerSpritesheet.StartAnimation();
        }

        private void TimerTicked(object sender, EventArgs e)
        {
            SpriteViewerSpritesheet.PlayAnimation();
        }
    }
}
