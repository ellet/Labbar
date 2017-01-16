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
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Globalization;
using System.Linq;
using System.Windows.Forms;
using FlowGraph.Enums;

namespace FlowGraph
{
    /// <summary>
    /// Represents a flow chart node (block) for use in a FlowGraphModel
    /// </summary>
    public class FlowGraphNode
    {
        /// <summary>
        /// Creates a new node in a given model given a descriptor
        /// </summary>
        /// <param name="descriptor"></param>
        /// <param name="model"></param>
        public FlowGraphNode(FlowGraphNodeDescriptor descriptor, FlowGraphModel model)
        {
            myisFailed = false;
            myDescriptor = descriptor;
            _model = model;

            X = descriptor.X;

            Y = descriptor.Y;

            _width = descriptor.Width;

            _height = descriptor.Height;

            UpdateHitRectangle();

            _title = String.IsNullOrWhiteSpace(descriptor.Title) ? null : descriptor.Title.Trim();

            _comment = String.IsNullOrWhiteSpace(descriptor.Comment) ? null : descriptor.Comment.Trim();

            IsHighlighted = false;

            _connectors = new List<FlowGraphConnector>();

            for (var i = 0; i < descriptor.myPins.Count(); i++)
            {
                ConnectorType connectorType = descriptor.myPins[i].myIsInput == true ? ConnectorType.Input : ConnectorType.Output;

                var si = i.ToString(CultureInfo.InvariantCulture);
                _connectors.Add(new FlowGraphConnector(this, connectorType, i, descriptor.myPins[i].myName, descriptor.myPins[i].myType, descriptor.myPins[i].myCommandPath));
            }

            Guid guid = Guid.NewGuid();
            byte[] gb = guid.ToByteArray();
            myGuid = BitConverter.ToInt64(gb, 0);

            Object = descriptor.Object;
        }

        [Browsable(false)]
        public Object Object { get; set; }

        [Browsable(false)]
        public List<FlowGraphConnector> OutputConnectors
        {
            get
            {
                return _connectors.Where(c => c.Type == ConnectorType.Output).ToList();
            }
        }

        [Browsable(false)]
        public List<FlowGraphConnector> InputConnectors
        {
            get
            {
                return _connectors.Where(c => c.Type == ConnectorType.Input).ToList();
            }
        }

        /// <summary>
        /// Node title (text displayed in the node header)
        /// </summary>
        [Category("FlowGraphNode")]
        public string Title { get { return _title; } }

        public bool myisFailed;

        /// <summary>
        /// X position (model space) of the node
        /// </summary>
        [Browsable(false)]
        public int X;

        /// <summary>
        /// Y position (model space) of the node
        /// </summary>
        [Browsable(false)]
        public int Y;

        /// <summary>
        /// Width of the node
        /// </summary>
        [Browsable(false)]
        public int Width { get { return _width; } set { _width = value; UpdateHitRectangle(); } }

        /// <summary>
        /// Height of the node
        /// </summary>
        [Browsable(false)]
        public int Height { get { return _height; } set { _height = value; UpdateHitRectangle(); } }

        /// <summary>
        /// The model this node belongs to
        /// </summary>
        [Browsable(false)]
        public FlowGraphModel Model { get { return _model; } }

        /// <summary>
        /// Whether the node is highlighted (selected)
        /// </summary>
        [Browsable(false)]
        public bool IsHighlighted;

        public FlowGraphNodeDescriptor GetDescriptor() { return myDescriptor; }

        /// <summary>
        /// The hit (mouse click) rectangle of the node
        /// </summary>
        [Browsable(false)]
        public Rectangle HitRectangle;

        /// <summary>
        /// This node's connectors list
        /// </summary>
        [Browsable(false)]
        public List<FlowGraphConnector> Connectors { get { return _connectors; } }

        /// <summary>
        /// Node commentary (text displayed above the node)
        /// </summary>
        [Category("FlowGraphNode")]
        public string Comment { get { return _comment; } set { _comment = value; } }

        public event PaintEventHandler PostDraw;

        /// <summary>
        /// Gets the connector index, given the connector object reference
        /// </summary>
        /// <param name="connector">the connector reference</param>
        /// <returns>the connector index</returns>
        public int GetConnectorIndex(FlowGraphConnector connector)
        {
            if (connector == null)
                throw new NullReferenceException();

            for (var i = 0; i < _connectors.Count; i++)
            {
                if (_connectors[i] == connector) return i;
            }

            return -1;
        }

        /// <summary>
        /// Updates hit rectangle (when moved)
        /// </summary>
        public void UpdateHitRectangle()
        {
            HitRectangle = new Rectangle(X, Y, Width, Height);
        }

        /// <summary>
        /// Intercepts a mouse hit and returns a connector if hit by the mouse, null otherwise
        /// </summary>
        /// <param name="screenPosition"></param>
        /// <returns></returns>
        public FlowGraphConnector GetConnectorMouseHit(Point screenPosition)
        {
            var hitRectangle = new Rectangle(screenPosition, Size.Empty);

            return _connectors.FirstOrDefault(connector => hitRectangle.IntersectsWith(connector.HitArea));
        }

        /// <summary>
        /// Draws the node
        /// </summary>
        /// <param name="e"></param>
        public void Draw(PaintEventArgs e)
        {
            var ctrlPos = _model.View.ModelToControl(new Point(X, Y));

            var scaledX = ctrlPos.X;

            var scaledY = ctrlPos.Y;

            var rectangle = new Rectangle(scaledX, scaledY, (int)(HitRectangle.Width * _model.CurrentZoom), (int)(HitRectangle.Height * _model.CurrentZoom));

            if (Model.View.DrawShadow)
                e.Graphics.DrawImage(FlowGraphResources.NodeShadow, Model.View.ModelToControl(new Rectangle( X - (int)(0.1f * Width) + 4, Y - (int)(0.1f * Height) + 4, Width + (int)(0.2f * Width)-4, Height + (int)(0.2f * Height)-4)));

            var nodeIconBitmap = FlowGraphResources.NodeValid; // TODO: Implement custom icons support
            if (myisFailed == true)
            {
                e.Graphics.FillRectangle(_model.View.NodeFillFailed, rectangle);

                e.Graphics.FillRectangle(_model.View.NodeFill, new Rectangle(rectangle.X, rectangle.Y, rectangle.Width, (int)(_model.View.NodeHeaderSize * _model.CurrentZoom)));

                e.Graphics.DrawRectangle(_model.View.NodeOutline, rectangle);
                nodeIconBitmap = FlowGraphResources.NodeInvalid;
            }
            else if (!IsHighlighted)
            {
                e.Graphics.FillRectangle(_model.View.NodeFill, rectangle);
                
                e.Graphics.FillRectangle(_model.View.NodeHeaderFill, new Rectangle(rectangle.X, rectangle.Y, rectangle.Width, (int)(_model.View.NodeHeaderSize * _model.CurrentZoom)));
                
                e.Graphics.DrawRectangle(_model.View.NodeOutline, rectangle);
            }
            else
            {
                e.Graphics.FillRectangle(_model.View.NodeFillSelected, rectangle);
                
                e.Graphics.FillRectangle(_model.View.NodeHeaderFill, new Rectangle(rectangle.X, rectangle.Y, rectangle.Width, (int)(_model.View.NodeHeaderSize * _model.CurrentZoom)));
                
                e.Graphics.DrawRectangle(_model.View.NodeOutlineSelected, rectangle);
            }

            var nodeIconPosition = _model.View.ModelToControl(new Point(X + Width - 20, Y + 4));
            
            var nodeIconRectangle = new Rectangle(nodeIconPosition.X, nodeIconPosition.Y, (int)(16 * _model.CurrentZoom), (int)(16 * _model.CurrentZoom));

         

            e.Graphics.DrawImage(nodeIconBitmap, nodeIconRectangle);

            if (_model.CurrentZoom > _model.View.NodeTitleZoomThreshold)
            {
                e.Graphics.DrawString(Title, _model.View.NodeScaledTitleFont, _model.View.NodeTextShadow, new Point(scaledX + (int)(2 * _model.CurrentZoom) + 1, scaledY + (int)(2 * _model.CurrentZoom) + 1));
                
                e.Graphics.DrawString(Title, _model.View.NodeScaledTitleFont, _model.View.NodeText, new Point(scaledX + (int)(2 * _model.CurrentZoom), scaledY + (int)(2 * _model.CurrentZoom)));
            }

            foreach (var connector in _connectors)
                connector.Draw(e);

            if (!String.IsNullOrWhiteSpace(_comment))
                e.Graphics.DrawString(_comment.Trim(), _model.View.NodeScaledTitleFont, _model.View.NodeText, new Point(scaledX, scaledY - (int)(16 * _model.CurrentZoom)));

            FirePostDraw(e);
        }

        protected void FirePostDraw(PaintEventArgs e)
        {
            if (PostDraw != null)
                PostDraw(this, e);
        }

        private readonly String _title;

        private readonly List<FlowGraphConnector> _connectors;

        private readonly FlowGraphModel _model;

        private int _height;

        private int _width;

        private string _comment;

        private FlowGraphNodeDescriptor myDescriptor;

        public long myGuid;
    }
}
