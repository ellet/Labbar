namespace DevelopingTheGamesAssembly.Popups
{
    partial class AskStudioName
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
            this.textBoxStudioName = new System.Windows.Forms.TextBox();
            this.vikommerintegoranagongtingmeddenylva = new System.Windows.Forms.GroupBox();
            this.ButtonNameStudio = new System.Windows.Forms.Button();
            this.vikommerintegoranagongtingmeddenylva.SuspendLayout();
            this.SuspendLayout();
            // 
            // textBoxStudioName
            // 
            this.textBoxStudioName.Location = new System.Drawing.Point(6, 19);
            this.textBoxStudioName.Name = "textBoxStudioName";
            this.textBoxStudioName.Size = new System.Drawing.Size(323, 20);
            this.textBoxStudioName.TabIndex = 0;
            // 
            // vikommerintegoranagongtingmeddenylva
            // 
            this.vikommerintegoranagongtingmeddenylva.Controls.Add(this.textBoxStudioName);
            this.vikommerintegoranagongtingmeddenylva.Location = new System.Drawing.Point(18, 30);
            this.vikommerintegoranagongtingmeddenylva.Name = "vikommerintegoranagongtingmeddenylva";
            this.vikommerintegoranagongtingmeddenylva.Size = new System.Drawing.Size(335, 53);
            this.vikommerintegoranagongtingmeddenylva.TabIndex = 1;
            this.vikommerintegoranagongtingmeddenylva.TabStop = false;
            this.vikommerintegoranagongtingmeddenylva.Text = "Studio Name:";
            // 
            // ButtonNameStudio
            // 
            this.ButtonNameStudio.Location = new System.Drawing.Point(18, 89);
            this.ButtonNameStudio.Name = "ButtonNameStudio";
            this.ButtonNameStudio.Size = new System.Drawing.Size(335, 43);
            this.ButtonNameStudio.TabIndex = 2;
            this.ButtonNameStudio.Text = "Create Studio";
            this.ButtonNameStudio.UseVisualStyleBackColor = true;
            this.ButtonNameStudio.Click += new System.EventHandler(this.ButtonNameStudio_Click);
            // 
            // AskStudioName
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(382, 153);
            this.Controls.Add(this.ButtonNameStudio);
            this.Controls.Add(this.vikommerintegoranagongtingmeddenylva);
            this.Name = "AskStudioName";
            this.Text = "WhatsDaStudio";
            this.vikommerintegoranagongtingmeddenylva.ResumeLayout(false);
            this.vikommerintegoranagongtingmeddenylva.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TextBox textBoxStudioName;
        private System.Windows.Forms.GroupBox vikommerintegoranagongtingmeddenylva;
        private System.Windows.Forms.Button ButtonNameStudio;
    }
}