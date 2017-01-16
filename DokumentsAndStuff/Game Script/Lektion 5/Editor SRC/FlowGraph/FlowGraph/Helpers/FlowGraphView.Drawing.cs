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

using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;
using FlowGraph.Enums;

namespace FlowGraph
{
    partial class FlowGraphView
    {
        /// <summary>
        /// Draws the selection rectangle
        /// </summary>
        /// <param name="e"></param>
        private void DrawSelectionBox(PaintEventArgs e)
        {
            if (_editMode == FlowGraphEditMode.SelectingBox)
            {
                var viewRectangle = new Rectangle();
                if (_selectBoxOrigin.X > _selectBoxCurrent.X)
                {
                    viewRectangle.X = _selectBoxCurrent.X;
                    viewRectangle.Width = _selectBoxOrigin.X - _selectBoxCurrent.X;
                }
                else
                {
                    viewRectangle.X = _selectBoxOrigin.X;
                    viewRectangle.Width = _selectBoxCurrent.X - _selectBoxOrigin.X;
                }
                if (_selectBoxOrigin.Y > _selectBoxCurrent.Y)
                {
                    viewRectangle.Y = _selectBoxCurrent.Y;
                    viewRectangle.Height = _selectBoxOrigin.Y - _selectBoxCurrent.Y;
                }
                else
                {
                    viewRectangle.Y = _selectBoxOrigin.Y;
                    viewRectangle.Height = _selectBoxCurrent.Y - _selectBoxOrigin.Y;
                }


                e.Graphics.FillRectangle(_selectionFill, ModelToControl(viewRectangle));
                e.Graphics.DrawRectangle(_selectionOutline, ModelToControl(viewRectangle));
            }
        }

        /// <summary>
        /// Draws the currently edited link
        /// </summary>
        /// <param name="e"></param>
        private void DrawLinkEditable(PaintEventArgs e)
        {
            if (_editMode == FlowGraphEditMode.Linking)
            {
                var startRect = _activeLeftConnector.Area;
                var startPos = new Point(startRect.X + (int)(6 * Model.CurrentZoom),
                    startRect.Y + (int)(4 * Model.CurrentZoom));
                var endPos = ModelToControl(new Point(_viewSpaceCursorLocation.X, _viewSpaceCursorLocation.Y));
                var startPosBezier = new Point(startPos.X + (int)((endPos.X - startPos.X) / LinkHardness),
                    startPos.Y);
                var endPosBezier = new Point(endPos.X - (int)((endPos.X - startPos.X) / LinkHardness), endPos.Y);

                switch (_linkVisualStyle)
                {
                    case LinkVisualStyle.Curve:
                        e.Graphics.DrawBezier(_linkEditable, startPos, startPosBezier, endPosBezier, endPos);
                        break;
                    case LinkVisualStyle.Direct:

                        e.Graphics.DrawLine(_linkEditable, startPos, endPos);
                        break;
                    case LinkVisualStyle.Rectangle:
                        e.Graphics.DrawLine(_linkEditable, startPos, startPosBezier);
                        e.Graphics.DrawLine(_linkEditable, startPosBezier, endPosBezier);
                        e.Graphics.DrawLine(_linkEditable, endPosBezier, endPos);
                        break;
                }
            }
        }

        /// <summary>
        /// Draws all links already created
        /// </summary>
        /// <param name="e"></param>
        private void DrawAllLinks(PaintEventArgs e)
        {
            foreach (var link in Model.Links)
            {
                var inRect = link.LeftConnector.Area;
                var outRect = link.RightConnector.Area;
                var startPos = new Point(inRect.X + (int)(6 * Model.CurrentZoom),
                    inRect.Y + (int)(4 * Model.CurrentZoom));
                var endPos = new Point(outRect.X + (int)(-4 * Model.CurrentZoom),
                    outRect.Y + (int)(4 * Model.CurrentZoom));
                var startPosBezier = new Point(startPos.X + (int)((endPos.X - startPos.X) / LinkHardness),
                    startPos.Y);
                var endPosBezier = new Point(endPos.X - (int)((endPos.X - startPos.X) / LinkHardness), endPos.Y);

                Point[] arrow =
                {
                    new Point(endPos.X + (int) (10*Model.CurrentZoom), endPos.Y),
                    new Point(endPos.X, endPos.Y - (int) (4*Model.CurrentZoom)),
                    new Point(endPos.X, endPos.Y + (int) (4*Model.CurrentZoom))
                };


                var linkPen = _link;
                var linkArrow = _linkArrow;

                switch (_linkVisualStyle)
                {
                    case LinkVisualStyle.Curve:
                        e.Graphics.DrawBezier(linkPen, startPos, startPosBezier, endPosBezier, endPos);
                        break;
                    case LinkVisualStyle.Direct:
                        endPos = new Point(outRect.X + (int)(-4 * Model.CurrentZoom),
                            outRect.Y + +(int)(4 * Model.CurrentZoom));
                        e.Graphics.DrawLine(linkPen, startPos, endPos);
                        break;
                    case LinkVisualStyle.Rectangle:
                        e.Graphics.DrawLine(linkPen, startPos, startPosBezier);
                        e.Graphics.DrawLine(linkPen, startPosBezier, endPosBezier);
                        e.Graphics.DrawLine(linkPen, endPosBezier, endPos);
                        break;
                }


                e.Graphics.FillPolygon(linkArrow, arrow);
            }
        }

        /// <summary>
        /// OnPaint Manager: Draws the canvas
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void FlowGraphPanel_Paint(object sender, PaintEventArgs e)
        {
            if (DrawBackground != null) DrawBackground(this, e);

            // Smooth Behavior
            if (SmoothBehavior)
            {
                Model.CurrentZoom += (Model.Zoom - Model.CurrentZoom) * 0.08f;
                if (Math.Abs(Model.CurrentZoom - Model.Zoom) < 0.005)
                {
                    Model.CurrentZoom = Model.Zoom;
                    UpdateFontSize();
                }
                else
                {
                    UpdateFontSize();
                    Invalidate();
                }
            }
            else
            {
                Model.CurrentZoom = Model.Zoom;
                UpdateFontSize();
            }


            e.Graphics.SmoothingMode = SmoothingMode.None;
            e.Graphics.CompositingQuality = CompositingQuality.HighSpeed;
            if (ShowGrid)
            {
                var bgLum = (BackColor.R + BackColor.G + BackColor.B) / 3;
                var gridColor = bgLum < 128 ? Color.FromArgb(GridAlpha, 255, 255, 255) : Color.FromArgb(GridAlpha, 0, 0, 0);

                var gridPen = new Pen(gridColor);

                var viewTopLeft = ControlToModel(new Point(0, 0));
                var viewBottomRight = ControlToModel(new Point(Width, Height));
                var minGridX = viewTopLeft.X - (viewTopLeft.X % GridPadding);
                var minGridY = viewTopLeft.Y - (viewTopLeft.Y % GridPadding);
                var maxGridX = viewBottomRight.X + (viewBottomRight.X % GridPadding);
                var maxGridY = viewBottomRight.Y + (viewBottomRight.Y % GridPadding);

                Point currentGridIn, currentGridOut;

                for (var i = minGridX; i < maxGridX; i += GridPadding)
                {
                    currentGridIn = ModelToControl(new Point(i, viewTopLeft.Y));
                    currentGridOut = ModelToControl(new Point(i, viewBottomRight.Y));
                    e.Graphics.DrawLine(gridPen, currentGridIn, currentGridOut);
                }
                for (var j = minGridY; j < maxGridY; j += GridPadding)
                {
                    currentGridIn = ModelToControl(new Point(viewTopLeft.X, j));
                    currentGridOut = ModelToControl(new Point(viewBottomRight.X, j));
                    e.Graphics.DrawLine(gridPen, currentGridIn, currentGridOut);
                }
            }

            foreach (var node in Model.Nodes)
                node.Draw(e);

            // Select Box
            DrawSelectionBox(e);
            e.Graphics.SmoothingMode = SmoothingMode.AntiAlias;
            DrawLinkEditable(e);
            DrawAllLinks(e);
            e.Graphics.SmoothingMode = SmoothingMode.None;

            if (ShowDebugData) DrawDebug(e);
        }

        /// <summary>
        /// Draws debug information
        /// </summary>
        /// <param name="e"></param>
        private void DrawDebug(PaintEventArgs e)
        {
            e.Graphics.DrawString("Edit Mode:" + _editMode, _debugFont, NodeText, new PointF(0.0f, 0.0f));
            e.Graphics.DrawString("ViewX: " + Model.ModelX, _debugFont, NodeText, new PointF(0.0f, 10.0f));
            e.Graphics.DrawString("ViewY: " + Model.ModelY, _debugFont, NodeText, new PointF(0.0f, 20.0f));
            e.Graphics.DrawString("ViewZoom: " + Model.Zoom, _debugFont, NodeText, new PointF(0.0f, 30.0f));

            e.Graphics.DrawString(
                "ViewSpace Cursor Location:" + _viewSpaceCursorLocation.X + " : " + _viewSpaceCursorLocation.Y,
                _debugFont, NodeText, new PointF(0.0f, 50.0f));

            e.Graphics.DrawString("AltPressed: " + _isAltPressed, _debugFont, NodeText, new PointF(0.0f, 70.0f));

            // BELOW: DEBUG ELEMENTS

            var originPen = new Pen(Color.Lime);
            e.Graphics.DrawLine(originPen, ModelToControl(new Point(-100, 0)), ModelToControl(new Point(100, 0)));
            e.Graphics.DrawLine(originPen, ModelToControl(new Point(0, -100)), ModelToControl(new Point(0, 100)));

            e.Graphics.DrawBezier(originPen, ModelToControl(_selectBoxOrigin), ModelToControl(_selectBoxOrigin),
                ModelToControl(_selectBoxCurrent), ModelToControl(_selectBoxCurrent));
        }
    }
}
