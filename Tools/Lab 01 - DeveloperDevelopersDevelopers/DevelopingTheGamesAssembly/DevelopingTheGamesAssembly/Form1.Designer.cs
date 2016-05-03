namespace DevelopingTheGamesAssembly
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
            this.LabelEconomy = new System.Windows.Forms.Label();
            this.ButtonEndTurn = new System.Windows.Forms.Button();
            this.LabelStudioName = new System.Windows.Forms.Label();
            this.LabelCosts = new System.Windows.Forms.Label();
            this.ButtonHire = new System.Windows.Forms.Button();
            this.ListViewWorkers = new System.Windows.Forms.ListView();
            this.WorkerName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.WorkerSkill = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.WorkerSalary = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ProjectName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ButtonFire = new System.Windows.Forms.Button();
            this.ProjectList = new System.Windows.Forms.ListBox();
            this.ButtonCreateProject = new System.Windows.Forms.Button();
            this.ButtonRemoveFromProject = new System.Windows.Forms.Button();
            this.assigntheworkybutton = new System.Windows.Forms.Button();
            this.LabelProjectInfo = new System.Windows.Forms.Label();
            this.GroupBoxWorkers = new System.Windows.Forms.GroupBox();
            this.GroupBoxProjects = new System.Windows.Forms.GroupBox();
            this.ButtonReleaseEarly = new System.Windows.Forms.Button();
            this.ButtonTerminateProject = new System.Windows.Forms.Button();
            this.progressBarGameProgress = new System.Windows.Forms.ProgressBar();
            this.ListBoxPublishedGames = new System.Windows.Forms.ListBox();
            this.GroupBoxPublishedGames = new System.Windows.Forms.GroupBox();
            this.LabelGameInfo = new System.Windows.Forms.Label();
            this.ButtonGetMoreRooms = new System.Windows.Forms.Button();
            this.LabelRooms = new System.Windows.Forms.Label();
            this.GroupBoxWorkers.SuspendLayout();
            this.GroupBoxProjects.SuspendLayout();
            this.GroupBoxPublishedGames.SuspendLayout();
            this.SuspendLayout();
            // 
            // LabelEconomy
            // 
            this.LabelEconomy.AutoSize = true;
            this.LabelEconomy.Font = new System.Drawing.Font("Comic Sans MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LabelEconomy.Location = new System.Drawing.Point(16, 47);
            this.LabelEconomy.Name = "LabelEconomy";
            this.LabelEconomy.Size = new System.Drawing.Size(129, 23);
            this.LabelEconomy.TabIndex = 0;
            this.LabelEconomy.Text = "Economy: 10000";
            // 
            // ButtonEndTurn
            // 
            this.ButtonEndTurn.Location = new System.Drawing.Point(870, 465);
            this.ButtonEndTurn.Name = "ButtonEndTurn";
            this.ButtonEndTurn.Size = new System.Drawing.Size(142, 35);
            this.ButtonEndTurn.TabIndex = 1;
            this.ButtonEndTurn.Text = "End Turn";
            this.ButtonEndTurn.UseVisualStyleBackColor = true;
            this.ButtonEndTurn.Click += new System.EventHandler(this.ButtonEndTurn_Click);
            // 
            // LabelStudioName
            // 
            this.LabelStudioName.AutoSize = true;
            this.LabelStudioName.Font = new System.Drawing.Font("Comic Sans MS", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LabelStudioName.Location = new System.Drawing.Point(12, 9);
            this.LabelStudioName.Name = "LabelStudioName";
            this.LabelStudioName.Size = new System.Drawing.Size(284, 38);
            this.LabelStudioName.TabIndex = 2;
            this.LabelStudioName.Text = "Generic Studio Name";
            // 
            // LabelCosts
            // 
            this.LabelCosts.AutoSize = true;
            this.LabelCosts.Location = new System.Drawing.Point(867, 383);
            this.LabelCosts.Name = "LabelCosts";
            this.LabelCosts.Size = new System.Drawing.Size(36, 13);
            this.LabelCosts.TabIndex = 3;
            this.LabelCosts.Text = "Costs:";
            // 
            // ButtonHire
            // 
            this.ButtonHire.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.ButtonHire.Location = new System.Drawing.Point(15, 218);
            this.ButtonHire.Name = "ButtonHire";
            this.ButtonHire.Size = new System.Drawing.Size(56, 29);
            this.ButtonHire.TabIndex = 4;
            this.ButtonHire.Text = "Hire";
            this.ButtonHire.UseVisualStyleBackColor = false;
            this.ButtonHire.Click += new System.EventHandler(this.ButtonHire_Click);
            // 
            // ListViewWorkers
            // 
            this.ListViewWorkers.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.WorkerName,
            this.WorkerSkill,
            this.WorkerSalary,
            this.ProjectName});
            this.ListViewWorkers.Location = new System.Drawing.Point(6, 19);
            this.ListViewWorkers.Name = "ListViewWorkers";
            this.ListViewWorkers.Size = new System.Drawing.Size(506, 195);
            this.ListViewWorkers.TabIndex = 5;
            this.ListViewWorkers.UseCompatibleStateImageBehavior = false;
            // 
            // WorkerName
            // 
            this.WorkerName.Text = "Name";
            this.WorkerName.Width = 150;
            // 
            // WorkerSkill
            // 
            this.WorkerSkill.Text = "Skill";
            // 
            // WorkerSalary
            // 
            this.WorkerSalary.Text = "Salary";
            this.WorkerSalary.Width = 72;
            // 
            // ProjectName
            // 
            this.ProjectName.Text = "Project";
            // 
            // ButtonFire
            // 
            this.ButtonFire.Location = new System.Drawing.Point(77, 219);
            this.ButtonFire.Name = "ButtonFire";
            this.ButtonFire.Size = new System.Drawing.Size(55, 28);
            this.ButtonFire.TabIndex = 6;
            this.ButtonFire.Text = "Fire";
            this.ButtonFire.UseVisualStyleBackColor = true;
            this.ButtonFire.Click += new System.EventHandler(this.ButtonFire_Click);
            // 
            // ProjectList
            // 
            this.ProjectList.DisplayMember = "ProjectName";
            this.ProjectList.FormattingEnabled = true;
            this.ProjectList.Location = new System.Drawing.Point(6, 19);
            this.ProjectList.Name = "ProjectList";
            this.ProjectList.Size = new System.Drawing.Size(120, 134);
            this.ProjectList.TabIndex = 7;
            this.ProjectList.SelectedIndexChanged += new System.EventHandler(this.ProjectList_SelectedIndexChanged);
            // 
            // ButtonCreateProject
            // 
            this.ButtonCreateProject.Location = new System.Drawing.Point(6, 159);
            this.ButtonCreateProject.Name = "ButtonCreateProject";
            this.ButtonCreateProject.Size = new System.Drawing.Size(75, 23);
            this.ButtonCreateProject.TabIndex = 8;
            this.ButtonCreateProject.Text = "New Project";
            this.ButtonCreateProject.UseVisualStyleBackColor = true;
            this.ButtonCreateProject.Click += new System.EventHandler(this.ButtonCreateProject_Click);
            // 
            // ButtonRemoveFromProject
            // 
            this.ButtonRemoveFromProject.Location = new System.Drawing.Point(254, 218);
            this.ButtonRemoveFromProject.Name = "ButtonRemoveFromProject";
            this.ButtonRemoveFromProject.Size = new System.Drawing.Size(120, 23);
            this.ButtonRemoveFromProject.TabIndex = 10;
            this.ButtonRemoveFromProject.Text = "Remove From Project";
            this.ButtonRemoveFromProject.UseVisualStyleBackColor = true;
            this.ButtonRemoveFromProject.Click += new System.EventHandler(this.ButtonRemoveFromProject_Click);
            // 
            // assigntheworkybutton
            // 
            this.assigntheworkybutton.Location = new System.Drawing.Point(380, 218);
            this.assigntheworkybutton.Name = "assigntheworkybutton";
            this.assigntheworkybutton.Size = new System.Drawing.Size(132, 23);
            this.assigntheworkybutton.TabIndex = 11;
            this.assigntheworkybutton.Text = "Assign To Project";
            this.assigntheworkybutton.UseVisualStyleBackColor = true;
            this.assigntheworkybutton.Click += new System.EventHandler(this.assigntheworkybutton_Click);
            // 
            // LabelProjectInfo
            // 
            this.LabelProjectInfo.AutoSize = true;
            this.LabelProjectInfo.Location = new System.Drawing.Point(132, 19);
            this.LabelProjectInfo.Name = "LabelProjectInfo";
            this.LabelProjectInfo.Size = new System.Drawing.Size(64, 13);
            this.LabelProjectInfo.TabIndex = 12;
            this.LabelProjectInfo.Text = "Project Info:";
            // 
            // GroupBoxWorkers
            // 
            this.GroupBoxWorkers.Controls.Add(this.ListViewWorkers);
            this.GroupBoxWorkers.Controls.Add(this.assigntheworkybutton);
            this.GroupBoxWorkers.Controls.Add(this.ButtonRemoveFromProject);
            this.GroupBoxWorkers.Controls.Add(this.ButtonHire);
            this.GroupBoxWorkers.Controls.Add(this.ButtonFire);
            this.GroupBoxWorkers.Location = new System.Drawing.Point(19, 247);
            this.GroupBoxWorkers.Name = "GroupBoxWorkers";
            this.GroupBoxWorkers.Size = new System.Drawing.Size(518, 253);
            this.GroupBoxWorkers.TabIndex = 13;
            this.GroupBoxWorkers.TabStop = false;
            this.GroupBoxWorkers.Text = "Workers";
            // 
            // GroupBoxProjects
            // 
            this.GroupBoxProjects.Controls.Add(this.ButtonReleaseEarly);
            this.GroupBoxProjects.Controls.Add(this.ButtonTerminateProject);
            this.GroupBoxProjects.Controls.Add(this.progressBarGameProgress);
            this.GroupBoxProjects.Controls.Add(this.ProjectList);
            this.GroupBoxProjects.Controls.Add(this.ButtonCreateProject);
            this.GroupBoxProjects.Controls.Add(this.LabelProjectInfo);
            this.GroupBoxProjects.Location = new System.Drawing.Point(409, 9);
            this.GroupBoxProjects.Name = "GroupBoxProjects";
            this.GroupBoxProjects.Size = new System.Drawing.Size(455, 227);
            this.GroupBoxProjects.TabIndex = 14;
            this.GroupBoxProjects.TabStop = false;
            this.GroupBoxProjects.Text = "Projects";
            // 
            // ButtonReleaseEarly
            // 
            this.ButtonReleaseEarly.Location = new System.Drawing.Point(157, 160);
            this.ButtonReleaseEarly.Name = "ButtonReleaseEarly";
            this.ButtonReleaseEarly.Size = new System.Drawing.Size(133, 39);
            this.ButtonReleaseEarly.TabIndex = 19;
            this.ButtonReleaseEarly.Text = "Release Early";
            this.ButtonReleaseEarly.UseVisualStyleBackColor = true;
            this.ButtonReleaseEarly.Click += new System.EventHandler(this.ButtonReleaseEarly_Click);
            // 
            // ButtonTerminateProject
            // 
            this.ButtonTerminateProject.Location = new System.Drawing.Point(323, 168);
            this.ButtonTerminateProject.Name = "ButtonTerminateProject";
            this.ButtonTerminateProject.Size = new System.Drawing.Size(105, 23);
            this.ButtonTerminateProject.TabIndex = 18;
            this.ButtonTerminateProject.Text = "Terminate Project";
            this.ButtonTerminateProject.UseVisualStyleBackColor = true;
            this.ButtonTerminateProject.Click += new System.EventHandler(this.ButtonTerminateProject_Click);
            // 
            // progressBarGameProgress
            // 
            this.progressBarGameProgress.Location = new System.Drawing.Point(157, 130);
            this.progressBarGameProgress.Name = "progressBarGameProgress";
            this.progressBarGameProgress.Size = new System.Drawing.Size(271, 23);
            this.progressBarGameProgress.TabIndex = 17;
            // 
            // ListBoxPublishedGames
            // 
            this.ListBoxPublishedGames.DisplayMember = "GetName";
            this.ListBoxPublishedGames.FormattingEnabled = true;
            this.ListBoxPublishedGames.Location = new System.Drawing.Point(6, 19);
            this.ListBoxPublishedGames.Name = "ListBoxPublishedGames";
            this.ListBoxPublishedGames.Size = new System.Drawing.Size(133, 121);
            this.ListBoxPublishedGames.TabIndex = 15;
            this.ListBoxPublishedGames.SelectedIndexChanged += new System.EventHandler(this.ListBoxPublishedGames_SelectedIndexChanged);
            // 
            // GroupBoxPublishedGames
            // 
            this.GroupBoxPublishedGames.Controls.Add(this.LabelGameInfo);
            this.GroupBoxPublishedGames.Controls.Add(this.ListBoxPublishedGames);
            this.GroupBoxPublishedGames.Location = new System.Drawing.Point(543, 247);
            this.GroupBoxPublishedGames.Name = "GroupBoxPublishedGames";
            this.GroupBoxPublishedGames.Size = new System.Drawing.Size(321, 253);
            this.GroupBoxPublishedGames.TabIndex = 16;
            this.GroupBoxPublishedGames.TabStop = false;
            this.GroupBoxPublishedGames.Text = "Published Games";
            // 
            // LabelGameInfo
            // 
            this.LabelGameInfo.AutoSize = true;
            this.LabelGameInfo.Location = new System.Drawing.Point(7, 147);
            this.LabelGameInfo.Name = "LabelGameInfo";
            this.LabelGameInfo.Size = new System.Drawing.Size(59, 13);
            this.LabelGameInfo.TabIndex = 16;
            this.LabelGameInfo.Text = "Game Info:";
            // 
            // ButtonGetMoreRooms
            // 
            this.ButtonGetMoreRooms.Location = new System.Drawing.Point(885, 213);
            this.ButtonGetMoreRooms.Name = "ButtonGetMoreRooms";
            this.ButtonGetMoreRooms.Size = new System.Drawing.Size(127, 23);
            this.ButtonGetMoreRooms.TabIndex = 17;
            this.ButtonGetMoreRooms.Text = "BuildMoreRooms";
            this.ButtonGetMoreRooms.UseVisualStyleBackColor = true;
            this.ButtonGetMoreRooms.Click += new System.EventHandler(this.ButtonGetMoreRooms_Click);
            // 
            // LabelRooms
            // 
            this.LabelRooms.AutoSize = true;
            this.LabelRooms.Location = new System.Drawing.Point(893, 141);
            this.LabelRooms.Name = "LabelRooms";
            this.LabelRooms.Size = new System.Drawing.Size(66, 13);
            this.LabelRooms.TabIndex = 18;
            this.LabelRooms.Text = "LabelRooms";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.ClientSize = new System.Drawing.Size(1024, 512);
            this.Controls.Add(this.LabelRooms);
            this.Controls.Add(this.ButtonGetMoreRooms);
            this.Controls.Add(this.GroupBoxPublishedGames);
            this.Controls.Add(this.GroupBoxProjects);
            this.Controls.Add(this.GroupBoxWorkers);
            this.Controls.Add(this.LabelCosts);
            this.Controls.Add(this.LabelStudioName);
            this.Controls.Add(this.ButtonEndTurn);
            this.Controls.Add(this.LabelEconomy);
            this.Name = "Form1";
            this.Text = "Developers The Game";
            this.GroupBoxWorkers.ResumeLayout(false);
            this.GroupBoxProjects.ResumeLayout(false);
            this.GroupBoxProjects.PerformLayout();
            this.GroupBoxPublishedGames.ResumeLayout(false);
            this.GroupBoxPublishedGames.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }



        #endregion

        private System.Windows.Forms.Label LabelEconomy;
        private System.Windows.Forms.Button ButtonEndTurn;
        private System.Windows.Forms.Label LabelStudioName;
        private System.Windows.Forms.Label LabelCosts;
        private System.Windows.Forms.Button ButtonHire;
        private System.Windows.Forms.ListView ListViewWorkers;
        private System.Windows.Forms.ColumnHeader WorkerName;
        private System.Windows.Forms.ColumnHeader WorkerSkill;
        private System.Windows.Forms.ColumnHeader WorkerSalary;
        private System.Windows.Forms.Button ButtonFire;
        private System.Windows.Forms.ListBox ProjectList;
        private System.Windows.Forms.Button ButtonCreateProject;
        private System.Windows.Forms.Button ButtonRemoveFromProject;
        private System.Windows.Forms.ColumnHeader ProjectName;
        private System.Windows.Forms.Button assigntheworkybutton;
        private System.Windows.Forms.Label LabelProjectInfo;
        private System.Windows.Forms.GroupBox GroupBoxWorkers;
        private System.Windows.Forms.GroupBox GroupBoxProjects;
        private System.Windows.Forms.ListBox ListBoxPublishedGames;
        private System.Windows.Forms.GroupBox GroupBoxPublishedGames;
        private System.Windows.Forms.Label LabelGameInfo;
        private System.Windows.Forms.ProgressBar progressBarGameProgress;
        private System.Windows.Forms.Button ButtonReleaseEarly;
        private System.Windows.Forms.Button ButtonTerminateProject;
        private System.Windows.Forms.Button ButtonGetMoreRooms;
        private System.Windows.Forms.Label LabelRooms;
    }
}

