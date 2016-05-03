using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UsefulToolForGameProjectYes
{
    public partial class GameSettings : Form
    {
        public GameSettings()
        {
            InitializeComponent();

            string text = System.IO.File.ReadAllText("JSON/testings.json");

            mySetup = JsonConvert.DeserializeObject<GameSetup>(text);
        }

        private void TESTY()
        {
            string output = JsonConvert.SerializeObject(mySetup);

            const string Folder = "JSON";
            Directory.CreateDirectory(Folder);

            System.IO.File.WriteAllText("JSON/testings.json", output);
            //myOther = JsonConvert.DeserializeObject<GameSetup>(output);
        }

        private void ComboBoxResolution_SelectedIndexChanged(object sender, EventArgs e)
        {

            mySetup.ResolutoinSettings = 
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

        private GameSetup mySetup;

        private void button1_Click(object sender, EventArgs e)
        {
            TESTY();
        }
    }
}
