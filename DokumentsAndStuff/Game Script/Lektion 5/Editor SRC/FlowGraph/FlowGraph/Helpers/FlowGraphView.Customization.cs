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

using System.ComponentModel;
using System.Drawing;
using FlowGraph.Enums;

namespace FlowGraph
{
    partial class FlowGraphView
    {
        [Category("FlowGraph")]
        public float NodeTitleZoomThreshold { get; set; }

        [Category("FlowGraph")]
        public float NodeCommentZoomTreshold { get; set; }

        [Category("FlowGraph")]
        public float NodeLabelsZoomTreshold { get; set; }

        [Category("FlowGraph")]
        public int NodeHeaderSize { get; set; }

        [Category("FlowGraph")]
        public LinkVisualStyle LinkVisualStyle
        {
            get { return _linkVisualStyle; }

            set
            {
                _linkVisualStyle = value;

                Refresh();
            }
        }

        [Category("FlowGraph")]
        public int ConnectorHitZoneBleed { get; set; }

        [Category("FlowGraph")]
        public float LinkHardness
        {
            get { return _linkHardness; }

            set
            {
                _linkHardness = value < 1.0f ? 1.0f : value;
            }
        }

        [Category("FlowGraph")]
        public int GridPadding { get; set; }

        [Category("FlowGraph")]
        public bool ShowDebugData { get; set; }

        [Category("FlowGraph")]
        public bool ShowGrid { get; set; }

        [Category("FlowGraph")]
        public byte GridAlpha { get; set; }

        [Category("FlowGraph")]
        public bool DrawShadow { get; set; }

        [Category("FlowGraph")]
        public bool SmoothBehavior { get; set; }

        # region Colors

        [Category("FlowGraph colors")]
        public Color NodeTextColor
        {
            get { return _nodeTextColor; }

            set
            {
                NodeText = new SolidBrush(value);

                _nodeTextColor = value;
            }
        }

        [Category("FlowGraph colors")]
        public Color NodeTextShadowColor
        {
            get { return _nodeTextShadowColor; }

            set
            {
                NodeTextShadow = new SolidBrush(value);

                _nodeTextShadowColor = value;
            }
        }

        [Category("FlowGraph colors")]
        public Color NodeFillColor
        {
            get { return _nodeFillColor; }

            set
            {
                NodeFill = new SolidBrush(value);

                _nodeFillColor = value;
            }
        }


        [Category("FlowGraph colors")]
        public Color NodeFillFailedColor
        {
            get { return _nodeFillFailedColor; }

            set
            {
                NodeFillFailed = new SolidBrush(value);

                _nodeFillFailedColor = value;
            }
        }

        [Category("FlowGraph colors")]
        public Color NodeFillSelectedColor
        {
            get { return _nodeFillSelectedColor; }

            set
            {
                NodeFillSelected = new SolidBrush(value);

                _nodeFillSelectedColor = value;
            }
        }

        [Category("FlowGraph colors")]
        public Color NodeOutlineColor
        {
            get { return _nodeOutlineColor; }

            set
            {
                NodeOutline = new Pen(value);

                _nodeOutlineColor = value;
            }
        }

        [Category("FlowGraph colors")]
        public Color NodeOutlineSelectedColor
        {
            get { return _nodeOutlineSelectedColor; }

            set
            {
                NodeOutlineSelected = new Pen(value);

                _nodeOutlineSelectedColor = value;
            }
        }

        [Category("FlowGraph colors")]
        public Color ConnectorTextColor
        {
            get { return _connectorTextColor; }

            set
            {
                ConnectorText = new SolidBrush(value);

                _connectorTextColor = value;
            }
        }

        [Category("FlowGraph colors")]
        public Color ConnectorFillColor
        {
            get { return _connectorFillColor; }

            set
            {
                ConnectorFill = new SolidBrush(value);

                _connectorFillColor = value;
            }
        }

        [Category("FlowGraph colors")]
        public Color ConnectorOutlineColor
        {
            get { return _connectorOutlineColor; }

            set
            {
                ConnectorOutline = new Pen(value);

                _connectorOutlineColor = value;
            }
        }

        [Category("FlowGraph colors")]
        public Color ConnectorFillSelectedColor
        {
            get { return _connectorSelectedFillColor; }

            set
            {
                ConnectorFillSelected = new SolidBrush(value);

                _connectorSelectedFillColor = value;
            }
        }

        [Category("FlowGraph colors")]
        public Color ConnectorOutlineSelectedColor
        {
            get { return _connectorOutlineSelectedColor; }

            set
            {
                ConnectorOutlineSelected = new Pen(value);

                _connectorOutlineSelectedColor = value;
            }
        }

        [Category("FlowGraph colors")]
        public Color SelectionFillColor
        {
            get { return _selectionFillColor; }

            set
            {
                _selectionFill = new SolidBrush(value);

                _selectionFillColor = value;
            }
        }

        [Category("FlowGraph colors")]
        public Color SelectionOutlineColor
        {
            get { return _selectionOutlineColor; }

            set
            {
                _selectionOutline = new Pen(value);

                _selectionOutlineColor = value;
            }
        }

        [Category("FlowGraph colors")]
        public Color NodeHeaderColor
        {
            get { return _nodeHeaderColor; }

            set
            {
                NodeHeaderFill = new SolidBrush(value);

                _nodeHeaderColor = value;
            }
        }

        [Category("FlowGraph colors")]
        public Color LinkColor
        {
            get { return _linkColor; }

            set
            {
                _link = new Pen(value, 0.5f);

                _linkArrow = new SolidBrush(value);

                _linkColor = value;
            }
        }

        [Category("FlowGraph colors")]
        public Color LinkEditableColor
        {
            get { return _linkEditableColor; }

            set
            {
                _linkEditable = new Pen(value, 0.5f);

                _linkEditableColor = value;
            }
        }

        #endregion
    }
}
