/*

Copyright (c) 2014, Ivan Mashchenko
Copyright (c) 2011, Thomas ICHE
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
following conditions are met:

        * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer 
          in the documentation and/or other materials provided with the distribution.
        * Neither the name of FlowGraph nor the names of its contributors may be used to endorse or promote products derived from this 
          software without specific prior written permission.


THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, 
OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

namespace FlowGraph
{
    partial class FlowGraphView
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

        #region Component Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.myPropertiesPanel = new System.Windows.Forms.Panel();
            this.myPropertiesNodeData = new System.Windows.Forms.Panel();
            this.label1 = new System.Windows.Forms.Label();
            this.myPropertiesPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // myPropertiesPanel
            // 
            this.myPropertiesPanel.AutoScroll = true;
            this.myPropertiesPanel.AutoSize = true;
            this.myPropertiesPanel.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.myPropertiesPanel.BackColor = System.Drawing.Color.DimGray;
            this.myPropertiesPanel.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.myPropertiesPanel.Controls.Add(this.myPropertiesNodeData);
            this.myPropertiesPanel.Controls.Add(this.label1);
            this.myPropertiesPanel.Dock = System.Windows.Forms.DockStyle.Left;
            this.myPropertiesPanel.Location = new System.Drawing.Point(0, 0);
            this.myPropertiesPanel.Name = "myPropertiesPanel";
            this.myPropertiesPanel.Size = new System.Drawing.Size(255, 588);
            this.myPropertiesPanel.TabIndex = 0;
            // 
            // myPropertiesNodeData
            // 
            this.myPropertiesNodeData.AutoSize = true;
            this.myPropertiesNodeData.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(94)))), ((int)(((byte)(94)))), ((int)(((byte)(94)))));
            this.myPropertiesNodeData.Location = new System.Drawing.Point(3, 19);
            this.myPropertiesNodeData.Name = "myPropertiesNodeData";
            this.myPropertiesNodeData.Size = new System.Drawing.Size(245, 342);
            this.myPropertiesNodeData.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.White;
            this.label1.Location = new System.Drawing.Point(38, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(70, 16);
            this.label1.TabIndex = 0;
            this.label1.Text = "Properties";
            // 
            // FlowGraphView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.Controls.Add(this.myPropertiesPanel);
            this.Name = "FlowGraphView";
            this.Size = new System.Drawing.Size(952, 588);
            this.Load += new System.EventHandler(this.FlowGraphView_Load);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.FlowGraphPanel_Paint);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.FlowGraphView_KeyDown);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.FlowGraphView_KeyUp);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.FlowGraphView_MouseDown);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.FlowGraphView_MouseMove);
            this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.FlowGraphView_MouseUp);
            this.MouseWheel += new System.Windows.Forms.MouseEventHandler(this.FlowGraphView_MouseWheel);
            this.Resize += new System.EventHandler(this.FlowGraphView_Resize);
            this.myPropertiesPanel.ResumeLayout(false);
            this.myPropertiesPanel.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        public System.Windows.Forms.Panel myPropertiesPanel;
        private System.Windows.Forms.Panel myPropertiesNodeData;


    }
}
