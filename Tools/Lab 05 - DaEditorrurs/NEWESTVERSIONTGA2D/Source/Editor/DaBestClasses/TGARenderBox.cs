using System;
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
            myPictureBox = aPictureBox;
        }

        public void RefreshWindow()
        {
            myPictureBox.Refresh();
        }

        private TGARenderer myRenderer;
        private PictureBox myPictureBox;
    }
}
