namespace CeePlusPlusTool
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
            this.numericUpDownApa = new System.Windows.Forms.NumericUpDown();
            this.labelApa = new System.Windows.Forms.Label();
            this.staticLabelValue = new System.Windows.Forms.Label();
            this.buttonAssignValue = new System.Windows.Forms.Button();
            this.labelValue = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownApa)).BeginInit();
            this.SuspendLayout();
            // 
            // numericUpDownApa
            // 
            this.numericUpDownApa.Location = new System.Drawing.Point(12, 42);
            this.numericUpDownApa.Name = "numericUpDownApa";
            this.numericUpDownApa.Size = new System.Drawing.Size(89, 20);
            this.numericUpDownApa.TabIndex = 0;
            // 
            // labelApa
            // 
            this.labelApa.AutoSize = true;
            this.labelApa.Location = new System.Drawing.Point(12, 23);
            this.labelApa.Name = "labelApa";
            this.labelApa.Size = new System.Drawing.Size(88, 13);
            this.labelApa.TabIndex = 1;
            this.labelApa.Text = "Insert Apa Value:";
            // 
            // staticLabelValue
            // 
            this.staticLabelValue.AutoSize = true;
            this.staticLabelValue.Location = new System.Drawing.Point(12, 118);
            this.staticLabelValue.Name = "staticLabelValue";
            this.staticLabelValue.Size = new System.Drawing.Size(62, 13);
            this.staticLabelValue.TabIndex = 2;
            this.staticLabelValue.Text = "Apa Value :";
            // 
            // buttonAssignValue
            // 
            this.buttonAssignValue.Location = new System.Drawing.Point(15, 69);
            this.buttonAssignValue.Name = "buttonAssignValue";
            this.buttonAssignValue.Size = new System.Drawing.Size(86, 23);
            this.buttonAssignValue.TabIndex = 3;
            this.buttonAssignValue.Text = "Assign Value";
            this.buttonAssignValue.UseVisualStyleBackColor = true;
            this.buttonAssignValue.Click += new System.EventHandler(this.buttonAssignValue_Click);
            // 
            // labelValue
            // 
            this.labelValue.AutoSize = true;
            this.labelValue.Location = new System.Drawing.Point(80, 118);
            this.labelValue.Name = "labelValue";
            this.labelValue.Size = new System.Drawing.Size(13, 13);
            this.labelValue.TabIndex = 4;
            this.labelValue.Text = "0";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(199, 167);
            this.Controls.Add(this.labelValue);
            this.Controls.Add(this.buttonAssignValue);
            this.Controls.Add(this.staticLabelValue);
            this.Controls.Add(this.labelApa);
            this.Controls.Add(this.numericUpDownApa);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownApa)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.NumericUpDown numericUpDownApa;
        private System.Windows.Forms.Label labelApa;
        private System.Windows.Forms.Label staticLabelValue;
        private System.Windows.Forms.Button buttonAssignValue;
        private System.Windows.Forms.Label labelValue;
    }
}

