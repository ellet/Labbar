using Newtonsoft.Json;
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

namespace UsefulToolForGameProjectYes
{
    public enum eGameState
    {
        eMainMenu,
        eInGame,
        eLevelSelect,
        ePauseMenu,
        eOptionsMenu,
        eCredits
    }

    public partial class GameSettings : Form
    {
        

        public GameSettings()
        {
            InitializeComponent();
            InitResolution();

            ToolTip.SetToolTip(this.GroupBoxDebug, "Location originates in Bin, not C");
            ToolTip.SetToolTip(this.TextBoxDebuglogsDirectory, "Location originates in Bin, not C");
            ToolTip.SetToolTip(this.LabelDebugDirectory, "Location originates in Bin, not C");

            string text = System.IO.File.ReadAllText("JSON/testings.json");

            mySetup = JsonConvert.DeserializeObject<GameSetup>(text);
        }

        void InitResolution()
        {
            ComboBoxResolution.Items.Add(new Resolution(1920, 1080));
            ComboBoxResolution.Items.Add(new Resolution(600, 800));
        }

        private void SaveGameSettingsToFile(string aFilePath)
        {
            string output = JsonConvert.SerializeObject(mySetup);
            System.IO.File.WriteAllText(aFilePath, output);
        }

        private void LoadGameSettingsFromFile(string aFilePath)
        {
            string input = System.IO.File.ReadAllText(aFilePath);
            mySetup = JsonConvert.DeserializeObject<GameSetup>(input);
        }

        private void ComboBoxResolution_SelectedIndexChanged(object sender, EventArgs e)
        {
            mySetup.ResolutoinSettings = ComboBoxResolution.SelectedItem as Resolution;
        }

        private void CheckBoxFullscreen_CheckedChanged(object sender, EventArgs e)
        {
            mySetup.IsFullscreen = CheckBoxFullscreen.Checked;
        }

        private void CheckBoxSkipIntro_CheckedChanged(object sender, EventArgs e)
        {
            mySetup.SkipIntro = CheckBoxSkipIntro.Checked;
        }

        private void CheckBoxSkipSplashScreen_CheckedChanged(object sender, EventArgs e)
        {
            mySetup.SkipSplashscreen = CheckBoxSkipSplashScreen.Checked;
        }

        private void CheckBoxMute_CheckedChanged(object sender, EventArgs e)
        {
            mySetup.MuteAllSounds = CheckBoxMute.Checked;
        }

        private void buttonSave_Click(object sender, EventArgs e)
        {
            SaveFileDialog tempSaveFileDialog = new SaveFileDialog();
            tempSaveFileDialog.InitialDirectory = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + "/JSON";
            tempSaveFileDialog.Filter = "Json Files(*.json) | *.json";
            tempSaveFileDialog.ShowDialog(this);

            if (tempSaveFileDialog.FileName != "")
            {
                mySetup.StartingGameState = (int)GetSelectedGameState();
                SaveGameSettingsToFile(tempSaveFileDialog.FileName);
            }
        }


        private void buttonLoad_Click(object sender, EventArgs e)
        {
            OpenFileDialog tempLoadFileDialog = new OpenFileDialog();
            tempLoadFileDialog.InitialDirectory = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location + "/JSON");
            tempLoadFileDialog.Filter = "Json Files(*.json) | *.json";
            tempLoadFileDialog.ShowDialog(this);

            if (tempLoadFileDialog.FileName != "")
            {
                LoadGameSettingsFromFile(tempLoadFileDialog.FileName);
            }
        }

        private eGameState GetSelectedGameState()
        {
            if (RadioButtonGamestateMenu.Checked == true)
            {
                return eGameState.eMainMenu;
            }
            else if (RadioButtonGamestateInGame.Checked == true)
            {
                return eGameState.eInGame;
            }
            else if (RadioButtonLevelSelect.Checked == true)
            {
                return eGameState.eLevelSelect;
            }
            else if (RadioButtonGamestatePauseMenu.Checked == true)
            {
                return eGameState.ePauseMenu;
            }
            else if (RadioButtonGamestateOptionsMenu.Checked == true)
            {
                return eGameState.eOptionsMenu;
            }
            else
            {
                return eGameState.eCredits;
            }
        }

        private void ButtonHelp_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Hello!\n\nIf you think something is missing or that something is confusing among the options here, go tell your friendly neighborhood programmers about it, and we will modify the tool according to feedback.");
        }
        private GameSetup mySetup;

    }
}
