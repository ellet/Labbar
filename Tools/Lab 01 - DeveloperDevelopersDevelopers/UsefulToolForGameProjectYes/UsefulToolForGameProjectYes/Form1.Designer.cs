namespace UsefulToolForGameProjectYes
{
    partial class GameSettings
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.TabWindow = new System.Windows.Forms.TabControl();
            this.TabGameSettings = new System.Windows.Forms.TabPage();
            this.button1 = new System.Windows.Forms.Button();
            this.GroupBoxMisc = new System.Windows.Forms.GroupBox();
            this.CheckBoxMute = new System.Windows.Forms.CheckBox();
            this.CheckBoxSkipSplashScreen = new System.Windows.Forms.CheckBox();
            this.CheckBoxSkipIntro = new System.Windows.Forms.CheckBox();
            this.GroupBoxResolution = new System.Windows.Forms.GroupBox();
            this.CheckBoxFullscreen = new System.Windows.Forms.CheckBox();
            this.ComboBoxResolution = new System.Windows.Forms.ComboBox();
            this.TabLDMode = new System.Windows.Forms.TabPage();
            this.TabWindow.SuspendLayout();
            this.TabGameSettings.SuspendLayout();
            this.GroupBoxMisc.SuspendLayout();
            this.GroupBoxResolution.SuspendLayout();
            this.SuspendLayout();
            // 
            // TabWindow
            // 
            this.TabWindow.Controls.Add(this.TabGameSettings);
            this.TabWindow.Controls.Add(this.TabLDMode);
            this.TabWindow.Location = new System.Drawing.Point(2, 3);
            this.TabWindow.Name = "TabWindow";
            this.TabWindow.SelectedIndex = 0;
            this.TabWindow.Size = new System.Drawing.Size(788, 423);
            this.TabWindow.TabIndex = 0;
            // 
            // TabGameSettings
            // 
            this.TabGameSettings.Controls.Add(this.button1);
            this.TabGameSettings.Controls.Add(this.GroupBoxMisc);
            this.TabGameSettings.Controls.Add(this.GroupBoxResolution);
            this.TabGameSettings.Location = new System.Drawing.Point(4, 22);
            this.TabGameSettings.Name = "TabGameSettings";
            this.TabGameSettings.Padding = new System.Windows.Forms.Padding(3);
            this.TabGameSettings.Size = new System.Drawing.Size(780, 397);
            this.TabGameSettings.TabIndex = 0;
            this.TabGameSettings.Text = "Game Settings";
            this.TabGameSettings.UseVisualStyleBackColor = true;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(379, 216);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 2;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // GroupBoxMisc
            // 
            this.GroupBoxMisc.Controls.Add(this.CheckBoxMute);
            this.GroupBoxMisc.Controls.Add(this.CheckBoxSkipSplashScreen);
            this.GroupBoxMisc.Controls.Add(this.CheckBoxSkipIntro);
            this.GroupBoxMisc.Location = new System.Drawing.Point(6, 106);
            this.GroupBoxMisc.Name = "GroupBoxMisc";
            this.GroupBoxMisc.Size = new System.Drawing.Size(188, 105);
            this.GroupBoxMisc.TabIndex = 1;
            this.GroupBoxMisc.TabStop = false;
            this.GroupBoxMisc.Text = "Misc.";
            // 
            // CheckBoxMute
            // 
            this.CheckBoxMute.AutoSize = true;
            this.CheckBoxMute.Checked = true;
            this.CheckBoxMute.CheckState = System.Windows.Forms.CheckState.Checked;
            this.CheckBoxMute.Location = new System.Drawing.Point(16, 75);
            this.CheckBoxMute.Name = "CheckBoxMute";
            this.CheckBoxMute.Size = new System.Drawing.Size(103, 17);
            this.CheckBoxMute.TabIndex = 2;
            this.CheckBoxMute.Text = "Mute All Sounds";
            this.CheckBoxMute.UseVisualStyleBackColor = true;
            this.CheckBoxMute.CheckedChanged += new System.EventHandler(this.CheckBoxMute_CheckedChanged);
            // 
            // CheckBoxSkipSplashScreen
            // 
            this.CheckBoxSkipSplashScreen.AutoSize = true;
            this.CheckBoxSkipSplashScreen.Checked = true;
            this.CheckBoxSkipSplashScreen.CheckState = System.Windows.Forms.CheckState.Checked;
            this.CheckBoxSkipSplashScreen.Location = new System.Drawing.Point(16, 51);
            this.CheckBoxSkipSplashScreen.Name = "CheckBoxSkipSplashScreen";
            this.CheckBoxSkipSplashScreen.Size = new System.Drawing.Size(114, 17);
            this.CheckBoxSkipSplashScreen.TabIndex = 1;
            this.CheckBoxSkipSplashScreen.Text = "Skip Splashscreen";
            this.CheckBoxSkipSplashScreen.UseVisualStyleBackColor = true;
            this.CheckBoxSkipSplashScreen.CheckedChanged += new System.EventHandler(this.CheckBoxSkipSplashScreen_CheckedChanged);
            // 
            // CheckBoxSkipIntro
            // 
            this.CheckBoxSkipIntro.AutoSize = true;
            this.CheckBoxSkipIntro.Checked = true;
            this.CheckBoxSkipIntro.CheckState = System.Windows.Forms.CheckState.Checked;
            this.CheckBoxSkipIntro.Location = new System.Drawing.Point(16, 28);
            this.CheckBoxSkipIntro.Name = "CheckBoxSkipIntro";
            this.CheckBoxSkipIntro.Size = new System.Drawing.Size(71, 17);
            this.CheckBoxSkipIntro.TabIndex = 0;
            this.CheckBoxSkipIntro.Text = "Skip Intro";
            this.CheckBoxSkipIntro.UseVisualStyleBackColor = true;
            this.CheckBoxSkipIntro.CheckedChanged += new System.EventHandler(this.CheckBoxSkipIntro_CheckedChanged);
            // 
            // GroupBoxResolution
            // 
            this.GroupBoxResolution.Controls.Add(this.CheckBoxFullscreen);
            this.GroupBoxResolution.Controls.Add(this.ComboBoxResolution);
            this.GroupBoxResolution.Location = new System.Drawing.Point(6, 22);
            this.GroupBoxResolution.Name = "GroupBoxResolution";
            this.GroupBoxResolution.Size = new System.Drawing.Size(188, 78);
            this.GroupBoxResolution.TabIndex = 0;
            this.GroupBoxResolution.TabStop = false;
            this.GroupBoxResolution.Text = "Resolution";
            // 
            // CheckBoxFullscreen
            // 
            this.CheckBoxFullscreen.AutoSize = true;
            this.CheckBoxFullscreen.Location = new System.Drawing.Point(16, 46);
            this.CheckBoxFullscreen.Name = "CheckBoxFullscreen";
            this.CheckBoxFullscreen.Size = new System.Drawing.Size(74, 17);
            this.CheckBoxFullscreen.TabIndex = 1;
            this.CheckBoxFullscreen.Text = "Fullscreen";
            this.CheckBoxFullscreen.UseVisualStyleBackColor = true;
            this.CheckBoxFullscreen.CheckedChanged += new System.EventHandler(this.CheckBoxFullscreen_CheckedChanged);
            // 
            // ComboBoxResolution
            // 
            this.ComboBoxResolution.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ComboBoxResolution.FormattingEnabled = true;
            this.ComboBoxResolution.Location = new System.Drawing.Point(6, 19);
            this.ComboBoxResolution.Name = "ComboBoxResolution";
            this.ComboBoxResolution.Size = new System.Drawing.Size(174, 21);
            this.ComboBoxResolution.TabIndex = 0;
            this.ComboBoxResolution.SelectedIndexChanged += new System.EventHandler(this.ComboBoxResolution_SelectedIndexChanged);
            // 
            // TabLDMode
            // 
            this.TabLDMode.Location = new System.Drawing.Point(4, 22);
            this.TabLDMode.Name = "TabLDMode";
            this.TabLDMode.Padding = new System.Windows.Forms.Padding(3);
            this.TabLDMode.Size = new System.Drawing.Size(780, 397);
            this.TabLDMode.TabIndex = 1;
            this.TabLDMode.Text = "LD mode";
            this.TabLDMode.UseVisualStyleBackColor = true;
            // 
            // GameSettings
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(802, 429);
            this.Controls.Add(this.TabWindow);
            this.Name = "GameSettings";
            this.Text = "Game Settings";
            this.TabWindow.ResumeLayout(false);
            this.TabGameSettings.ResumeLayout(false);
            this.GroupBoxMisc.ResumeLayout(false);
            this.GroupBoxMisc.PerformLayout();
            this.GroupBoxResolution.ResumeLayout(false);
            this.GroupBoxResolution.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl TabWindow;
        private System.Windows.Forms.TabPage TabGameSettings;
        private System.Windows.Forms.GroupBox GroupBoxResolution;
        private System.Windows.Forms.CheckBox CheckBoxFullscreen;
        private System.Windows.Forms.TabPage TabLDMode;
        private System.Windows.Forms.ComboBox ComboBoxResolution;
        private System.Windows.Forms.GroupBox GroupBoxMisc;
        private System.Windows.Forms.CheckBox CheckBoxMute;
        private System.Windows.Forms.CheckBox CheckBoxSkipSplashScreen;
        private System.Windows.Forms.CheckBox CheckBoxSkipIntro;
        private System.Windows.Forms.Button button1;
    }
}

