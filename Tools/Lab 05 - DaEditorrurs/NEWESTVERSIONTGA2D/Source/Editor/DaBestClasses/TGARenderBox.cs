﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Editor.DaBestClasses
{
    public class TGARenderBox
    {
        public TGARenderBox()
        {
            myRenderer = new TGARenderer();
        }

        public void Init(PictureBox aPictureBox)
        {
            myRenderer.StartRendering(aPictureBox.Handle);
        }

        private TGARenderer myRenderer;
    }
}
