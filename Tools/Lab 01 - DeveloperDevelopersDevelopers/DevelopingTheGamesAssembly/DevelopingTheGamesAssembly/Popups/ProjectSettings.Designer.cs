namespace DevelopingTheGamesAssembly.Popups
{
    partial class ProjectSettings
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.TextBoxProjectName = new System.Windows.Forms.TextBox();
            this.ButtonCreateProject = new System.Windows.Forms.Button();
            this.BarDifficulty = new System.Windows.Forms.TrackBar();
            this.GroupDifficuly = new System.Windows.Forms.GroupBox();
            this.LabelFewFeatures = new System.Windows.Forms.Label();
            this.LabelManyFeatures = new System.Windows.Forms.Label();
            this.ButtonCancel = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.BarDifficulty)).BeginInit();
            this.GroupDifficuly.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.TextBoxProjectName);
            this.groupBox1.Location = new System.Drawing.Point(14, 22);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(376, 52);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Project Name";
            // 
            // TextBoxProjectName
            // 
            this.TextBoxProjectName.Location = new System.Drawing.Point(6, 19);
            this.TextBoxProjectName.Name = "TextBoxProjectName";
            this.TextBoxProjectName.Size = new System.Drawing.Size(363, 20);
            this.TextBoxProjectName.TabIndex = 0;
            // 
            // ButtonCreateProject
            // 
            this.ButtonCreateProject.Location = new System.Drawing.Point(24, 209);
            this.ButtonCreateProject.Name = "ButtonCreateProject";
            this.ButtonCreateProject.Size = new System.Drawing.Size(75, 23);
            this.ButtonCreateProject.TabIndex = 1;
            this.ButtonCreateProject.Text = "Create";
            this.ButtonCreateProject.UseVisualStyleBackColor = true;
            this.ButtonCreateProject.Click += new System.EventHandler(this.ButtonCreateProject_Click);
            // 
            // BarDifficulty
            // 
            this.BarDifficulty.Location = new System.Drawing.Point(10, 19);
            this.BarDifficulty.Maximum = 50;
            this.BarDifficulty.Minimum = 5;
            this.BarDifficulty.Name = "BarDifficulty";
            this.BarDifficulty.Size = new System.Drawing.Size(359, 45);
            this.BarDifficulty.TabIndex = 5;
            this.BarDifficulty.TickFrequency = 3;
            this.BarDifficulty.Value = 5;
            // 
            // GroupDifficuly
            // 
            this.GroupDifficuly.Controls.Add(this.LabelManyFeatures);
            this.GroupDifficuly.Controls.Add(this.LabelFewFeatures);
            this.GroupDifficuly.Controls.Add(this.BarDifficulty);
            this.GroupDifficuly.Location = new System.Drawing.Point(14, 80);
            this.GroupDifficuly.Name = "GroupDifficuly";
            this.GroupDifficuly.Size = new System.Drawing.Size(376, 109);
            this.GroupDifficuly.TabIndex = 3;
            this.GroupDifficuly.TabStop = false;
            this.GroupDifficuly.Text = "Difficulty";
            // 
            // LabelFewFeatures
            // 
            this.LabelFewFeatures.AutoSize = true;
            this.LabelFewFeatures.Location = new System.Drawing.Point(28, 67);
            this.LabelFewFeatures.Name = "LabelFewFeatures";
            this.LabelFewFeatures.Size = new System.Drawing.Size(68, 13);
            this.LabelFewFeatures.TabIndex = 3;
            this.LabelFewFeatures.Text = "Few features";
            // 
            // LabelManyFeatures
            // 
            this.LabelManyFeatures.AutoSize = true;
            this.LabelManyFeatures.Location = new System.Drawing.Point(272, 67);
            this.LabelManyFeatures.Name = "LabelManyFeatures";
            this.LabelManyFeatures.Size = new System.Drawing.Size(81, 13);
            this.LabelManyFeatures.TabIndex = 4;
            this.LabelManyFeatures.Text = "A lot of features";
            // 
            // ButtonCancel
            // 
            this.ButtonCancel.Location = new System.Drawing.Point(105, 209);
            this.ButtonCancel.Name = "ButtonCancel";
            this.ButtonCancel.Size = new System.Drawing.Size(75, 23);
            this.ButtonCancel.TabIndex = 4;
            this.ButtonCancel.Text = "Cancel";
            this.ButtonCancel.UseVisualStyleBackColor = true;
            this.ButtonCancel.Click += new System.EventHandler(this.ButtonCancel_Click);
            // 
            // ProjectSettings
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(425, 253);
            this.Controls.Add(this.ButtonCancel);
            this.Controls.Add(this.GroupDifficuly);
            this.Controls.Add(this.ButtonCreateProject);
            this.Controls.Add(this.groupBox1);
            this.Name = "ProjectSettings";
            this.Text = "Project Setup";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.BarDifficulty)).EndInit();
            this.GroupDifficuly.ResumeLayout(false);
            this.GroupDifficuly.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TextBox TextBoxProjectName;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button ButtonCreateProject;
        private System.Windows.Forms.TrackBar BarDifficulty;
        private System.Windows.Forms.GroupBox GroupDifficuly;
        private System.Windows.Forms.Label LabelManyFeatures;
        private System.Windows.Forms.Label LabelFewFeatures;
        private System.Windows.Forms.Button ButtonCancel;
    }
}