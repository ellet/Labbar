﻿using Editor.DaBestClasses;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Editor
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            myRenderer = new TGARenderBox();
            myRenderer.Init(RenderBox);
        }

        private TGARenderBox myRenderer;

        private void button1_Click(object sender, EventArgs e)
        {
            myRenderer.RefreshWindow();
        }
    }
}