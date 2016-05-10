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
            this.ToolStripHalp = new System.Windows.Forms.ToolStripMenuItem();
            this.GroupBoxSpritesheet = new System.Windows.Forms.GroupBox();
            this.LabelAnimationColumns = new System.Windows.Forms.Label();
            this.LabelAnimationRows = new System.Windows.Forms.Label();
            this.NumericUpDownRows = new System.Windows.Forms.NumericUpDown();
            this.NumericUpDownColumns = new System.Windows.Forms.NumericUpDown();
            this.animation1 = new ANIMATIOOOONS.Classes.Animation();
            this.SpriteViewerSpritesheet = new ANIMATIOOOONS.Classes.SpriteViewer(this.animation1);
            this.GroupBoxAnimation = new System.Windows.Forms.GroupBox();
            this.ButtonPause = new System.Windows.Forms.Button();
            this.ButtonPlayAnimation = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.MenuStrip.SuspendLayout();
            this.GroupBoxSpritesheet.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NumericUpDownRows)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.NumericUpDownColumns)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.animation1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.SpriteViewerSpritesheet)).BeginInit();
            this.GroupBoxAnimation.SuspendLayout();
            this.SuspendLayout();
            // 
            // MenuStrip
            // 
            this.MenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ToolStripFile,
            this.ToolStripHalp});
            this.MenuStrip.Location = new System.Drawing.Point(0, 0);
            this.MenuStrip.Name = "MenuStrip";
            this.MenuStrip.Size = new System.Drawing.Size(852, 24);
            this.MenuStrip.TabIndex = 0;
            this.MenuStrip.Text = "Menu?";
            // 
            // ToolStripFile
            // 
            this.ToolStripFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ToolStripLoad,
            this.ToolStripSave});
            this.ToolStripFile.Name = "ToolStripFile";
            this.ToolStripFile.Size = new System.Drawing.Size(37, 20);
            this.ToolStripFile.Text = "File";
            // 
            // ToolStripLoad
            // 
            this.ToolStripLoad.Name = "ToolStripLoad";
            this.ToolStripLoad.Size = new System.Drawing.Size(103, 22);
            this.ToolStripLoad.Text = "Open";
            // 
            // ToolStripSave
            // 
            this.ToolStripSave.Name = "ToolStripSave";
            this.ToolStripSave.Size = new System.Drawing.Size(103, 22);
            this.ToolStripSave.Text = "Save";
            // 
            // ToolStripHalp
            // 
            this.ToolStripHalp.Name = "ToolStripHalp";
            this.ToolStripHalp.Size = new System.Drawing.Size(44, 20);
            this.ToolStripHalp.Text = "Halp";
            // 
            // GroupBoxSpritesheet
            // 
            this.GroupBoxSpritesheet.Controls.Add(this.LabelAnimationColumns);
            this.GroupBoxSpritesheet.Controls.Add(this.LabelAnimationRows);
            this.GroupBoxSpritesheet.Controls.Add(this.NumericUpDownRows);
            this.GroupBoxSpritesheet.Controls.Add(this.NumericUpDownColumns);
            this.GroupBoxSpritesheet.Controls.Add(this.SpriteViewerSpritesheet);
            this.GroupBoxSpritesheet.Location = new System.Drawing.Point(12, 27);
            this.GroupBoxSpritesheet.Name = "GroupBoxSpritesheet";
            this.GroupBoxSpritesheet.Size = new System.Drawing.Size(398, 283);
            this.GroupBoxSpritesheet.TabIndex = 1;
            this.GroupBoxSpritesheet.TabStop = false;
            this.GroupBoxSpritesheet.Text = "Spritesheet";
            // 
            // LabelAnimationColumns
            // 
            this.LabelAnimationColumns.AutoSize = true;
            this.LabelAnimationColumns.Location = new System.Drawing.Point(6, 74);
            this.LabelAnimationColumns.Name = "LabelAnimationColumns";
            this.LabelAnimationColumns.Size = new System.Drawing.Size(97, 13);
            this.LabelAnimationColumns.TabIndex = 5;
            this.LabelAnimationColumns.Text = "# Columns in sheet";
            // 
            // LabelAnimationRows
            // 
            this.LabelAnimationRows.AutoSize = true;
            this.LabelAnimationRows.Location = new System.Drawing.Point(6, 35);
            this.LabelAnimationRows.Name = "LabelAnimationRows";
            this.LabelAnimationRows.Size = new System.Drawing.Size(84, 13);
            this.LabelAnimationRows.TabIndex = 4;
            this.LabelAnimationRows.Text = "# Rows in sheet";
            // 
            // NumericUpDownRows
            // 
            this.NumericUpDownRows.Location = new System.Drawing.Point(9, 51);
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
            1,
            0,
            0,
            0});
            this.NumericUpDownRows.ValueChanged += new System.EventHandler(this.NumericUpDownRows_ValueChanged);
            // 
            // NumericUpDownColumns
            // 
            this.NumericUpDownColumns.Location = new System.Drawing.Point(9, 90);
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
            1,
            0,
            0,
            0});
            this.NumericUpDownColumns.ValueChanged += new System.EventHandler(this.NumericUpDownColumns_ValueChanged);
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
            this.SpriteViewerSpritesheet.Location = new System.Drawing.Point(132, 19);
            this.SpriteViewerSpritesheet.Name = "SpriteViewerSpritesheet";
            this.SpriteViewerSpritesheet.Size = new System.Drawing.Size(256, 256);
            this.SpriteViewerSpritesheet.TabIndex = 2;
            this.SpriteViewerSpritesheet.TabStop = false;
            this.SpriteViewerSpritesheet.Click += new System.EventHandler(this.SpriteViewerSpritesheet_Click);
            this.SpriteViewerSpritesheet.Paint += new System.Windows.Forms.PaintEventHandler(this.testDrawing);
            // 
            // GroupBoxAnimation
            // 
            this.GroupBoxAnimation.Controls.Add(this.animation1);
            this.GroupBoxAnimation.Controls.Add(this.ButtonPause);
            this.GroupBoxAnimation.Controls.Add(this.ButtonPlayAnimation);
            this.GroupBoxAnimation.Location = new System.Drawing.Point(417, 28);
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
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(852, 543);
            this.Controls.Add(this.GroupBoxAnimation);
            this.Controls.Add(this.GroupBoxSpritesheet);
            this.Controls.Add(this.MenuStrip);
            this.MainMenuStrip = this.MenuStrip;
            this.Name = "Form1";
            this.MenuStrip.ResumeLayout(false);
            this.MenuStrip.PerformLayout();
            this.GroupBoxSpritesheet.ResumeLayout(false);
            this.GroupBoxSpritesheet.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NumericUpDownRows)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.NumericUpDownColumns)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.animation1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.SpriteViewerSpritesheet)).EndInit();
            this.GroupBoxAnimation.ResumeLayout(false);
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
    }
}

