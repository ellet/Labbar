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

using System.Drawing;
using System.Linq;
using FlowGraph.Enums;
using FlowGraph.EventArguments;

namespace FlowGraph
{
    partial class FlowGraphView
    {
        /// <summary>
        /// Converts a point coordinates from control space to model space
        /// </summary>
        /// <param name="point"></param>
        /// <returns></returns>
        public Point ControlToModel(Point point)
        {
            return new Point((int)((point.X - (Width / 2)) / Model.CurrentZoom) - Model.ModelX,
                (int)((point.Y - (Height / 2)) / Model.CurrentZoom) - Model.ModelY);
        }

        /// <summary>
        /// Converts a point coordinates from model space to control space
        /// </summary>
        /// <param name="point"></param>
        /// <returns></returns>
        public Point ModelToControl(Point point)
        {
            return new Point((int)((point.X + Model.ModelX) * Model.CurrentZoom) + (Width / 2),
                (int)((point.Y + Model.ModelY) * Model.CurrentZoom) + (Height / 2));
        }

        /// <summary>
        /// Converts a rectangle coordinates and sizes from control space to model space
        /// </summary>
        /// <param name="rectangle"></param>
        /// <returns></returns>
        public Rectangle ControlToModel(Rectangle rectangle)
        {
            return new Rectangle(ControlToModel(new Point(rectangle.X, rectangle.Y)),
                new Size((int)(rectangle.Width / Model.CurrentZoom), (int)(rectangle.Height / Model.CurrentZoom)));
        }

        /// <summary>
        /// Converts a rectangle coordinates and sizes from model space to control space
        /// </summary>
        /// <param name="rectangle"></param>
        /// <returns></returns>
        public Rectangle ModelToControl(Rectangle rectangle)
        {
            return new Rectangle(ModelToControl(new Point(rectangle.X, rectangle.Y)),
                new Size((int)(rectangle.Width * Model.CurrentZoom), (int)(rectangle.Height * Model.CurrentZoom)));
        }

        /// <summary>
        /// Returns the other end of a connector
        /// </summary>
        /// <param name="linkOutConnector"></param>
        /// <returns></returns>
        public FlowGraphConnector GetLink(FlowGraphConnector linkOutConnector)
        {
            return (from link in Model.Links where link.RightConnector == linkOutConnector select link.LeftConnector).FirstOrDefault();
        }

        /// <summary>
        /// Returns whether a connector is already linked
        /// </summary>
        /// <param name="connector"></param>
        /// <returns></returns>
        public bool IsLinked(FlowGraphConnector connector)
        {
            return Model.Links.Any(link => link.LeftConnector == connector || link.RightConnector == connector);
        }

        /// <summary>
        /// Tells if the cursor is in the scroll area
        /// </summary>
        /// <param name="cursorLocation"></param>
        /// <returns></returns>
        public bool IsInScrollArea(Point cursorLocation)
        {
            if (cursorLocation.X > _scrollMargins
                && cursorLocation.X < Width - _scrollMargins
                && cursorLocation.Y > _scrollMargins
                && cursorLocation.Y < Height - _scrollMargins)
                return false;

            return true;
        }

        /// <summary>
        /// Updates panel scrolling
        /// </summary>
        /// <param name="cursorLocation"></param>
        private void UpdateScroll(Point cursorLocation)
        {
            if (cursorLocation.X < _scrollMargins)
                Model.ModelX += (int)(_scrollMarginsValue / Model.CurrentZoom);
            else if (cursorLocation.X > Width - _scrollMargins)
                Model.ModelX -= (int)(_scrollMarginsValue / Model.CurrentZoom);
            else if (cursorLocation.Y < _scrollMargins)
                Model.ModelY += (int)(_scrollMarginsValue / Model.CurrentZoom);
            else if (cursorLocation.Y > Height - _scrollMargins)
                Model.ModelY -= (int)(_scrollMarginsValue / Model.CurrentZoom);
        }

        /// <summary>
        /// Updates selection highlights
        /// </summary>
        private void UpdateHighlights()
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

            foreach (var node in Model.Nodes)
                node.IsHighlighted = node.HitRectangle.IntersectsWith(viewRectangle);
        }

        /// <summary>
        /// Creates a selection of FlowGraphNodes depending on the click or selection rectangle
        /// </summary>
        private void CreateSelection()
        {
            Model.SelectedNodes.Clear();

            var i = 0;

            foreach (var node in Model.Nodes)
                if (node.IsHighlighted)
                {
                    i++;

                    Model.SelectedNodes.Add(node);
                }

            if (i > 0)
                FireSelectionChanged(new FlowGraphViewSelectionEventArgs(i));

            if (i == 0)
                FireSelectionCleared(new FlowGraphViewSelectionEventArgs(i));
        }

        /// <summary>
        /// Returns a HitType depending on what Hit the cursor within the selected items
        /// </summary>
        /// <param name="cursorLocation"></param>
        /// <returns></returns>
        private HitType HitSelected(Point cursorLocation)
        {
            var hitTest = new Rectangle(ControlToModel(cursorLocation), new Size());

            foreach (var node in Model.SelectedNodes)
                if (hitTest.IntersectsWith(node.HitRectangle))
                {
                    var hitConnector = node.GetConnectorMouseHit(cursorLocation);

                    return hitConnector == null ? HitType.Node : HitType.Connector;
                }

            return HitType.Nothing;
        }

        /// <summary>
        /// Returns a HitType depending on what Hit the cursor within the All items
        /// </summary>
        /// <param name="cursorLocation"></param>
        /// <returns></returns>
        private HitType HitAll(Point cursorLocation)
        {
            var hitTest = new Rectangle(ControlToModel(cursorLocation), new Size());

            foreach (var node in Model.Nodes)
                if (hitTest.IntersectsWith(node.HitRectangle))
                {
                    var hitConnector = node.GetConnectorMouseHit(cursorLocation);

                    return hitConnector == null ? HitType.Node : HitType.Connector;
                }

            return HitType.Nothing;
        }

        /// <summary>
        /// Gets the connector associated to the mouse hit
        /// </summary>
        /// <param name="cursorLocation"></param>
        /// <returns></returns>
        private FlowGraphConnector GetHitConnector(Point cursorLocation)
        {
            var hitTest = new Rectangle(ControlToModel(cursorLocation), new Size());

            foreach (var node in Model.Nodes)
                if (hitTest.IntersectsWith(node.HitRectangle))
                    return node.GetConnectorMouseHit(cursorLocation);

            return null;
        }

        /// <summary>
        /// Adds a link drawn by the user
        /// </summary>
        private void AddLink()
        {
            if (_activeLeftConnector != null &&
                _activeRightConnector != null &&
                _activeLeftConnector != _activeRightConnector &&
                _activeLeftConnector.Type == ConnectorType.Output &&
                _activeRightConnector.Type == ConnectorType.Input)
                AddLink(_activeLeftConnector, _activeRightConnector);

            _activeLeftConnector = null;

            _activeRightConnector = null;
        }

        /// <summary>
        /// Moves the selection, given an offset
        /// </summary>
        /// <param name="offset"></param>
        private void MoveSelection(Point offset)
        {
            foreach (var node in Model.SelectedNodes)
            {
                node.X -= offset.X;

                node.Y -= offset.Y;

                node.UpdateHitRectangle();
            }
        }

        /// <summary>
        /// Updates font size, depending of the model Zoom
        /// </summary>
        private void UpdateFontSize()
        {
            NodeScaledTitleFont = new Font(NodeTitleFont.Name, NodeTitleFont.Size * Model.CurrentZoom);
            
            NodeScaledConnectorFont = new Font(NodeConnectorFont.Name, NodeConnectorFont.Size * Model.CurrentZoom);
        }
    }
}
