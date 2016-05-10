using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ANIMATIOOOONS.Classes
{
    public class SpriteViewer : PictureBox
    {
        public SpriteViewer(Animation anAnimationWindow)
        {
            myColumns = 4;
            myRows = 4;
            myDrawOverImage = null;        
            myActiveFrame = 0;
            myAnimation = anAnimationWindow;
            myAnimationTimer = new Timer();
        }

        public void StartAnimation()
        {
            myAnimationTimer.Start();
        }

        public void PlayAnimation()
        {
            int currentFrame = myActiveFrame;
            ++currentFrame;
            if (currentFrame >= (myColumns * myRows))
            {
                currentFrame = 0;
            }

            SetActiveFrame(currentFrame);
        }

        public void testDrawStuff()
        {
            Graphics tempg = Graphics.FromImage(myDrawOverImage);
            
            tempg.Clear(Color.Transparent);

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
                    tempg.DrawLine(Pens.Black, lineToDrawStart, lineToDrawEnd);
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
                    tempg.DrawLine(Pens.Black, lineToDrawStart, lineToDrawEnd);
                }
            }

            int frameWidth = (int)(((float)mySprite.Size.Width / (float)myColumns));
            int frameHeight = (int)(((float)mySprite.Size.Height / (float)myRows));

            int x = frameWidth * (myActiveFrame % myColumns);
            int y = frameHeight * (myActiveFrame / myColumns);

            Rectangle tempRect = new Rectangle(x, y, frameWidth, frameHeight);

            int animFrameWidth = (int)(((float)myOriginalImage.Size.Width / (float)myColumns));
            int animFrameHeight = (int)(((float)myOriginalImage.Size.Height / (float)myRows));

            int animX = animFrameWidth * (myActiveFrame % myColumns);
            int animY = animFrameHeight * (myActiveFrame / myColumns);

            myAnimation.SpriteRectangle = new Rectangle(animX, animY, animFrameWidth, animFrameHeight);

            SolidBrush tempBrush = new SolidBrush(Color.Black);
            tempBrush.Color = Color.FromArgb(100, 0, 0, 0);
            tempg.FillRectangle(tempBrush, tempRect);

            this.Refresh();
            tempg.Dispose();
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

        private int myActiveFrame;

        private Bitmap myDrawOverImage;
        private Bitmap myOriginalImage;
        private Animation myAnimation;
        private Timer myAnimationTimer;
        private float myScale;

        private int myColumns;
        private int myRows;

        private string myImagePath;
    }
}

//float imageScale;

//Size SizeOfOrigin = tempImage.Size;

//            if (tempImage.Size.Height > tempImage.Size.Width)
//            {
//                imageScale = (float)SizeOfOrigin.Width / (float)SizeOfOrigin.Height;
//            }
//            else
//            {
//                imageScale = (float)SizeOfOrigin.Height / (float)SizeOfOrigin.Width;
//            }

           
//            if (drawArea.Width<drawArea.Height)
//            {
//                tempSize.X = drawArea.Width;
//                tempSize.Y = (int)((float)drawArea.Width* ((float)tempImage.Size.Height / (float)tempImage.Size.Width));
//            }
//            else
//            {
//                tempSize.Y = drawArea.Height;
//                tempSize.X = (int)((float)drawArea.Height* ((float)tempImage.Size.Width / (float)tempImage.Size.Height));
//            }

//            //tempSize.X = (int)((float)drawArea.Width * Scale);
//            //tempSize.Y = (int)((float)drawArea.Height * Scale);


    //Rectangle tempRect = new Rectangle(0, 0, (int)(((float)mySprite.Size.Width / (float)myColumns)), (int)(((float)mySprite.Size.Height / (float)myRows)));


                //tempg.DrawRectangle(Pens.Black, tempRect);