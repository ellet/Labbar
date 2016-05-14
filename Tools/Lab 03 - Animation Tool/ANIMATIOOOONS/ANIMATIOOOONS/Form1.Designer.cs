namespace ANIMATIOOOONS
{
    partial class Form1
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
            this.components = new System.ComponentModel.Container();
            this.MenuStrip = new System.Windows.Forms.MenuStrip();
            this.ToolStripFile = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolStripLoad = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolStripSave = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolStripMenuItemLoadSpritesheet = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolStripHalp = new System.Windows.Forms.ToolStripMenuItem();
            this.GroupBoxSpritesheet = new System.Windows.Forms.GroupBox();
            this.GroupBoxEditWithFrameSize = new System.Windows.Forms.GroupBox();
            this.NumericUpDownHeightInPixels = new System.Windows.Forms.NumericUpDown();
            this.LabelHeightInPixels = new System.Windows.Forms.Label();
            this.LabelFrameWidthPixels = new System.Windows.Forms.Label();
            this.NumericUpDownWidthInPixels = new System.Windows.Forms.NumericUpDown();
            this.LabelFPS = new System.Windows.Forms.Label();
            this.NumericUpDownFPS = new System.Windows.Forms.NumericUpDown();
            this.LabelSpritesheetStyle = new System.Windows.Forms.Label();
            this.ComboBoxAnimationSettings = new System.Windows.Forms.ComboBox();
            this.GroupBoxEditWithColumnRows = new System.Windows.Forms.GroupBox();
            this.LabelAnimationColumns = new System.Windows.Forms.Label();
            this.LabelAnimationRows = new System.Windows.Forms.Label();
            this.NumericUpDownColumns = new System.Windows.Forms.NumericUpDown();
            this.NumericUpDownRows = new System.Windows.Forms.NumericUpDown();
            this.GroupBoxAnimation = new System.Windows.Forms.GroupBox();
            this.ButtonPause = new System.Windows.Forms.Button();
            this.ButtonPlayAnimation = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.notifyIcon1 = new System.Windows.Forms.NotifyIcon(this.components);
            this.LabelSpritesheetFilepath = new System.Windows.Forms.Label();
            this.animation1 = new ANIMATIOOOONS.Classes.Animation();
            this.SpriteViewerSpritesheet = new ANIMATIOOOONS.Classes.SpriteViewer();
            this.MenuStrip.SuspendLayout();
            this.GroupBoxSpritesheet.SuspendLayout();
            this.GroupBoxEditWithFrameSize.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NumericUpDownHeightInPixels)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.NumericUpDownWidthInPixels)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.NumericUpDownFPS)).BeginInit();
            this.GroupBoxEditWithColumnRows.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NumericUpDownColumns)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.NumericUpDownRows)).BeginInit();
            this.GroupBoxAnimation.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.animation1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.SpriteViewerSpritesheet)).BeginInit();
            this.SuspendLayout();
            // 
            // MenuStrip
            // 
            this.MenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ToolStripFile,
            this.ToolStripHalp});
            this.MenuStrip.Location = new System.Drawing.Point(0, 0);
            this.MenuStrip.Name = "MenuStrip";
            this.MenuStrip.Size = new System.Drawing.Size(884, 24);
            this.MenuStrip.TabIndex = 0;
            this.MenuStrip.Text = "Menu?";
            // 
            // ToolStripFile
            // 
            this.ToolStripFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ToolStripLoad,
            this.ToolStripSave,
            this.ToolStripMenuItemLoadSpritesheet});
            this.ToolStripFile.Name = "ToolStripFile";
            this.ToolStripFile.Size = new System.Drawing.Size(37, 20);
            this.ToolStripFile.Text = "File";
            // 
            // ToolStripLoad
            // 
            this.ToolStripLoad.Name = "ToolStripLoad";
            this.ToolStripLoad.Size = new System.Drawing.Size(161, 22);
            this.ToolStripLoad.Text = "Open";
            this.ToolStripLoad.Click += new System.EventHandler(this.ToolStripLoad_Click);
            // 
            // ToolStripSave
            // 
            this.ToolStripSave.Name = "ToolStripSave";
            this.ToolStripSave.Size = new System.Drawing.Size(161, 22);
            this.ToolStripSave.Text = "Save";
            this.ToolStripSave.Click += new System.EventHandler(this.ToolStripSave_Click);
            // 
            // ToolStripMenuItemLoadSpritesheet
            // 
            this.ToolStripMenuItemLoadSpritesheet.Name = "ToolStripMenuItemLoadSpritesheet";
            this.ToolStripMenuItemLoadSpritesheet.Size = new System.Drawing.Size(161, 22);
            this.ToolStripMenuItemLoadSpritesheet.Text = "Load Spritesheet";
            this.ToolStripMenuItemLoadSpritesheet.Click += new System.EventHandler(this.ToolStripMenuItemLoadSpritesheet_Click);
            // 
            // ToolStripHalp
            // 
            this.ToolStripHalp.Name = "ToolStripHalp";
            this.ToolStripHalp.Size = new System.Drawing.Size(44, 20);
            this.ToolStripHalp.Text = "Halp";
            // 
            // GroupBoxSpritesheet
            // 
            this.GroupBoxSpritesheet.Controls.Add(this.LabelSpritesheetFilepath);
            this.GroupBoxSpritesheet.Controls.Add(this.GroupBoxEditWithFrameSize);
            this.GroupBoxSpritesheet.Controls.Add(this.LabelFPS);
            this.GroupBoxSpritesheet.Controls.Add(this.NumericUpDownFPS);
            this.GroupBoxSpritesheet.Controls.Add(this.LabelSpritesheetStyle);
            this.GroupBoxSpritesheet.Controls.Add(this.ComboBoxAnimationSettings);
            this.GroupBoxSpritesheet.Controls.Add(this.GroupBoxEditWithColumnRows);
            this.GroupBoxSpritesheet.Controls.Add(this.SpriteViewerSpritesheet);
            this.GroupBoxSpritesheet.Location = new System.Drawing.Point(12, 27);
            this.GroupBoxSpritesheet.Name = "GroupBoxSpritesheet";
            this.GroupBoxSpritesheet.Size = new System.Drawing.Size(434, 418);
            this.GroupBoxSpritesheet.TabIndex = 1;
            this.GroupBoxSpritesheet.TabStop = false;
            this.GroupBoxSpritesheet.Text = "Spritesheet";
            // 
            // GroupBoxEditWithFrameSize
            // 
            this.GroupBoxEditWithFrameSize.Controls.Add(this.NumericUpDownHeightInPixels);
            this.GroupBoxEditWithFrameSize.Controls.Add(this.LabelHeightInPixels);
            this.GroupBoxEditWithFrameSize.Controls.Add(this.LabelFrameWidthPixels);
            this.GroupBoxEditWithFrameSize.Controls.Add(this.NumericUpDownWidthInPixels);
            this.GroupBoxEditWithFrameSize.Location = new System.Drawing.Point(6, 74);
            this.GroupBoxEditWithFrameSize.Name = "GroupBoxEditWithFrameSize";
            this.GroupBoxEditWithFrameSize.Size = new System.Drawing.Size(157, 139);
            this.GroupBoxEditWithFrameSize.TabIndex = 7;
            this.GroupBoxEditWithFrameSize.TabStop = false;
            this.GroupBoxEditWithFrameSize.Text = "Set with Frame Size";
            // 
            // NumericUpDownHeightInPixels
            // 
            this.NumericUpDownHeightInPixels.Location = new System.Drawing.Point(12, 80);
            this.NumericUpDownHeightInPixels.Maximum = new decimal(new int[] {
            2048,
            0,
            0,
            0});
            this.NumericUpDownHeightInPixels.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.NumericUpDownHeightInPixels.Name = "NumericUpDownHeightInPixels";
            this.NumericUpDownHeightInPixels.Size = new System.Drawing.Size(62, 20);
            this.NumericUpDownHeightInPixels.TabIndex = 3;
            this.NumericUpDownHeightInPixels.Value = new decimal(new int[] {
            256,
            0,
            0,
            0});
            this.NumericUpDownHeightInPixels.ValueChanged += new System.EventHandler(this.NumericUpDownHeightInPixels_ValueChanged);
            // 
            // LabelHeightInPixels
            // 
            this.LabelHeightInPixels.AutoSize = true;
            this.LabelHeightInPixels.Location = new System.Drawing.Point(9, 63);
            this.LabelHeightInPixels.Name = "LabelHeightInPixels";
            this.LabelHeightInPixels.Size = new System.Drawing.Size(78, 13);
            this.LabelHeightInPixels.TabIndex = 2;
            this.LabelHeightInPixels.Text = "Height in pixels";
            // 
            // LabelFrameWidthPixels
            // 
            this.LabelFrameWidthPixels.AutoSize = true;
            this.LabelFrameWidthPixels.Location = new System.Drawing.Point(9, 24);
            this.LabelFrameWidthPixels.Name = "LabelFrameWidthPixels";
            this.LabelFrameWidthPixels.Size = new System.Drawing.Size(75, 13);
            this.LabelFrameWidthPixels.TabIndex = 1;
            this.LabelFrameWidthPixels.Text = "Width in pixels";
            // 
            // NumericUpDownWidthInPixels
            // 
            this.NumericUpDownWidthInPixels.Location = new System.Drawing.Point(12, 40);
            this.NumericUpDownWidthInPixels.Maximum = new decimal(new int[] {
            2048,
            0,
            0,
            0});
            this.NumericUpDownWidthInPixels.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.NumericUpDownWidthInPixels.Name = "NumericUpDownWidthInPixels";
            this.NumericUpDownWidthInPixels.Size = new System.Drawing.Size(62, 20);
            this.NumericUpDownWidthInPixels.TabIndex = 0;
            this.NumericUpDownWidthInPixels.Value = new decimal(new int[] {
            256,
            0,
            0,
            0});
            this.NumericUpDownWidthInPixels.ValueChanged += new System.EventHandler(this.NumericUpDownWidthInPixels_ValueChanged);
            // 
            // LabelFPS
            // 
            this.LabelFPS.AutoSize = true;
            this.LabelFPS.Location = new System.Drawing.Point(8, 224);
            this.LabelFPS.Name = "LabelFPS";
            this.LabelFPS.Size = new System.Drawing.Size(99, 13);
            this.LabelFPS.TabIndex = 6;
            this.LabelFPS.Text = "Frames per Second";
            // 
            // NumericUpDownFPS
            // 
            this.NumericUpDownFPS.Location = new System.Drawing.Point(18, 240);
            this.NumericUpDownFPS.Maximum = new decimal(new int[] {
            120,
            0,
            0,
            0});
            this.NumericUpDownFPS.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.NumericUpDownFPS.Name = "NumericUpDownFPS";
            this.NumericUpDownFPS.Size = new System.Drawing.Size(44, 20);
            this.NumericUpDownFPS.TabIndex = 5;
            this.NumericUpDownFPS.Value = new decimal(new int[] {
            24,
            0,
            0,
            0});
            this.NumericUpDownFPS.ValueChanged += new System.EventHandler(this.numericUpDown1_ValueChanged);
            // 
            // LabelSpritesheetStyle
            // 
            this.LabelSpritesheetStyle.AllowDrop = true;
            this.LabelSpritesheetStyle.AutoSize = true;
            this.LabelSpritesheetStyle.Location = new System.Drawing.Point(15, 28);
            this.LabelSpritesheetStyle.Name = "LabelSpritesheetStyle";
            this.LabelSpritesheetStyle.Size = new System.Drawing.Size(65, 13);
            this.LabelSpritesheetStyle.TabIndex = 4;
            this.LabelSpritesheetStyle.Text = "Editing Style";
            // 
            // ComboBoxAnimationSettings
            // 
            this.ComboBoxAnimationSettings.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ComboBoxAnimationSettings.FormattingEnabled = true;
            this.ComboBoxAnimationSettings.Items.AddRange(new object[] {
            "Size of a Frame",
            "Columns & Rows"});
            this.ComboBoxAnimationSettings.Location = new System.Drawing.Point(15, 47);
            this.ComboBoxAnimationSettings.Name = "ComboBoxAnimationSettings";
            this.ComboBoxAnimationSettings.Size = new System.Drawing.Size(139, 21);
            this.ComboBoxAnimationSettings.TabIndex = 3;
            this.ComboBoxAnimationSettings.SelectedIndexChanged += new System.EventHandler(this.ComboBoxAnimationSettings_SelectedIndexChanged);
            // 
            // GroupBoxEditWithColumnRows
            // 
            this.GroupBoxEditWithColumnRows.Controls.Add(this.LabelAnimationColumns);
            this.GroupBoxEditWithColumnRows.Controls.Add(this.LabelAnimationRows);
            this.GroupBoxEditWithColumnRows.Controls.Add(this.NumericUpDownColumns);
            this.GroupBoxEditWithColumnRows.Controls.Add(this.NumericUpDownRows);
            this.GroupBoxEditWithColumnRows.Location = new System.Drawing.Point(6, 74);
            this.GroupBoxEditWithColumnRows.Name = "GroupBoxEditWithColumnRows";
            this.GroupBoxEditWithColumnRows.Size = new System.Drawing.Size(157, 137);
            this.GroupBoxEditWithColumnRows.TabIndex = 3;
            this.GroupBoxEditWithColumnRows.TabStop = false;
            this.GroupBoxEditWithColumnRows.Text = "Set with Columns and Rows";
            this.GroupBoxEditWithColumnRows.Visible = false;
            // 
            // LabelAnimationColumns
            // 
            this.LabelAnimationColumns.AutoSize = true;
            this.LabelAnimationColumns.Location = new System.Drawing.Point(9, 71);
            this.LabelAnimationColumns.Name = "LabelAnimationColumns";
            this.LabelAnimationColumns.Size = new System.Drawing.Size(97, 13);
            this.LabelAnimationColumns.TabIndex = 5;
            this.LabelAnimationColumns.Text = "# Columns in sheet";
            // 
            // LabelAnimationRows
            // 
            this.LabelAnimationRows.AutoSize = true;
            this.LabelAnimationRows.Location = new System.Drawing.Point(9, 32);
            this.LabelAnimationRows.Name = "LabelAnimationRows";
            this.LabelAnimationRows.Size = new System.Drawing.Size(84, 13);
            this.LabelAnimationRows.TabIndex = 4;
            this.LabelAnimationRows.Text = "# Rows in sheet";
            // 
            // NumericUpDownColumns
            // 
            this.NumericUpDownColumns.Location = new System.Drawing.Point(12, 87);
            this.NumericUpDownColumns.Maximum = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.NumericUpDownColumns.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.NumericUpDownColumns.Name = "NumericUpDownColumns";
            this.NumericUpDownColumns.Size = new System.Drawing.Size(44, 20);
            this.NumericUpDownColumns.TabIndex = 2;
            this.NumericUpDownColumns.Value = new decimal(new int[] {
            4,
            0,
            0,
            0});
            this.NumericUpDownColumns.ValueChanged += new System.EventHandler(this.NumericUpDownColumns_ValueChanged);
            // 
            // NumericUpDownRows
            // 
            this.NumericUpDownRows.Location = new System.Drawing.Point(12, 48);
            this.NumericUpDownRows.Maximum = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.NumericUpDownRows.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.NumericUpDownRows.Name = "NumericUpDownRows";
            this.NumericUpDownRows.Size = new System.Drawing.Size(44, 20);
            this.NumericUpDownRows.TabIndex = 3;
            this.NumericUpDownRows.Value = new decimal(new int[] {
            4,
            0,
            0,
            0});
            this.NumericUpDownRows.ValueChanged += new System.EventHandler(this.NumericUpDownRows_ValueChanged);
            // 
            // GroupBoxAnimation
            // 
            this.GroupBoxAnimation.Controls.Add(this.animation1);
            this.GroupBoxAnimation.Controls.Add(this.ButtonPause);
            this.GroupBoxAnimation.Controls.Add(this.ButtonPlayAnimation);
            this.GroupBoxAnimation.Location = new System.Drawing.Point(452, 27);
            this.GroupBoxAnimation.Name = "GroupBoxAnimation";
            this.GroupBoxAnimation.Size = new System.Drawing.Size(423, 511);
            this.GroupBoxAnimation.TabIndex = 2;
            this.GroupBoxAnimation.TabStop = false;
            this.GroupBoxAnimation.Text = "Animation";
            // 
            // ButtonPause
            // 
            this.ButtonPause.Location = new System.Drawing.Point(337, 428);
            this.ButtonPause.Name = "ButtonPause";
            this.ButtonPause.Size = new System.Drawing.Size(75, 32);
            this.ButtonPause.TabIndex = 2;
            this.ButtonPause.Text = "Pause";
            this.ButtonPause.UseVisualStyleBackColor = true;
            this.ButtonPause.Click += new System.EventHandler(this.ButtonPause_Click);
            // 
            // ButtonPlayAnimation
            // 
            this.ButtonPlayAnimation.Location = new System.Drawing.Point(337, 464);
            this.ButtonPlayAnimation.Name = "ButtonPlayAnimation";
            this.ButtonPlayAnimation.Size = new System.Drawing.Size(75, 39);
            this.ButtonPlayAnimation.TabIndex = 1;
            this.ButtonPlayAnimation.Text = "Play";
            this.ButtonPlayAnimation.UseVisualStyleBackColor = true;
            this.ButtonPlayAnimation.Click += new System.EventHandler(this.ButtonPlayAnimation_Click);
            // 
            // timer1
            // 
            this.timer1.Interval = 16;
            this.timer1.Tick += new System.EventHandler(this.TimerTicked);
            // 
            // notifyIcon1
            // 
            this.notifyIcon1.Text = "notifyIcon1";
            this.notifyIcon1.Visible = true;
            // 
            // LabelSpritesheetFilepath
            // 
            this.LabelSpritesheetFilepath.AutoSize = true;
            this.LabelSpritesheetFilepath.Location = new System.Drawing.Point(15, 289);
            this.LabelSpritesheetFilepath.Name = "LabelSpritesheetFilepath";
            this.LabelSpritesheetFilepath.Size = new System.Drawing.Size(100, 13);
            this.LabelSpritesheetFilepath.TabIndex = 8;
            this.LabelSpritesheetFilepath.Text = "Spritesheet Filepath";
            // 
            // animation1
            // 
            this.animation1.Location = new System.Drawing.Point(12, 18);
            this.animation1.Name = "animation1";
            this.animation1.Size = new System.Drawing.Size(400, 400);
            this.animation1.TabIndex = 3;
            this.animation1.TabStop = false;
            // 
            // SpriteViewerSpritesheet
            // 
            this.SpriteViewerSpritesheet.Location = new System.Drawing.Point(169, 18);
            this.SpriteViewerSpritesheet.Name = "SpriteViewerSpritesheet";
            this.SpriteViewerSpritesheet.Size = new System.Drawing.Size(256, 256);
            this.SpriteViewerSpritesheet.TabIndex = 2;
            this.SpriteViewerSpritesheet.TabStop = false;
            this.SpriteViewerSpritesheet.Click += new System.EventHandler(this.SpriteViewerSpritesheet_Click);
            this.SpriteViewerSpritesheet.Paint += new System.Windows.Forms.PaintEventHandler(this.testDrawing);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(884, 543);
            this.Controls.Add(this.GroupBoxAnimation);
            this.Controls.Add(this.GroupBoxSpritesheet);
            this.Controls.Add(this.MenuStrip);
            this.MainMenuStrip = this.MenuStrip;
            this.Name = "Form1";
            this.MenuStrip.ResumeLayout(false);
            this.MenuStrip.PerformLayout();
            this.GroupBoxSpritesheet.ResumeLayout(false);
            this.GroupBoxSpritesheet.PerformLayout();
            this.GroupBoxEditWithFrameSize.ResumeLayout(false);
            this.GroupBoxEditWithFrameSize.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NumericUpDownHeightInPixels)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.NumericUpDownWidthInPixels)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.NumericUpDownFPS)).EndInit();
            this.GroupBoxEditWithColumnRows.ResumeLayout(false);
            this.GroupBoxEditWithColumnRows.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NumericUpDownColumns)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.NumericUpDownRows)).EndInit();
            this.GroupBoxAnimation.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.animation1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.SpriteViewerSpritesheet)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip MenuStrip;
        private System.Windows.Forms.ToolStripMenuItem ToolStripFile;
        private System.Windows.Forms.ToolStripMenuItem ToolStripLoad;
        private System.Windows.Forms.ToolStripMenuItem ToolStripSave;
        private System.Windows.Forms.ToolStripMenuItem ToolStripHalp;
        private System.Windows.Forms.GroupBox GroupBoxSpritesheet;
        private Classes.SpriteViewer SpriteViewerSpritesheet;
        private System.Windows.Forms.Label LabelAnimationColumns;
        private System.Windows.Forms.Label LabelAnimationRows;
        private System.Windows.Forms.NumericUpDown NumericUpDownRows;
        private System.Windows.Forms.NumericUpDown NumericUpDownColumns;
        private System.Windows.Forms.GroupBox GroupBoxAnimation;
        private System.Windows.Forms.Button ButtonPause;
        private System.Windows.Forms.Button ButtonPlayAnimation;
        private Classes.Animation animation1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label LabelFPS;
        private System.Windows.Forms.NumericUpDown NumericUpDownFPS;
        private System.Windows.Forms.Label LabelSpritesheetStyle;
        private System.Windows.Forms.ComboBox ComboBoxAnimationSettings;
        private System.Windows.Forms.GroupBox GroupBoxEditWithColumnRows;
        private System.Windows.Forms.GroupBox GroupBoxEditWithFrameSize;
        private System.Windows.Forms.NotifyIcon notifyIcon1;
        private System.Windows.Forms.NumericUpDown NumericUpDownWidthInPixels;
        private System.Windows.Forms.NumericUpDown NumericUpDownHeightInPixels;
        private System.Windows.Forms.Label LabelHeightInPixels;
        private System.Windows.Forms.Label LabelFrameWidthPixels;
        private System.Windows.Forms.ToolStripMenuItem ToolStripMenuItemLoadSpritesheet;
        private System.Windows.Forms.Label LabelSpritesheetFilepath;
    }
}

