using ANIMATIOOOONS.Classes;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
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
            SpriteViewerSpritesheet.Init(animation1);
            SpriteViewerSpritesheet.SetImage("..\\Sprites\\wut.png");

            SpriteViewerSpritesheet.AnimationTimer = timer1;
            ComboBoxAnimationSettings.SelectedItem = "Size of a Frame";
            SpriteViewerSpritesheet.testDrawStuff();
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
            SpriteViewerSpritesheet.Rows = (int)NumericUpDownRows.Value;
            SpriteViewerSpritesheet.testDrawStuff();

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

        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            decimal millisecond = 1000 / NumericUpDownFPS.Value;
            SpriteViewerSpritesheet.FrameInterval = (int)millisecond;
        }

        private void ComboBoxAnimationSettings_SelectedIndexChanged(object sender, EventArgs e)
        {
            //Size of a Frame
            //Columns & Rows
            if (ComboBoxAnimationSettings.SelectedItem.ToString() == "Size of a Frame")
            {
                GroupBoxEditWithColumnRows.Hide();
                GroupBoxEditWithFrameSize.Show();
                SpriteViewerSpritesheet.FrameStyle = Classes.eFrameStyle.eFrameSize;
                SpriteViewerSpritesheet.testDrawStuff();
            }
            else
            {
                GroupBoxEditWithColumnRows.Show();
                GroupBoxEditWithFrameSize.Hide();
                SpriteViewerSpritesheet.FrameStyle = Classes.eFrameStyle.eColumnRows;
                SpriteViewerSpritesheet.testDrawStuff();
            }
        }

        private void NumericUpDownWidthInPixels_ValueChanged(object sender, EventArgs e)
        {
            SpriteViewerSpritesheet.FrameSizeWidth = (int)NumericUpDownWidthInPixels.Value;
            SpriteViewerSpritesheet.testDrawStuff();
        }

        private void NumericUpDownHeightInPixels_ValueChanged(object sender, EventArgs e)
        {
            SpriteViewerSpritesheet.FrameSizeHeight = (int)NumericUpDownHeightInPixels.Value;
            SpriteViewerSpritesheet.testDrawStuff();
        }

        private void ButtonPause_Click(object sender, EventArgs e)
        {
            SpriteViewerSpritesheet.StopAnimation();
        }

        private void ToolStripLoad_Click(object sender, EventArgs e)
        {
            OpenFileDialog tempLoadFileDialog = new OpenFileDialog();
            string folderPath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + "\\JSON";
            System.IO.Directory.CreateDirectory(folderPath);
            tempLoadFileDialog.InitialDirectory = folderPath;
            tempLoadFileDialog.RestoreDirectory = false;
            tempLoadFileDialog.Filter = "Json Files(*.json) | *.json";
            tempLoadFileDialog.ShowDialog(this);

            if (tempLoadFileDialog.FileName != "")
            {
                AnimationInfo temp = new AnimationInfo();
                temp = SpriteViewerSpritesheet.LoadAnimation(tempLoadFileDialog.FileName);

                NumericUpDownFPS.Value = (decimal)(1000 / temp.FrameIntervalMilliseconds);
                NumericUpDownHeightInPixels.Value = (decimal)temp.FrameWidthHeight.Y;
                NumericUpDownWidthInPixels.Value = (decimal)temp.FrameWidthHeight.X;
                LabelSpritesheetFilepath.Text = temp.ImagePath;
                SpriteViewerSpritesheet.SetImage(temp.ImagePath);
                SpriteViewerSpritesheet.testDrawStuff();
            }
        }

        private void ToolStripSave_Click(object sender, EventArgs e)
        {

            SaveFileDialog tempSaveFileDialog = new SaveFileDialog();
            string folderPath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + "\\JSON";
            System.IO.Directory.CreateDirectory(folderPath);
            tempSaveFileDialog.InitialDirectory = folderPath;
            tempSaveFileDialog.Filter = "Json Files(*.json) | *.json";
            tempSaveFileDialog.ShowDialog(this);

            if (tempSaveFileDialog.FileName != "")
            {
                SpriteViewerSpritesheet.SaveAnimation(tempSaveFileDialog.FileName);
            }
        }

        private void ToolStripMenuItemLoadSpritesheet_Click(object sender, EventArgs e)
        {
            OpenFileDialog tempLoadFileDialog = new OpenFileDialog();
            string folderPath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
            tempLoadFileDialog.InitialDirectory = folderPath;
            tempLoadFileDialog.RestoreDirectory = false;
            tempLoadFileDialog.Filter = "Png Files(*.png) | *.png";
            tempLoadFileDialog.ShowDialog(this);

            if (tempLoadFileDialog.FileName != "")
            {
                SpriteViewerSpritesheet.SetImage(tempLoadFileDialog.FileName);
                LabelSpritesheetFilepath.Text = tempLoadFileDialog.FileName;
            }
        }
    }
}
