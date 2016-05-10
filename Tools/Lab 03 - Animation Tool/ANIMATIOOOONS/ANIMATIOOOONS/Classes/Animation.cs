using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ANIMATIOOOONS.Classes
{
    public class Animation : PictureBox
    {
        public Animation()
        {
            mySpriteRectangle = new Rectangle(0,0,256,256);

        }

        //public void DrawDerp()
        //{
        //    Graphics tempG = Graphics.FromImage(this.Image);

        //    tempG.DrawImage(this.Image, new Point(0, 0));
        //}

        protected override void OnPaint(PaintEventArgs pe)
        {
            if (this.Image != null)
            {
                pe.Graphics.DrawImage(this.Image, 0, 0, mySpriteRectangle, GraphicsUnit.Pixel);
            }
            //base.OnPaint(pe);
        }


        public Rectangle SpriteRectangle
        {
            set
            {
                mySpriteRectangle = value;
                this.Refresh();
            }
        }

        public Bitmap Picture
        {
            set
            {
                this.Image = value;
            }
        }

        private Rectangle mySpriteRectangle;
    }
}
