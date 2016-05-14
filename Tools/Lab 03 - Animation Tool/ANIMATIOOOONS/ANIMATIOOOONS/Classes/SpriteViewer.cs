using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ANIMATIOOOONS.Classes
{
    public enum eFrameStyle
    {
        eFrameSize,
        eColumnRows
    }


    public class SpriteViewer : PictureBox
    {
        public SpriteViewer()
        {
            myColumns = 4;
            myRows = 4;
            myDrawOverImage = null;        
            myActiveFrame = 0;
            myFrameIntervallInMilliSeconds = 1;
            myAnimationTimer = new Timer();
            myFrameStyle = eFrameStyle.eFrameSize;
            myFrameWidthHeight = new Point();
            myFrameWidthHeight.X = 256;
            myFrameWidthHeight.Y = 256;
        }

        public void Init(Animation anAnimationWindow)
        {
            myAnimation = anAnimationWindow;
        }

        public void StartAnimation()
        {
            myAnimationTimer.Start();
        }

        public void StopAnimation()
        {
            myAnimationTimer.Stop();
        }

        public void PlayAnimation()
        {
            int currentFrame = myActiveFrame;
            ++currentFrame;
            switch (myFrameStyle)
            {
                case eFrameStyle.eFrameSize:
                    int fitWidth = (int)((float)(myFrameWidthHeight.X) * ((float)myDrawOverImage.Size.Width / (float)myOriginalImage.Size.Width));
                    int fitHeigt = (int)((float)(myFrameWidthHeight.Y) * ((float)myDrawOverImage.Size.Height / (float)myOriginalImage.Size.Height));

                    int framesPerRow = (int)((float)myDrawOverImage.Size.Width / (float)fitWidth);
                    int framesPerColumn = (int)((float)myDrawOverImage.Size.Height / (float)fitHeigt);


                    if (currentFrame >= (framesPerColumn * framesPerRow))
                    {
                        currentFrame = 0;
                    }
                    break;
                case eFrameStyle.eColumnRows:
                    if (currentFrame >= (myColumns * myRows))
                    {
                        currentFrame = 0;
                    }
                    break;
                default:
                    break;
            }

            SetActiveFrame(currentFrame);
        }

        public void testDrawStuff()
        {
            Graphics tempg = Graphics.FromImage(myDrawOverImage);

            tempg.Clear(Color.Transparent);


            Point animFrameWidthHeight = new Point();
            Point animXYPos = new Point();

            switch (myFrameStyle)
            {
                case eFrameStyle.eFrameSize:
                    animFrameWidthHeight = myFrameWidthHeight;
                    DrawSpritesheetLinesFrameSize(tempg);
                    SetFrameRectangleFrameSize(tempg);
                    //Check how many frames fit
                    int fitWidth = myOriginalImage.Size.Width / myFrameWidthHeight.X;
                    int fitHeigt = myOriginalImage.Size.Height / myFrameWidthHeight.Y;

                    int framesPerRow = (int)((float)myDrawOverImage.Size.Width / (float)fitWidth);

                    //int x = 
                    //int y = 

                    animXYPos.X = myFrameWidthHeight.X * (myActiveFrame % fitWidth);
                    animXYPos.Y = myFrameWidthHeight.Y * (myActiveFrame / fitWidth);
                    break;
                case eFrameStyle.eColumnRows:
                    animFrameWidthHeight = GetFrameWidthColumnsRows();
                    DrawSpritesheetLinesColumnRows(tempg);
                    SetFrameRectangleColumnsRows(tempg);
                    animXYPos.X = animFrameWidthHeight.X * (myActiveFrame % myColumns);
                    animXYPos.Y = animFrameWidthHeight.Y * (myActiveFrame / myColumns);
                    break;
                default:
                    animFrameWidthHeight.X = 64;
                    animFrameWidthHeight.Y = 64;
                    animXYPos.X = 0;
                    animXYPos.Y = 0;
                    break;
            }

            myAnimation.SpriteRectangle = new Rectangle(animXYPos.X, animXYPos.Y, animFrameWidthHeight.X, animFrameWidthHeight.Y);

            this.Refresh();
            tempg.Dispose();
        }

        private int RowsFrameSize()
        {
            int fitWidth = (int)((float)(myFrameWidthHeight.X) * ((float)myDrawOverImage.Size.Width / (float)myOriginalImage.Size.Width));
            int fitHeigt = (int)((float)(myFrameWidthHeight.Y) * ((float)myDrawOverImage.Size.Height / (float)myOriginalImage.Size.Height));

            return (int)((float)myDrawOverImage.Size.Width / (float)fitWidth);
        }

        private int ColumnsFrameSize()
        {
            int fitWidth = (int)((float)(myFrameWidthHeight.X) * ((float)myDrawOverImage.Size.Width / (float)myOriginalImage.Size.Width));
            int fitHeigt = (int)((float)(myFrameWidthHeight.Y) * ((float)myDrawOverImage.Size.Height / (float)myOriginalImage.Size.Height));

            return (int)((float)myDrawOverImage.Size.Height / (float)fitHeigt);
        }

        private void SetFrameRectangleFrameSize(Graphics aGraphics)
        {
            int fitWidth = (int)((float)(myFrameWidthHeight.X) * ((float)myDrawOverImage.Size.Width / (float)myOriginalImage.Size.Width));
            int fitHeigt = (int)((float)(myFrameWidthHeight.Y) * ((float)myDrawOverImage.Size.Height / (float)myOriginalImage.Size.Height));
    
            int framesPerRow = (int)((float)myDrawOverImage.Size.Width / (float)fitWidth);

            int x = fitWidth * (myActiveFrame % framesPerRow);
            int y = fitHeigt * (myActiveFrame / framesPerRow);

            Rectangle tempRect = new Rectangle(x, y, fitWidth, fitHeigt);


            SolidBrush tempBrush = new SolidBrush(Color.Black);
            tempBrush.Color = Color.FromArgb(100, 0, 0, 0);
            aGraphics.FillRectangle(tempBrush, tempRect);
        }

        private void DrawSpritesheetLinesFrameSize(Graphics aGraphics)
        {
            Point lineToDrawStart = new Point(0, 0);
            Point lineToDrawEnd = new Point(0, 0);

            if (myFrameWidthHeight.Y < (float)myOriginalImage.Size.Height)
            {
                int stepDistance = (int)((float)(myFrameWidthHeight.Y) * ((float)myDrawOverImage.Size.Height / (float)myOriginalImage.Size.Height));//(myDrawOverImage.Size.Height / myOriginalImage.Size.Height) / myFrameWidthHeight.Y;

                lineToDrawStart.X = 0;
                lineToDrawEnd.X = myDrawOverImage.Size.Width;
                int lineYValue = 1;
                while ((lineYValue * stepDistance) < (float)myDrawOverImage.Size.Height)
                {
                    lineToDrawStart.Y = lineYValue * stepDistance;
                    lineToDrawEnd.Y = lineYValue * stepDistance;
                    aGraphics.DrawLine(Pens.Black, lineToDrawStart, lineToDrawEnd);
                    ++lineYValue;
                }

            }
            if (myFrameWidthHeight.X < (float)myOriginalImage.Size.Width)
            {
                int stepDistance = (int)((float)(myFrameWidthHeight.X) * ((float)myDrawOverImage.Size.Width / (float)myOriginalImage.Size.Width));

                lineToDrawStart.Y = 0;
                lineToDrawEnd.Y = myDrawOverImage.Size.Height;
                int lineXValue = 1;
                while ((lineXValue * stepDistance) < (float)myDrawOverImage.Size.Width)
                {
                    lineToDrawStart.X = lineXValue * stepDistance;
                    lineToDrawEnd.X = lineXValue * stepDistance;
                    aGraphics.DrawLine(Pens.Black, lineToDrawStart, lineToDrawEnd);
                    ++lineXValue;
                }

            }
        }

        private void SetFrameRectangleColumnsRows(Graphics aGraphics)
        {
            int frameWidth = (int)(((float)mySprite.Size.Width / (float)myColumns));
            int frameHeight = (int)(((float)mySprite.Size.Height / (float)myRows));

            int x = frameWidth * (myActiveFrame % myColumns);
            int y = frameHeight * (myActiveFrame / myColumns);

            Rectangle tempRect = new Rectangle(x, y, frameWidth, frameHeight);


            SolidBrush tempBrush = new SolidBrush(Color.Black);
            tempBrush.Color = Color.FromArgb(100, 0, 0, 0);
            aGraphics.FillRectangle(tempBrush, tempRect);
        }

        private void DrawSpritesheetLinesColumnRows(Graphics aGraphics)
        {
            Point lineToDrawStart = new Point(0, 0);
            Point lineToDrawEnd = new Point(0, 0);

            if (myRows > 1)
            {
                int stepDistance = (myDrawOverImage.Size.Height / myRows);

                lineToDrawStart.X = 0;
                lineToDrawEnd.X = myDrawOverImage.Size.Width;
                for (int iRows = 0; iRows < myRows; ++iRows)
                {
                    lineToDrawStart.Y = (iRows + 1) * stepDistance;
                    lineToDrawEnd.Y = (iRows + 1) * stepDistance;
                    aGraphics.DrawLine(Pens.Black, lineToDrawStart, lineToDrawEnd);
                }

            }
            if (myColumns > 1)
            {
                int stepDistance = (myDrawOverImage.Size.Width / myColumns);

                lineToDrawStart.Y = 0;
                lineToDrawEnd.Y = myDrawOverImage.Size.Height;
                for (int iColumns = 0; iColumns < myColumns; ++iColumns)
                {
                    lineToDrawStart.X = (iColumns + 1) * stepDistance;
                    lineToDrawEnd.X = (iColumns + 1) * stepDistance;
                    aGraphics.DrawLine(Pens.Black, lineToDrawStart, lineToDrawEnd);
                }
            }
        }

        private Point GetFrameWidthColumnsRows()
        {
            Point animFrame = new Point();
            animFrame.X = (int)(((float)myOriginalImage.Size.Width / (float)myColumns));
            animFrame.Y = (int)(((float)myOriginalImage.Size.Height / (float)myRows));
            return animFrame;
        }

        public void ScaleImage()
        {
            myOriginalImage = new Bitmap(myImagePath);
            myAnimation.Picture = new Bitmap(myOriginalImage);


            Size drawArea = this.Size;
            Size imageArea = myOriginalImage.Size;

            float WidthRatio;
            float HeightRatio;

            WidthRatio = (float)drawArea.Width / (float)imageArea.Width;
            HeightRatio = (float)drawArea.Height / (float)imageArea.Height;

            Point newImageSize = new Point(0, 0);
            if (WidthRatio < HeightRatio)
            {
                myScale = WidthRatio;
                newImageSize.X = (int)((float)imageArea.Width * WidthRatio);
                newImageSize.Y = (int)((float)imageArea.Height * WidthRatio);
            }
            else
            {
                myScale = HeightRatio;
                newImageSize.X = (int)((float)imageArea.Width * HeightRatio);
                newImageSize.Y = (int)((float)imageArea.Height * HeightRatio);
            }

            mySprite = new Bitmap(myOriginalImage, newImageSize.X, newImageSize.Y);
        }

        protected override void OnPaint(PaintEventArgs pe)
        {
            base.OnPaint(pe);
            if (myDrawOverImage != null)
            {
                pe.Graphics.DrawImage(myDrawOverImage, new Point(0, 0));
            }
        }

        public void SetImage(string aPath)
        {
            myImagePath = aPath;
            ScaleImage();
            myDrawOverImage = new Bitmap(mySprite);
        }

        public void SetActiveFrame(Point aPoint)
        {
            int tempX = (aPoint.X / (mySprite.Size.Width / myColumns));
            int tempY = (aPoint.Y / (mySprite.Size.Height / myRows));

            SetActiveFrame((tempY * myColumns) + tempX);
        }

        public void SetActiveFrame(int aFrame)
        {
            myActiveFrame = aFrame;
            testDrawStuff();
        }

        public void SaveAnimation(string aFilepath)
        {
            AnimationInfo temp = new AnimationInfo();
            temp.ImagePath = myImagePath;
            temp.FrameIntervalMilliseconds = myFrameIntervallInMilliSeconds;

            if (myFrameStyle == eFrameStyle.eFrameSize)
            {
                temp.FrameWidthHeight = myFrameWidthHeight;
                temp.Columns = ColumnsFrameSize();
                temp.Rows = RowsFrameSize();
            }
            else
            {
                Point sizeXY = new Point();
                sizeXY.X = myOriginalImage.Size.Width / myColumns;
                sizeXY.Y = myOriginalImage.Size.Height / myRows;
                temp.FrameWidthHeight = sizeXY;
                temp.Rows = myRows;
                temp.Columns = myColumns;
            }

            string output = JsonConvert.SerializeObject(temp, Formatting.Indented);
            System.IO.File.WriteAllText(aFilepath, output);
        }

        public AnimationInfo LoadAnimation(string aFilepath)
        {
            string input = System.IO.File.ReadAllText(aFilepath);
            AnimationInfo temp = new AnimationInfo();
            temp = JsonConvert.DeserializeObject<AnimationInfo>(input);

            myFrameIntervallInMilliSeconds = temp.FrameIntervalMilliseconds;
            myImagePath = temp.ImagePath;
            myFrameWidthHeight.X = temp.FrameWidthHeight.X;
            myFrameWidthHeight.Y = temp.FrameWidthHeight.Y;
            return temp;
            
        }

        public int Columns
        {
            set
            {
                myColumns = value;
            }
        }

        public int Rows
        {
            set
            {
                myRows = value;
            }
        }

        public int FrameInterval
        {
            set
            {
                myFrameIntervallInMilliSeconds = value;
                myAnimationTimer.Interval = myFrameIntervallInMilliSeconds;
            }
        }

        private Image mySprite
        {
            set
            {
                this.Image = value;
            }
            get
            {
                return this.Image;
            }
        }

        public Timer AnimationTimer
        {
            set
            {
                myAnimationTimer = value;
            }
        }

        public eFrameStyle FrameStyle
        {
            set
            {
                myFrameStyle = value;
            }
        }

        public int FrameSizeWidth
        {
            set
            {
                myFrameWidthHeight.X = value;
            }
        }

        public int FrameSizeHeight
        {
            set
            {
                myFrameWidthHeight.Y = value;
            }
        }

        private int myActiveFrame;

        private Bitmap myDrawOverImage;
        private Bitmap myOriginalImage;
        private Animation myAnimation;
        private Timer myAnimationTimer;
        private Point myFrameWidthHeight;
        private float myScale;
        private int myFrameIntervallInMilliSeconds;

        private eFrameStyle myFrameStyle;

        private int myColumns;
        private int myRows;

        private string myImagePath;
    }
}
