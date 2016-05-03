namespace DevelopersTheGame
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
            this.MoneyLabel = new System.Windows.Forms.Label();
            this.IdleWorkers = new System.Windows.Forms.ListBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.HireWorkerButton = new System.Windows.Forms.Button();
            this.FireWorkerButton = new System.Windows.Forms.Button();
            this.WorkersListView = new System.Windows.Forms.ListView();
            this.Worker = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Salary = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Skill = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // MoneyLabel
            // 
            this.MoneyLabel.AutoSize = true;
            this.MoneyLabel.Location = new System.Drawing.Point(12, 9);
            this.MoneyLabel.Name = "MoneyLabel";
            this.MoneyLabel.Size = new System.Drawing.Size(45, 13);
            this.MoneyLabel.TabIndex = 0;
            this.MoneyLabel.Text = "Money: ";
            // 
            // IdleWorkers
            // 
            this.IdleWorkers.DisplayMember = "GetName";
            this.IdleWorkers.FormattingEnabled = true;
            this.IdleWorkers.Location = new System.Drawing.Point(26, 19);
            this.IdleWorkers.Name = "IdleWorkers";
            this.IdleWorkers.Size = new System.Drawing.Size(122, 95);
            this.IdleWorkers.TabIndex = 1;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.WorkersListView);
            this.groupBox1.Controls.Add(this.FireWorkerButton);
            this.groupBox1.Controls.Add(this.HireWorkerButton);
            this.groupBox1.Controls.Add(this.IdleWorkers);
            this.groupBox1.Location = new System.Drawing.Point(15, 359);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(618, 159);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "WorkersBox";
            // 
            // HireWorkerButton
            // 
            this.HireWorkerButton.Location = new System.Drawing.Point(26, 120);
            this.HireWorkerButton.Name = "HireWorkerButton";
            this.HireWorkerButton.Size = new System.Drawing.Size(75, 23);
            this.HireWorkerButton.TabIndex = 2;
            this.HireWorkerButton.Text = "Hire";
            this.HireWorkerButton.UseVisualStyleBackColor = true;
            this.HireWorkerButton.Click += new System.EventHandler(this.HireWorkerButton_Click);
            // 
            // FireWorkerButton
            // 
            this.FireWorkerButton.Location = new System.Drawing.Point(107, 120);
            this.FireWorkerButton.Name = "FireWorkerButton";
            this.FireWorkerButton.Size = new System.Drawing.Size(75, 23);
            this.FireWorkerButton.TabIndex = 3;
            this.FireWorkerButton.Text = "Fire";
            this.FireWorkerButton.UseVisualStyleBackColor = true;
            this.FireWorkerButton.Click += new System.EventHandler(this.FireWorkerButton_Click);
            // 
            // WorkersListView
            // 
            this.WorkersListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.Worker,
            this.Salary,
            this.Skill});
            this.WorkersListView.Location = new System.Drawing.Point(188, 19);
            this.WorkersListView.Name = "WorkersListView";
            this.WorkersListView.Size = new System.Drawing.Size(406, 127);
            this.WorkersListView.TabIndex = 4;
            this.WorkersListView.UseCompatibleStateImageBehavior = false;
            this.WorkersListView.SelectedIndexChanged += new System.EventHandler(this.WorkersListView_SelectedIndexChanged);
            // 
            // Worker
            // 
            this.Worker.Text = "Worker";
            // 
            // Salary
            // 
            this.Salary.Text = "Salary";
            // 
            // Skill
            // 
            this.Skill.Text = "Skill";
            // 
            // Form1
            // 
            this.ClientSize = new System.Drawing.Size(670, 530);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.MoneyLabel);
            this.Name = "Form1";
            this.groupBox1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label MoneyLabel;
        private System.Windows.Forms.ListBox IdleWorkers;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button HireWorkerButton;
        private System.Windows.Forms.Button FireWorkerButton;
        private System.Windows.Forms.ListView WorkersListView;
        private System.Windows.Forms.ColumnHeader Worker;
        private System.Windows.Forms.ColumnHeader Salary;
        private System.Windows.Forms.ColumnHeader Skill;
    }
}

