namespace DevelopingTheGamesAssembly.Popups
{
    partial class ErrorPopup
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
            this.labelErrorText = new System.Windows.Forms.Label();
            this.ButtonOk = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // labelErrorText
            // 
            this.labelErrorText.AutoSize = true;
            this.labelErrorText.Location = new System.Drawing.Point(22, 20);
            this.labelErrorText.Name = "labelErrorText";
            this.labelErrorText.Size = new System.Drawing.Size(50, 13);
            this.labelErrorText.TabIndex = 0;
            this.labelErrorText.Text = "ErrorText";
            // 
            // ButtonOk
            // 
            this.ButtonOk.Location = new System.Drawing.Point(263, 113);
            this.ButtonOk.Name = "ButtonOk";
            this.ButtonOk.Size = new System.Drawing.Size(75, 23);
            this.ButtonOk.TabIndex = 1;
            this.ButtonOk.Text = "Okilidokili";
            this.ButtonOk.UseVisualStyleBackColor = true;
            this.ButtonOk.Click += new System.EventHandler(this.ButtonOk_Click);
            // 
            // ErrorPopup
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(739, 164);
            this.Controls.Add(this.ButtonOk);
            this.Controls.Add(this.labelErrorText);
            this.Name = "ErrorPopup";
            this.Text = "ErrorPopup";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelErrorText;
        private System.Windows.Forms.Button ButtonOk;
    }
}