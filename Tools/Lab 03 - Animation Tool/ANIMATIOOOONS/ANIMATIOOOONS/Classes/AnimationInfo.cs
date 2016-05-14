using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ANIMATIOOOONS.Classes
{
    public class AnimationInfo
    {
        public AnimationInfo()
        {
            myImagePath = "";
            myFrameWidthHeight = new Point();
            myFrameWidthHeight.X = 256;
            myFrameWidthHeight.Y = 256;
            myFrameIntervallInMilliSeconds = 24;
            myColumns = 4;
            myRows = 4;
        }


        public string ImagePath
        {
            set
            {
                myImagePath = value;
            }
            get
            {
                return myImagePath;
            }
        }

        public Point FrameWidthHeight
        {

            set
            {
                myFrameWidthHeight = value;
            }
            get
            {
                return myFrameWidthHeight;
            }
        }

        public int FrameIntervalMilliseconds
        {
            set
            {
                myFrameIntervallInMilliSeconds = value;
            }
            get
            {
                return myFrameIntervallInMilliSeconds;
            }
        }

        public int Rows
        {
            set
            {
                myRows = value;
            }
            get
            {
                return myRows;
            }
        }

        public int Columns
        {
            set
            {
                myColumns = value;
            }
            get
            {
                return myColumns;
            }
        }

        private string myImagePath;
        private Point myFrameWidthHeight;
        private int myFrameIntervallInMilliSeconds;
        private int myColumns;
        private int myRows;
    }
}
