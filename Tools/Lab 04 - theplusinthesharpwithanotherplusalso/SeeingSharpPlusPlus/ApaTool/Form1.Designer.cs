namespace ApaTool
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
            this.buttonAssign = new System.Windows.Forms.Button();
            this.numericUpDownApa = new System.Windows.Forms.NumericUpDown();
            this.staticLabelAssignApa = new System.Windows.Forms.Label();
            this.labelValue = new System.Windows.Forms.Label();
            this.staticLabelInput = new System.Windows.Forms.Label();
            this.staticLabelApaName = new System.Windows.Forms.Label();
            this.labelApaName = new System.Windows.Forms.Label();
            this.textBoxApaName = new System.Windows.Forms.TextBox();
            this.buttonAssignName = new System.Windows.Forms.Button();
            this.StaticLabelName = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownApa)).BeginInit();
            this.SuspendLayout();
            // 
            // buttonAssign
            // 
            this.buttonAssign.Location = new System.Drawing.Point(13, 73);
            this.buttonAssign.Name = "buttonAssign";
            this.buttonAssign.Size = new System.Drawing.Size(106, 23);
            this.buttonAssign.TabIndex = 0;
            this.buttonAssign.Text = "Assign Apa Value";
            this.buttonAssign.UseVisualStyleBackColor = true;
            this.buttonAssign.Click += new System.EventHandler(this.buttonAssign_Click);
            // 
            // numericUpDownApa
            // 
            this.numericUpDownApa.Location = new System.Drawing.Point(13, 47);
            this.numericUpDownApa.Name = "numericUpDownApa";
            this.numericUpDownApa.Size = new System.Drawing.Size(56, 20);
            this.numericUpDownApa.TabIndex = 1;
            // 
            // staticLabelAssignApa
            // 
            this.staticLabelAssignApa.AutoSize = true;
            this.staticLabelAssignApa.Location = new System.Drawing.Point(10, 110);
            this.staticLabelAssignApa.Name = "staticLabelAssignApa";
            this.staticLabelAssignApa.Size = new System.Drawing.Size(65, 13);
            this.staticLabelAssignApa.TabIndex = 2;
            this.staticLabelAssignApa.Text = "Apa Value : ";
            // 
            // labelValue
            // 
            this.labelValue.AutoSize = true;
            this.labelValue.Location = new System.Drawing.Point(81, 110);
            this.labelValue.Name = "labelValue";
            this.labelValue.Size = new System.Drawing.Size(13, 13);
            this.labelValue.TabIndex = 3;
            this.labelValue.Text = "0";
            // 
            // staticLabelInput
            // 
            this.staticLabelInput.AutoSize = true;
            this.staticLabelInput.Location = new System.Drawing.Point(13, 28);
            this.staticLabelInput.Name = "staticLabelInput";
            this.staticLabelInput.Size = new System.Drawing.Size(69, 13);
            this.staticLabelInput.TabIndex = 4;
            this.staticLabelInput.Text = "Insert Value :";
            // 
            // staticLabelApaName
            // 
            this.staticLabelApaName.AutoSize = true;
            this.staticLabelApaName.Location = new System.Drawing.Point(142, 110);
            this.staticLabelApaName.Name = "staticLabelApaName";
            this.staticLabelApaName.Size = new System.Drawing.Size(63, 13);
            this.staticLabelApaName.TabIndex = 5;
            this.staticLabelApaName.Text = "Apa Name :";
            // 
            // labelApaName
            // 
            this.labelApaName.AutoSize = true;
            this.labelApaName.Location = new System.Drawing.Point(202, 110);
            this.labelApaName.Name = "labelApaName";
            this.labelApaName.Size = new System.Drawing.Size(30, 13);
            this.labelApaName.TabIndex = 6;
            this.labelApaName.Text = "Derp";
            // 
            // textBoxApaName
            // 
            this.textBoxApaName.Location = new System.Drawing.Point(145, 46);
            this.textBoxApaName.Name = "textBoxApaName";
            this.textBoxApaName.Size = new System.Drawing.Size(87, 20);
            this.textBoxApaName.TabIndex = 7;
            this.textBoxApaName.Text = "Derp";
            // 
            // buttonAssignName
            // 
            this.buttonAssignName.Location = new System.Drawing.Point(135, 73);
            this.buttonAssignName.Name = "buttonAssignName";
            this.buttonAssignName.Size = new System.Drawing.Size(120, 23);
            this.buttonAssignName.TabIndex = 8;
            this.buttonAssignName.Text = "Assign Apa Name";
            this.buttonAssignName.UseVisualStyleBackColor = true;
            this.buttonAssignName.Click += new System.EventHandler(this.buttonAssignName_Click);
            // 
            // StaticLabelName
            // 
            this.StaticLabelName.AutoSize = true;
            this.StaticLabelName.Location = new System.Drawing.Point(145, 28);
            this.StaticLabelName.Name = "StaticLabelName";
            this.StaticLabelName.Size = new System.Drawing.Size(70, 13);
            this.StaticLabelName.TabIndex = 9;
            this.StaticLabelName.Text = "Insert Name :";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(281, 153);
            this.Controls.Add(this.StaticLabelName);
            this.Controls.Add(this.buttonAssignName);
            this.Controls.Add(this.textBoxApaName);
            this.Controls.Add(this.labelApaName);
            this.Controls.Add(this.staticLabelApaName);
            this.Controls.Add(this.staticLabelInput);
            this.Controls.Add(this.labelValue);
            this.Controls.Add(this.staticLabelAssignApa);
            this.Controls.Add(this.numericUpDownApa);
            this.Controls.Add(this.buttonAssign);
            this.Name = "Form1";
            this.Text = "Apa Simulator";
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownApa)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonAssign;
        private System.Windows.Forms.NumericUpDown numericUpDownApa;
        private System.Windows.Forms.Label staticLabelAssignApa;
        private System.Windows.Forms.Label labelValue;
        private System.Windows.Forms.Label staticLabelInput;
        private System.Windows.Forms.Label staticLabelApaName;
        private System.Windows.Forms.Label labelApaName;
        private System.Windows.Forms.TextBox textBoxApaName;
        private System.Windows.Forms.Button buttonAssignName;
        private System.Windows.Forms.Label StaticLabelName;
    }
}

