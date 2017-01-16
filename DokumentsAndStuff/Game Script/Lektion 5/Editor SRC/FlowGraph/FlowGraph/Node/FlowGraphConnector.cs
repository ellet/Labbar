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
using System.Windows.Forms;
using FlowGraph.Enums;
using System.Collections.Generic;

namespace FlowGraph
{
    /// <summary>
    /// Represents a connector on a node
    /// </summary>
    public class CommandPath
    {
       public CommandPath(string aPath, string aName)
        {
            myPath = aPath;
            myName = aName;
        }
        public string myPath;
        public string myName;
    }
    public class FlowGraphConnector
    {
        /// <summary>
        /// Creates a new connector, given a label, a parent node, type and index
        /// </summary>
        /// <param name="label">Connector label</param>
        /// <param name="node">Parent node</param>
        /// <param name="type">Connector type (input/output)</param>
        /// <param name="index">Connector index</param>
        public FlowGraphConnector(FlowGraphNode node, ConnectorType type, int index, string label = null, string aType = null, CommandPath aCommandPath = null)
        {
            Label = String.IsNullOrWhiteSpace(label) ? null : label.Trim();
            Node = node;
            Model = node.Model;
            Type = type;
            Index = index;
            VarType = aType;
            myCommandPath = aCommandPath;
        }

        public List<FlowGraphLink> myLinks;
        public void AddLink(FlowGraphLink aLink)
        {
            if (myLinks == null)
            {
                myLinks = new List<FlowGraphLink>();
            }
            myLinks.Add(aLink);
        }

        public void RemoveLink(FlowGraphLink aLink)
        {
            if (myLinks != null)
            {
                myLinks.Remove(aLink);
            }
        }

        public bool HasLink()
        {
            if (myLinks != null)
            {
                return myLinks.Count > 0;
            }
            return false;
        }

        /// <summary>
        /// Connector label
        /// </summary>
        public string Label { get; private set; }


        public CommandPath myCommandPath;
        public string VarType { get; private set; }

        /// <summary>
        /// A node this connector belongs to
        /// </summary>
        public FlowGraphNode Node { get; private set; }

        /// <summary>
        /// Connector index
        /// </summary>
        public int Index { get; private set; }

        /// <summary>
        /// Connector type (input/output)
        /// </summary>
        public ConnectorType Type { get; private set; }

        /// <summary>
        /// A model this connector belongs to
        /// </summary>
        public FlowGraphModel Model { get; private set; }

        public string myData { get; set; }

        /// <summary>
        /// A rectangle determining the visible area of the connector
        /// </summary>
        public Rectangle Area
        {
            get
            {
                Point position;

                Rectangle connectorRectangle;

                switch (Type)
                {
                    case ConnectorType.Input:
                        position = Model.View.ModelToControl(new Point(Node.X, (Node.Y + Model.View.NodeHeaderSize + 6 + (Index * 16))));

                        connectorRectangle = new Rectangle(position.X, position.Y, (int)(12 * Model.CurrentZoom), (int)(8 * Model.CurrentZoom));

                        break;

                    default: // case ConnectorType.OutputConnector:
                        position = Model.View.ModelToControl(new Point(Node.X + (Node.HitRectangle.Width - 12), (Node.Y + Model.View.NodeHeaderSize + 6 + (Index * 16))));

                        connectorRectangle = new Rectangle(position.X, position.Y, (int)(12 * Model.CurrentZoom), (int)(8 * Model.CurrentZoom));

                        break;
                }

                return connectorRectangle;
            }
        }

        /// <summary>
        /// A rectangle determining the click area of the connector
        /// </summary>
        public Rectangle HitArea
        {
            get
            {
                Point position;

                Rectangle connectorRectangle;

                var bleed = Model.View.ConnectorHitZoneBleed;

                switch (Type)
                {
                    case ConnectorType.Input:
                        position = Model.View.ModelToControl(new Point(Node.X, (Node.Y + Model.View.NodeHeaderSize + 6 + (Index * 16))));

                        connectorRectangle = new Rectangle(position.X - bleed, position.Y - bleed, (int)(12 * Model.CurrentZoom) + (2 * bleed), (int)(8 * Model.CurrentZoom) + (2 * bleed));

                        break;

                    default: // case ConnectorType.OutputConnector:
                        position = Model.View.ModelToControl(new Point(Node.X + (Node.HitRectangle.Width - 12), (Node.Y + Model.View.NodeHeaderSize + 6 + (Index * 16))));

                        connectorRectangle = new Rectangle(position.X - bleed, position.Y - bleed, (int)(12 * Model.CurrentZoom) + (2 * bleed), (int)(8 * Model.CurrentZoom) + (2 * bleed));

                        break;
                }

                return connectorRectangle;
            }
        }

        /// <summary>
        /// Returns the position of the displayed text
        /// </summary>
        /// <param name="e">PaintEventArgs used for measure</param>
        /// <returns>Position of the text</returns>
        public Point GetTextPosition(PaintEventArgs e)
        {
            var label = String.IsNullOrWhiteSpace(Label) ? String.Empty : Label.Trim();

            Point textPosition;

            switch (Type)
            {
                case ConnectorType.Input:
                    textPosition = Model.View.ModelToControl(new Point(Node.X + 16, Node.Y + Model.View.NodeHeaderSize + 4 + (Index * 16)));

                    break;

                default: // case ConnectorType.OutputConnector:
                    var measure = e.Graphics.MeasureString(label, Model.View.NodeScaledConnectorFont);

                    textPosition = Model.View.ModelToControl(new Point(Node.X + (Node.HitRectangle.Width), Node.Y + Model.View.NodeHeaderSize + 4 + (Index * 16)));

                    textPosition.X = textPosition.X - (int)(16.0f * Model.CurrentZoom) - (int)measure.Width;

                    break;
            }

            return textPosition;
        }

        /// <summary>
        /// Draws the connector
        /// </summary>
        /// <param name="e"></param>
        public void Draw(PaintEventArgs e)
        {
            var label = String.IsNullOrWhiteSpace(Label) ? String.Empty : Label.Trim();

            var connectorRectangle = Area;
            var connectorOutlinePen = Model.View.ConnectorOutline;

            var connectorFillBrush = Model.View.ConnectorFill;
            if (VarType != null)
            {
                connectorFillBrush = GetColor(VarType);
            }

            e.Graphics.FillRectangle(connectorFillBrush, connectorRectangle);

            e.Graphics.DrawRectangle(connectorOutlinePen, connectorRectangle);

            if (Model.CurrentZoom > Model.View.NodeLabelsZoomTreshold)
            {
                var textPosition = GetTextPosition(e);

                string theVal = String.IsNullOrWhiteSpace(myData) ? String.Empty : "[" + myData.Trim() + "]";
                e.Graphics.DrawString(label + theVal, Model.View.NodeScaledConnectorFont, Model.View.ConnectorText, textPosition.X, textPosition.Y);
            }
        }

        SortedDictionary<string, Color> myValues;

        public void CreateValues()
        {
            myValues["int"] = Color.Green;
            myValues["long"] = Color.DarkGreen;
            myValues["float"] = Color.LightBlue;
            myValues["impulse"] = Color.IndianRed;
            myValues["bool"] = Color.Yellow;
            myValues["pointer"] = Color.Pink;
            myValues["string"] = Color.White;
            myValues[""] = Color.Black;
        }
        public SolidBrush GetColor(string aType)
        {
            if (myValues == null )
            {
                myValues = new SortedDictionary<string, Color>();
                CreateValues();
            }

            SolidBrush brush = Model.View.ConnectorFill;

            string type = aType.ToLower();
            if(myValues.ContainsKey(type) == true)
            {
                brush = new SolidBrush(myValues[type]);
            }
            else
            {
                brush = new SolidBrush(Color.Gray);
            }
            return brush;
        }
    }
}
